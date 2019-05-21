/**
 * @file GloabalVarDecl.h
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief Represents a variable in the top level in the format 'name 0;'
 * @version 0.1
 * @date 2019-05-09
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#include "Decl.h"
#include "AST/Tags.h"
#include "Token.h"
#include <cstddef>

class GlobalVarDecl : public Decl {
    Token name;
    register_t initial_value;
    bool array;

public:

    using ast_tag = AstTag::recursive_tag;

    /**
     * @brief Construct a new Global Var Decl object
     * 
     * @param name 
     * @param init 
     * @param array if array is true then init represents the number of elements in the array
     */
    GlobalVarDecl(Token name, register_t init = 0, bool array = false)
    : name(name), initial_value(init), array(array)
    {}

    void accept(AbstractVisitor& av) override {
        av.visit(*this);
    }
    
    register_t get_value()
    {
        return this->initial_value;
    }

    Token get_token()
    {
        return this->name;
    }

    bool is_array()
    {
        return this->array;
    }
};
