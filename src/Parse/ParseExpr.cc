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
#include "UserError.h"
#include <queue>
#include <stack>


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
shunting_yard(TokenList::iterator iter, std::queue<Token>& output_queue, 
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
        std::cout << "just popped " << t.to_string() << '\n';
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
        if (top == operator_map.end()) {
            std::string s = operator_stack.top().to_string();
            std::cout << s << "\n";
            abort();
        }
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
        if (number()) {
            output_queue.push(*iter);
            std::cout << "(num) adding " << iter->to_string() << "\n";
        }

        else if (func()) {
            operator_stack.push(*iter);
            std::cout << "(func) adding " << iter->to_string() << "\n";
        }

        else if (ParseUtil::is_operator(*iter)) {
            std::cout << iter->to_string() << " is an operator\n";
            
            while ( (func_on_stack() || greater_precedence() 
            || eq_and_left()) && not_left_paren()) {
                output_queue.push(pop());
            }
            operator_stack.push(*iter);
            std::cout << "(oper) pushing " << iter->to_string() << "\n";
        }

        else if (*iter == ParseUtil::LiteralTokens::LEFT_PAREN) {
            operator_stack.push(*iter);
            std::cout << "('(') adding " << iter->to_string() << "\n";
        } 

        else if (*iter == ParseUtil::LiteralTokens::RIGHT_PAREN) {
            using namespace ParseUtil::LiteralTokens;

            for (Token t = pop(); t != LEFT_PAREN; t = pop()) {
                output_queue.push(t);
                std::cout << "(')') adding " << iter->to_string() << "\n";
            }
        }

        else {
            std::cout << "Token '" << iter->to_string() << "' matched nowhere\n";
        }
    }

    std::cout << "finished loop\n";

    while (!operator_stack.empty()) {
        output_queue.push(pop());
        std::cout << "_ ";
    }

    std::cout << std::endl;

    return iter;
}
