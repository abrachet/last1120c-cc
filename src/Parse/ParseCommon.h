/**
 * @file ParseCommon.h
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief 
 * @version 0.1
 * @date 2019-05-14
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#include "ParseUtil.h"
#include "Token.h"
#include "TokenList.h"
#include "AST/Variable.h"

static inline TokenList::iterator 
semi_colon(TokenList::iterator iter)
{
    if (*iter != ParseUtil::LiteralTokens::SEMI_COLON) 
        return false;

    return ++iter;
}

/**
 * @brief 
 * 
 * @return TokenList::iterator 
 */
TokenList::iterator variable_declaration(TokenList::iterator, std::vector<Variable>&);

/**
 * @brief 
 * 
 * @return TokenList::iterator 
 */
TokenList::iterator type(TokenList::iterator, Type&);
