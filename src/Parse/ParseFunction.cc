/**
 * @file ParseFunction.cc
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief Parses tokens inside of a function
 * @version 0.1
 * @date 2019-05-15
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "ParseFunction.h"
#include "ParseUtil.h"

TokenList::iterator parse_function(TokenList::iterator iter, FunctionDecl& func)
{
    for (; *iter != ParseUtil::LiteralTokens::RIGTH_CR_BRACK; ++iter);

    return ++iter;
}