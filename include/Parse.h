/**
 * @file Parse.h
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief 
 * @version 0.1
 * @date 2019-05-14
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#include "TokenizedFile.h"
#include "AST/TranslationUnit.h"

TranslationUnit parse_tokenized_file(TokenizedFile&);
