/**
 * @file Type.h
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief 
 * @version 0.1
 * @date 2019-05-09
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#include "Modifier.h"
#include "Token.h"
#include <cstddef>
#include <string>

// int back then was the size of a word
#ifndef INT_WIDTH
  #define INT_WIDTH sizeof(register_t)
#endif

class Type;

// int should be wordsize because in early versions of c 
//static const Type builtin_int (Token("int", 3), INT_WIDTH);
//static const Type builtin_char(Token("char", 4), 1);

class Type {
    const Token name;
    const std::size_t size;
    Modifier modifier;

public:
    Type() = delete;

    Type(Token name, std::size_t size) 
    : name(name), size(size), modifier(Modifier::None)
    {}

    Type(Token name, std::size_t size, Modifier mod) 
    : name(name), size(size), modifier(mod)
    {}

    inline Modifier get_modifier() { return this->modifier; }

    inline Token get_name() { return name; }

    inline std::size_t get_size() { return size; }

    inline void add_to_modifier(Modifier mod) { this->modifier |= mod; } 
};
