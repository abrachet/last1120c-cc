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

#include "AST/Decl.h"
#include "AST/Tags.h"
#include "Token.h"
#include <cstddef>

class GlobalVarDecl : public Decl {
    Token name;
    register_t initial_value;

public:

    using ast_tag = AstTag::recursive_tag;

    GlobalVarDecl(Token name, register_t init = 0)
    : name(name), initial_value(init)
    {}

    virtual ~GlobalVarDecl() {}

    virtual void accept(AbstractVisitor& av) override {
        av.visit(*this);
    }

    register_t get_value()
    {
        return this->initial_value;
    }
};
