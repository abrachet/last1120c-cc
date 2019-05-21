/**
 * @file LocalVar.h
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief 
 * @version 0.1
 * @date 2019-05-09
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#include "Type.h"
#include "Token.h"
#include "Modifier.h"

struct Variable {
    Token name;
    Type  type;

    Variable(Type t, Token name = Token("<unnamed>", 10))
    : name(name), type(t)
    {}

    Variable(Token name, 
        Type type = BuiltinTypes::builtin_int) 
    : name(name), type(type)
    {}
};
