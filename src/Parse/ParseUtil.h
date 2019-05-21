/**
 * @file Parser.h
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief 
 * @version 0.1
 * @date 2019-05-10
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#include "AST/Type.h"
#include "AST/TranslationUnit.h"
#include "TokenizedFile.h"
#include "Token.h"
#include <cstddef>
#include <cstring>
#include <vector>
#include <type_traits>
#include <functional>

TranslationUnit parse_tokenized_file(TokenizedFile&);

long parse_number(Token t) noexcept(false);
bool __get_array_subscript(Token, int64_t&);

namespace ParseUtil {

namespace LiteralTokens {

// Token::Token() is constexpr so there is not much cost putting these into header files

#ifndef NDEBUG
  #define _constexpr const
#else
  #define _constexpr constexpr
#endif

_constexpr Token INT("int", 3);
_constexpr Token CHAR("char", 4);

_constexpr Token POINTER("[]", 2);
_constexpr Token INDIRECTION("*", 1);
_constexpr Token ADDRESSOF("&", 1);

_constexpr Token IF("if", 2);
_constexpr Token ELSE("else", 4);

_constexpr Token WHILE("while", 5);

_constexpr Token RETURN("return", 6);

_constexpr Token EXTERN("extern", 6);
_constexpr Token AUTO("auto", 4);
_constexpr Token COMMA(",", 1);

_constexpr Token SWITCH("switch", 6);
_constexpr Token CASE("case", 4);
_constexpr Token GOTO("goto", 4);
_constexpr Token COLON(":", 1);

_constexpr Token SEMI_COLON(";", 1);

_constexpr Token LEFT_PAREN("(", 1);
_constexpr Token RIGHT_PAREN(")", 1);
_constexpr Token LEFT_SQ_BRACK("[", 1);
_constexpr Token RIGHT_SQ_BRACK("]", 1);
_constexpr Token LEFT_CR_BRACK("{", 1);
_constexpr Token RIGTH_CR_BRACK("}", 1);

_constexpr Token ASSIGNMENT("=", 1);
_constexpr Token ADDITION("+", 1);
_constexpr Token SUBTRACTION("-", 1);
_constexpr Token MULTIPLICATION("*", 1);
_constexpr Token DIVISION("/", 1); 

_constexpr Token EQUALITY("==", 2);
_constexpr Token INEQUALITY("!=", 2);

_constexpr Token LOGICAL_NOT("!", 1);

#undef _constexpr

} // namespace LiteralTokens

static inline bool is_type(Token t)
{
    return t == LiteralTokens::INT || t == LiteralTokens::CHAR;
}


static inline bool is_math_operator(Token t)
{
    using namespace LiteralTokens;
    return t == ADDITION    || t == MULTIPLICATION
        || t == SUBTRACTION || t == DIVISION;
}

static bool is_keyword(Token t)
{
    if (is_type(t))
        return true;

    using namespace LiteralTokens;
    return t == IF || t == ELSE || t == RETURN ||
    t == WHILE || t == EXTERN || t == AUTO || t == SWITCH ||
    t == CASE || t == GOTO;
}

static bool is_operator(Token t)
{
    if (is_math_operator(t))
        return true;

    using namespace LiteralTokens;
    return (t == POINTER || t == INDIRECTION || t == COMMA ||
    t == COLON || t == SEMI_COLON || t == EQUALITY || 
    t == EQUALITY || t == ASSIGNMENT);
}

static inline bool is_known(Token t)
{
    return is_operator(t) || is_keyword(t);
}

/**
 * @brief parses a number in binary (0b) octal (0) 
 * hex (0x) or decimal 
 * 
 * @param t token representing a number in any valid format
 * @return long 
 */
static long parse_number(Token t) noexcept(false) {
   return ::parse_number(t);
}

static inline bool is_number(Token t)
{
    try {
        // it got upset because it was declared as a friend of class Token...
        // so I need to do this
        ::ParseUtil::parse_number(t);
    } catch (...) {
        return false;
    }

    return true;
}


/**
 * @brief Parses tokens representing character literals like 'a'
 * 
 * @param t 
 * @return char the value of the token 
 */
static inline char parse_char(Token t)
{
    throw "not done";
}

template <typename T>
constexpr bool is_int_type()
{
    return (std::is_same<T, int>::value || std::is_same<T, int64_t>::value ||
            std::is_same<T, unsigned>::value);
}

template <typename parse_t>
static std::vector<parse_t>
parse_list(TokenList::iterator iter, std::function<parse_t(Token)> f, 
    Token end = LiteralTokens::SEMI_COLON)
{
    std::vector<parse_t> ret;

    for (; *iter != end; ++iter) {
        ret.push_back(f(*iter));
        
        ++iter;
        if (*iter == end)
            break;
        cc_assert(*iter == LiteralTokens::COMMA, "expected comma in parse_list");
    }

    return ret;
}

static inline std::vector<Token> 
parse_token_list(TokenList::iterator iter, Token end = LiteralTokens::SEMI_COLON) {
    return parse_list<Token>(iter, [](Token t) { return t; }, end);
}

static bool
is_array_subscript(Token tok)
{
    return tok[0] == '[' && tok[tok.get_size()-1] == ']';
}

static bool
get_array_subscript(Token tok, int64_t& i)
{
    return ::__get_array_subscript(tok, i);
}

} // namespace ParseUtil
