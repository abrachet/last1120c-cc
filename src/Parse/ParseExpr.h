/**
 * @file ParseExpr.h
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief 
 * @version 0.1
 * @date 2019-05-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#include "Token.h"
#include "TokenList.h"
#include "ParseUtil.h"
#include "AST/Expr/Expr.h"
#include "AST/Variable.h"
#include <memory>
#include <unordered_map>
#include <queue>
#include <vector>

class FunctionDecl;
class UserError;

TokenList::iterator parse_assignment_expression(TokenList::iterator, 
                    FunctionDecl& parent, UserError& error);

TokenList::iterator parse_math_expr(TokenList::iterator, 
                    std::shared_ptr<Expr>&, UserError&,
                    Token expected_end = ParseUtil::LiteralTokens::SEMI_COLON);

TokenList::iterator
shunting_yard(TokenList::iterator, std::queue<Token>&, 
    UserError&, const std::vector<Variable>&, Token expected_end = ParseUtil::LiteralTokens::SEMI_COLON);


struct OpInfo {
    uint8_t precedence;
    bool    left_associative;
};


template <>
struct std::hash<Token> {
    std::size_t operator()(const Token& ) const {
        return 0;
    }
};

// 
// https://en.cppreference.com/w/c/language/operator_precedence
//
static const std::unordered_map<Token, OpInfo> operator_map = {
    { ParseUtil::LiteralTokens::LEFT_PAREN,     {1, false} },
    { ParseUtil::LiteralTokens::RIGHT_PAREN,    {1, false} },

    { ParseUtil::LiteralTokens::LOGICAL_NOT,    {2, false} },
    { ParseUtil::LiteralTokens::INDIRECTION,    {2, false} },
    { ParseUtil::LiteralTokens::ADDRESSOF,      {2, false} },

    { ParseUtil::LiteralTokens::MULTIPLICATION, {3, true}  },
    { ParseUtil::LiteralTokens::DIVISION,       {3, true}  },

    { ParseUtil::LiteralTokens::ADDITION,       {4, true}  },
    { ParseUtil::LiteralTokens::SUBTRACTION,    {4, true}  },

    { ParseUtil::LiteralTokens::EQUALITY,       {5, true}  },
    { ParseUtil::LiteralTokens::INEQUALITY,     {5, true}  },

    { ParseUtil::LiteralTokens::ASSIGNMENT,     {14, false}}
};

static bool 
is_operator(Token tok)
{
    auto it = operator_map.find(tok);
    return it != operator_map.end();
}
