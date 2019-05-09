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
#include "Token.h"
#include <cstddef>

class GlobalVarDecl : public Decl {
public:
    Token name;
    register_t initial_value;

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
