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

class Type {
    Token name;
    std::size_t size;
    Modifier modifier;

public:
    Type() = delete;

    Type(Token name, std::size_t size, Modifier mod = Modifier::None) 
    : name(name), size(size), modifier(mod)
    {}

    Type(Type&) = default;
    Type(const Type&) = default;
  
    inline Token get_name() const { return name; }

    inline std::size_t get_size() const { return size; }

    inline Modifier get_modifier() const { return modifier; }

    inline void add_to_modifier(Modifier mod) { this->modifier |= mod; }
    inline void add_to_modiifer(Type t) { this->add_to_modifier(this->modifier); }

    bool operator==(Type& t) const
    {
        return t.name == this->name && t.size == this->size && t.modifier == this->modifier;
    }
    
    bool operator==(const Type& t) const
    {
        return t.name == this->name && t.size == this->size && t.modifier == this->modifier;
    }
};

namespace BuiltinTypes {

// int should be wordsize because in early versions of c 
static const Type builtin_int(Token("int", 3), INT_WIDTH);
static const Type builtin_char(Token("char", 4), 1);

};