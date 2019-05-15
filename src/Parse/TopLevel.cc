/**
 * @file TopLevel.cc
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief 
 * @version 0.1
 * @date 2019-05-14
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "TopLevel.h"
#include "ParseCommon.h"
#include "ParseUtil.h"
#include "ParseFunction.h"
#include "Token.h"
#include "TokenList.h"
#include "AST/Decl/GlobalVarDecl.h"
#include "AST/Decl/FunctionDecl.h"
#include <iostream>

TokenList::iterator 
global_var(TokenList::iterator iter, TranslationUnit& tu)
{
    if (ParseUtil::is_known(*iter))
        return false;

    Token name = *iter;
    long num = 0;
    bool array = false;

    ++iter;

    auto expect_number = [&num](TokenList::iterator it) -> TokenList::iterator {
        try {
            num = ParseUtil::parse_number(*it);
        } catch (...) {
            return false;
        }

        return ++it;
    };

    TokenList::iterator potential;

    // form 'name <%d>;'
    if ( (potential = expect_number(iter)) ) {
        iter = potential;
    // form 'name [<%d>];' to define a zero'd array on data segment
    } else if (*iter == ParseUtil::LiteralTokens::LEFT_SQ_BRACK) {
        ++iter;
        if ( (potential = expect_number(iter)) )
            iter = potential;
        else
            return false;

        if (*iter != ParseUtil::LiteralTokens::RIGHT_SQ_BRACK) 
            return false;

        array = true;
        ++iter;
    }

    // TODO parse form 'name[] 1,2,3;'

    if (*iter != ParseUtil::LiteralTokens::SEMI_COLON)
        return false;

    GlobalVarDecl decl(name, num, array);

    tu.add_node(decl);

    // return past the ';' which we are guaranteed to be on
    return ++iter;
}

TokenList::iterator 
function(TokenList::iterator iter, TranslationUnit& tu)
{
    TokenList::iterator potential;

    Type return_type = BuiltinTypes::builtin_int;
    if ( (potential = type(iter, return_type)) )
        iter = potential;
    
    if (ParseUtil::is_known(*iter))
        return false;

    FunctionDecl func(*iter, return_type);

    ++iter;

    // must be on the '('
    if (*iter != ParseUtil::LiteralTokens::LEFT_PAREN)
        return false;

    ++iter;

    std::vector<Variable> arguments;
    iter = arg_list(iter, arguments);
    cc_assert(iter, "didn't find ')'");

    /// parse the types of the arguments 
    /// ex: func(a, b, c) 
    ///     int a[], c; 
    ///     { }
    /// declares a as pointer to int and b and c as int

    iter = arg_types(iter, arguments);
    cc_assert(iter, "didn't find '{'");

    func.add_arguments(arguments);

    parse_function(iter, func);

    tu.add_node(func);
    // must return after the '}'
    return ++iter;
}

TokenList::iterator
arg_types(TokenList::iterator iter, std::vector<Variable>& vec)
{
    //TokenList::iterator potential;

    std::for_each(vec.begin(), vec.end(), [](Variable v) {
        v.modifier |= Modifier::FuncArgs;
    });

    // we look through the vector that we just got 
    auto assign_to_vec = [&vec](std::vector<Variable>& v) -> bool {
        auto contains = [&vec](Token var_name) {
            return std::find_if(vec.begin(), vec.end(), [var_name](Variable var) {
                return var.name == var_name;
            });
        };

        for (auto& i : v) {
            auto it = contains(i.name);
            if (it == vec.end())
                return false;

            it->type = i.type;
            it->modifier |= i.modifier;
        }

        return true;
    };

    while ( *iter != ParseUtil::LiteralTokens::LEFT_CR_BRACK) {
        std::vector<Variable> curr;

        iter = variable_declaration(iter, curr);
        if (!iter)
            return false;

        assign_to_vec(curr);
    }

    cc_assert(*iter == ParseUtil::LiteralTokens::LEFT_CR_BRACK, "");

    return ++iter;
}

TokenList::iterator
arg_list(TokenList::iterator iter, std::vector<Variable>& vec)
{
    //cc_assert( *(iter - 1) == ParseUtil::LiteralTokens::LEFT_PAREN, "");

    for (;*iter != ParseUtil::LiteralTokens::RIGHT_PAREN; ++iter) {
        if (ParseUtil::is_known(*iter))
            return false;

        vec.push_back(Variable(*iter));

        ++iter;

        if (*iter == ParseUtil::LiteralTokens::RIGHT_PAREN)
            return ++iter;

        if (*iter != ParseUtil::LiteralTokens::COMMA)
            return false;
    }

    return ++iter;
}
