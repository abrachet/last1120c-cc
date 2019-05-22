/**
 * @file ParseExpr.cc
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief Uses the Shunting-Yard algorithm to parse mathematical expressions
 * @version 0.1
 * @date 2019-05-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "ParseExpr.h"
#include "TokenList.h"
#include "ParseUtil.h"
#include "AST/Decl/FunctionDecl.h"
#include "AST/Expr/BinaryOperator.h"
#include "AST/Expr/SingleTokenExpr.h"
#include "AST/Expr/NumberExpr.h"
#include "UserError.h"
#include <queue>
#include <deque>
#include <stack>
#include <typeinfo>


TokenList::iterator 
parse_assignment_expression(TokenList::iterator iter, 
                    FunctionDecl& parent, UserError& error)
{
    assert(!error && "parse_assignment_expr with an error value");

    if (ParseUtil::is_known(*iter) || ParseUtil::is_number(*iter)) {
        if ( *(++iter) == ParseUtil::LiteralTokens::ASSIGNMENT)
            error.make_error(iter->to_string() + " is not an lvalue");

        return false;
    }

    std::shared_ptr<SingleTokenExpr> left = 
        std::make_shared<SingleTokenExpr>(*iter);

    if ( *(++iter) != ParseUtil::LiteralTokens::ASSIGNMENT) 
        return false;

    std::shared_ptr<Expr> right;

    if ( ! (iter = parse_math_expr(++iter, right, error)) ) 
        return false;

    assert(right && "parse_math_expr should have created ptr or " 
        "returned false");

    auto assign_oper = std::make_shared<BinaryOperator>(BinaryOperator::Assignment);
    assign_oper->add_children(left, right);

    parent.add_statment(assign_oper);

    return iter;
}

TokenList::iterator 
parse_math_expr(TokenList::iterator iter, std::shared_ptr<Expr>& expr, UserError& error,
    Token expected_end)
{
    if (ParseUtil::is_known(*iter))
        return false;

    std::queue<Token> output_queue;
    

    return false;
}

TokenList::iterator
shunting_yard(TokenList::iterator iter, std::deque<Token>& output_queue, 
    UserError& error, const std::vector<Variable>& known, Token expected_end)
{
    std::stack<Token> operator_stack;

    auto number = [known, &iter]() -> bool {
        for (auto& i : known)
            if (i.name == *iter)
                return true;

        return ParseUtil::is_number(*iter);
    };

    auto pop = [&operator_stack]() -> Token {
        Token t = operator_stack.top();
        operator_stack.pop();
        return t;   
    };

    auto func = [&iter]() -> bool {
        if (ParseUtil::is_number(*iter) || ParseUtil::is_operator(*iter))
            return false;
        
        auto i = iter;
        ++i;
        return *i == ParseUtil::LiteralTokens::LEFT_PAREN;
    };

    auto func_on_stack = [&operator_stack]() -> bool {
        if (operator_stack.empty())
            return false;
        
        return is_operator(operator_stack.top());
    };

    auto greater_precedence = [&operator_stack, &iter]() -> bool {
        if (operator_stack.empty())
            return false;

        auto top = operator_map.find(operator_stack.top());
        assert(top != operator_map.end() && "not found in map");

        auto cmp = operator_map.find(*iter);
        assert(cmp != operator_map.end() && "not found in map");

        return top->second.precedence > cmp->second.precedence;
    };

    auto eq_and_left = [&operator_stack, &iter]() -> bool {
        if (operator_stack.empty())
            return false;

        auto top = operator_map.find(operator_stack.top());
        assert(top != operator_map.end() && "not found in map");

        auto cmp = operator_map.find(*iter);
        assert(cmp != operator_map.end() && "not found in map");

        return (top->second.precedence == cmp->second.precedence) && top->second.left_associative;
    };

    auto not_left_paren = [&operator_stack]() -> bool {
        return operator_stack.top() != ParseUtil::LiteralTokens::LEFT_PAREN;
    };

    for (; *iter != expected_end; ++iter) {
        if (number()) 
            output_queue.push_back(*iter);

        else if (func())
            operator_stack.push(*iter);

        else if (ParseUtil::is_operator(*iter)) {            
            while ( (func_on_stack() || greater_precedence() 
            || eq_and_left()) && not_left_paren())
                output_queue.push_back(pop());
            
            operator_stack.push(*iter);
        }

        else if (*iter == ParseUtil::LiteralTokens::LEFT_PAREN)
            operator_stack.push(*iter);
        

        else if (*iter == ParseUtil::LiteralTokens::RIGHT_PAREN) {
            using namespace ParseUtil::LiteralTokens;

            for (Token t = pop(); t != LEFT_PAREN; t = pop())
                output_queue.push_back(t);
            
        }

        else 
            assert(!"token matched nowhere");
    }


    while (!operator_stack.empty())
        output_queue.push_back(pop());
    

    return iter;
}

static std::shared_ptr<BinaryOperator> 
make_expr(Token tok)
{
    using namespace ParseUtil::LiteralTokens;

    BinaryOperator::Type type;

    if (tok == ADDITION)
        type = BinaryOperator::Addition;
    else if (tok == SUBTRACTION)
        type = BinaryOperator::Subtraction;
    else if (tok == MULTIPLICATION)
        type = BinaryOperator::Multiplication;
    else if (tok == EQUALITY)
        type = BinaryOperator::Equality;
    else {
        std::cout << "On token: " << tok.to_string();
        assert(!"invalid token to make expression");
    }
    return std::make_shared<BinaryOperator>(type);
}

std::shared_ptr<Expr> 
rpn_to_tree(std::deque<Token>& deque)
{
    assert(!deque.empty() && "cant be called with empty deque");
    Token top = deque.back();
    deque.pop_back();

    if (ParseUtil::is_number(top)) 
        return std::make_shared<NumberExpr>(ParseUtil::parse_number(top));
    
    // must be a variable
    if (!ParseUtil::is_known(top))
        return std::make_shared<SingleTokenExpr>(top);

    auto ret = make_expr(top);
    auto right = rpn_to_tree(deque);
    auto left  = rpn_to_tree(deque);

    #pragma clang diagnostic push   
    #pragma clang diagnostic ignored "-Wpotentially-evaluated-expression"

    std::cout << "right is: " << typeid(*right.get()).name() << " left is: " << typeid(*left.get()).name() << '\n';

    #pragma clang diagnostic pop

    //std::cout << "current top is: " << deque.back().to_string() << '\n';
    ret->add_children(left, right);

    return ret;
}
