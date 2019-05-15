/**
 * @file TopLevel.h
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief Header for 
 * @version 0.1
 * @date 2019-05-14
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#include "TokenList.h"
#include "AST/TranslationUnit.h"
#include "AST/Variable.h"
#include <vector>

/**
 * @brief 
 * 
 * @return TokenList::iterator 
 */
TokenList::iterator global_var(TokenList::iterator, TranslationUnit&);

/**
 * @brief 
 * 
 * @return TokenList::iterator 
 */
TokenList::iterator function(TokenList::iterator, TranslationUnit&);

/**
 * @brief 
 * 
 * @return TokenList::iterator 
 */
TokenList::iterator arg_types(TokenList::iterator, std::vector<Variable>&);


/**
 * @brief add's variables to vec
 * 
 * @param iter 
 * @return TokenList::iterator false_iter if it was unable to match (should never happen)
 */
TokenList::iterator arg_list(TokenList::iterator iter, std::vector<Variable>& vec);
