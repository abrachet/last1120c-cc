#include <gtest/gtest.h>

#include "../../src/Parse/ParseExpr.h"
#include "TokenList.h"
#include "Token.h"
#include "UserError.h"
#include <queue>
#include <iostream>
#include "AST/Variable.h"

TEST(ParseExpr, SanityTest)
{
    TokenList tl;
    
    tl.push_back(Token("(", 1));
    tl.push_back(Token("1", 1));
    tl.push_back(Token("+", 1));
    tl.push_back(Token("2", 1));
    tl.push_back(Token(")", 1));
    tl.push_back(Token("*", 1));
    tl.push_back(Token("3", 1));
    tl.push_back(Token(";", 1));

    std::vector<Variable> known = {Token("a", 1)};

    std::queue<Token> queue;
    UserError e;

    auto iter = shunting_yard(tl.begin(), queue, e, known);

    while (!queue.empty()) {
        std::cout << queue.front().to_string() << ' ';
        queue.pop();
    }

    std::cout << std::endl;

    ASSERT_TRUE(iter);
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

    std::queue<Token> queue;
    UserError e;

    auto iter = shunting_yard(tl.begin(), queue, e, known);

    while (!queue.empty()) {
        std::cout << queue.front().to_string() << ' ';
        queue.pop();
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

    std::queue<Token> queue;
    UserError e;

    auto iter = shunting_yard(tl.begin(), queue, e, known);

    while (!queue.empty()) {
        std::cout << queue.front().to_string() << ' ';
        queue.pop();
    }

    std::cout << std::endl;

    ASSERT_TRUE(iter);
}