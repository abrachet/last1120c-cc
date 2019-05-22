#include <gtest/gtest.h>

#include "../../src/Parse/ParseExpr.h"
#include "TokenList.h"
#include "Token.h"
#include "UserError.h"
#include <queue>
#include <iostream>
#include "AST/Variable.h"
#include "AST/AbstractVisitor.h"
#include "AST/Expr/BinaryOperator.h"
#include "AST/Expr/NumberExpr.h"



TEST(ParseExpr, SanityTest)
{
    TokenList tl;
    // (1 + 2) * 3
    tl.push_back(Token("(", 1));
    tl.push_back(Token("1", 1));
    tl.push_back(Token("+", 1));
    tl.push_back(Token("2", 1));
    tl.push_back(Token(")", 1));
    tl.push_back(Token("*", 1));
    tl.push_back(Token("3", 1));
    tl.push_back(Token(";", 1));

    std::vector<Variable> known = {Token("a", 1)};

    std::deque<Token> deque;
    UserError e;

    auto iter = shunting_yard(tl.begin(), deque, e, known);

    ASSERT_TRUE(iter);

    // expect '1 2 + 3 *'
    // too lazy to test that though

    ASSERT_EQ(deque.size(), 5);

    auto tree = rpn_to_tree(deque);

    EXPECT_TRUE(deque.empty()) << "length is: " << deque.size() << "\n";

    // we want the tree
    //      *
    //    +    3
    //  1   2
    BinaryOperator* bo = dynamic_cast<BinaryOperator*>(tree.get());
    ASSERT_TRUE(bo);
    EXPECT_EQ(bo->get_type(), BinaryOperator::Multiplication);

    NumberExpr* right = dynamic_cast<NumberExpr*>(bo->get_right().get());
    ASSERT_TRUE(right);
    EXPECT_EQ(right->get_value(), 3);

    BinaryOperator* left = dynamic_cast<BinaryOperator*>(bo->get_left().get());
    ASSERT_TRUE(left);
    EXPECT_EQ(left->get_type(), BinaryOperator::Addition);
    
    NumberExpr* lr = dynamic_cast<NumberExpr*>(left->get_right().get());
    ASSERT_TRUE(lr);
    EXPECT_EQ(lr->get_value(), 2);

    NumberExpr* ll = dynamic_cast<NumberExpr*>(left->get_left().get());
    ASSERT_TRUE(ll);
    EXPECT_EQ(ll->get_value(), 1);

}

TEST(ParseExpr, BasicExpr)
{
    TokenList tl;
    tl.push_back(Token("a", 1));
    tl.push_back(Token("=", 1));
    tl.push_back(Token("8", 1));
    tl.push_back(Token("+", 1));
    tl.push_back(Token("12", 2));
    tl.push_back(Token(";", 1));

    std::vector<Variable> known = {Token("a", 1)};

    std::deque<Token> queue;
    UserError e;

    auto iter = shunting_yard(tl.begin(), queue, e, known);

    while (!queue.empty()) {
        std::cout << queue.front().to_string() << ' ';
        queue.pop_front();
    }

    std::cout << std::endl;

    ASSERT_TRUE(iter);
}

TEST(ParseExpr, BasicExpr_)
{
    TokenList tl;
    tl.push_back(Token("a", 1));
    tl.push_back(Token("=", 1));
    tl.push_back(Token("a", 1));
    tl.push_back(Token("+", 1));
    tl.push_back(Token("12", 2));
    tl.push_back(Token("+", 1));
    tl.push_back(Token("a", 1));
    tl.push_back(Token(";", 1));

    ASSERT_EQ(Token("+", 1), ParseUtil::LiteralTokens::ADDITION);

    std::vector<Variable> known = {Token("a", 1)};

    std::deque<Token> deque;
    UserError e;

    auto iter = shunting_yard(tl.begin(), deque, e, known);

    ASSERT_TRUE(iter);

    //auto tree = rpn_to_tree(deque);

    
}