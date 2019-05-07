/**
 * @file Token.hh 
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief Represents a C token. These are outputted by the lexer. Many functions will 
 * return or accept Tokens and not Token&. The reason is that sizeof(Token) == 8. Dealing with
 * pointers to tokens only adds indirection, so references are not slower.
 * 
 * @version 0.1
 * @date 2019-05-05
 * 
 * @copyright Copyright (c) 2019
 */
#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cassert>
#include <string>

struct Token {
private:
    std::uintptr_t    start:48;  ///< const char *, start of the string
    std::size_t        size:16;  ///< size of the string

public:

    Token() : start(0), size(0) 
    {}

    Token(const char* start, std::size_t size) : start((std::uintptr_t)start), size(size)
    {
        #ifndef NDEBUG 
        if (size)
            if (!start)
                throw "no token can have a size and point to 0";
        #endif
    }

    Token(const Token& t) : Token((const char*)t.start, t.size)
    {}

    bool operator==(const Token& t) const
    {
        if (this->size != t.size)
            return false;

        return !strncmp((const char*)this->start, (const char*)t.start, t.size);
    }

    bool operator!=(const Token& t) const {
        return !(*this == t);
    }

    std::string to_string() const
    {
        return std::string((const char*)this->start, 0, this->size);
    }
};
