/**
 * @file ParseFunction.h
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief Parses function scope Tokens
 * @version 0.1
 * @date 2019-05-14
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#include "TokenList.h"
#include "AST/Decl/FunctionDecl.h"

/**
 * @brief 
 * 
 * @param iter 
 * @param func 
 * @return TokenList::iterator 
 */
TokenList::iterator parse_function(TokenList::iterator iter, FunctionDecl& func);
