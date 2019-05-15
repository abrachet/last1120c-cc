/**
 * @file ParseCommon.cc
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief 
 * @version 0.1
 * @date 2019-05-14
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "ParseCommon.h"
#include "ParseUtil.h"
#include "Token.h"
#include "TokenList.h"
#include "AST/Variable.h"
#include <vector>

TokenList::iterator
variable_declaration(TokenList::iterator iter, std::vector<Variable>& v)
{
    TokenList::iterator potential;

    cc_assert(v.empty(), "expected empty vector");

    Type t = BuiltinTypes::builtin_int;
    if ( !(potential = type(iter, t)) )
        return false;

    iter = potential;
    
    for (; *iter != ParseUtil::LiteralTokens::SEMI_COLON; ) {
        if (ParseUtil::is_known(*iter))
            return false;

        Variable curr(t, *iter);

        ++iter; 
        if (*iter == ParseUtil::LiteralTokens::POINTER) {
            curr.modifier |= Modifier::Pointer;
            ++iter;
        }

        v.push_back(curr);
        if (*iter == ParseUtil::LiteralTokens::COMMA)
            ++iter;
    }
    
    cc_assert(*iter == ParseUtil::LiteralTokens::SEMI_COLON, "");

    return ++iter;
}

TokenList::iterator
type(TokenList::iterator iter, Type& type)
{
    if ( ParseUtil::is_type(*iter) ) {
        if ( *iter == BuiltinTypes::builtin_int.get_name())
            type = BuiltinTypes::builtin_int;
        else if ( *iter == BuiltinTypes::builtin_char.get_name() )
            type = BuiltinTypes::builtin_char;
        else
            cc_assert(0, "shouldn't have gotten here, is_type() was true but "
                "was neither int or char");

        return ++iter;
    }

    return false;
}
