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
#include <iostream>
#include <string>


//struct Token;
//long parse_number(Token) noexcept(false);

struct alignas(uintptr_t) Token {
private:
    std::uintptr_t    start:48;  ///< const char *, start of the string
    std::size_t        size:16;  ///< size of the string

public:

    friend bool __get_array_subscript(Token, int64_t&);
    //friend struct ParsingUtil;
    friend long parse_number(Token) noexcept(false);

    constexpr Token() : start(0), size(0) 
    {}

    #ifdef NDEBUG
    constexpr
    #endif
    Token(const char* start, std::size_t size) 
    : start(reinterpret_cast<uintptr_t>(start)), size(size)
    {
        #ifndef NDEBUG 
        if (size)
            if (!start)
                throw "no token can have a size and point to 0";
        #endif
    }

    Token(const Token& t) : Token(reinterpret_cast<const char*>(t.start), t.size)
    {}

    bool operator==(const Token& t) const
    {
        if (this->size != t.size)
            return false;

        return !strncmp(reinterpret_cast<const char*>(this->start), 
            reinterpret_cast<const char*>(t.start), t.size);
    }

    bool operator!=(const Token& t) const {
        return !(*this == t);
    }

    std::string to_string() const
    {
        if (this->start == 0)
            return "";

        return std::string(reinterpret_cast<const char*>(this->start), 0, this->size);
    }

    void print_info() const
    {
        std::cout << "size: " << this->size << std::endl; 
    }

    char operator[](uint16_t i) const
    {
        assert(i < size && "out of bounds access");
        return reinterpret_cast<char*>(start)[i];
    }

    uint16_t get_size() const
    {
        return size;
    }
};
