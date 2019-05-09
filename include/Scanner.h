/**
 * @file Scanner.hh
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief 
 * @version 0.1
 * @date 2019-05-06
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#include "last-cc_assert.h"
#include "last-cc.h"
#include "Token.h"

#include <string>
#include <stdexcept>
#include <csignal>
#include <iostream>

class ScannerTest;

class Scanner {
    const char* file;
    std::size_t pos;
    const std::size_t len;

    static constexpr char delim_chars[] = {
        ' ', '=', '(', ')', '*', ',',
        '-', '+', '/', ';', '[', ']',
        '\n', '\t', '{', '}', '"', ':', '?',
        '>', '<', '^', '&', '|', '%', '!'
    };

    static bool delim_char(char c)
    {
        for (int i = 0; i < sizeof(delim_chars); i++)
            if (c == delim_chars[i])
                return true;

        return false;
    }

    static bool white_space(char c)
    {
        return c == ' ' || c == '\n' || c == '\t';
    }

    /**
     * @brief true for chars which can be doubled for different meanings
     * ++ and + are fundamentally different operators and there cannot be space between them
     */
    static bool can_double(char c) 
    {
        switch(c) {
            case '=': case '<': case '>':
            case '+': case '-': case '&':
            case '|': case ']':
                return true;
        }

        return false;
    }

    /**
     * @brief true for chars which can pair with others to create other operators
     * 
     * += for example
     */
    static bool can_pair(char c) 
    {
        if (c == '/' || c == '*' || c == '[')
            return true;

        return can_double(c);
    }

    static void __segfault_handler(int) {
        throw std::runtime_error("Improperlly written code. No end to comment");
    }

    static bool ignore_char(char c)
    {
        if (c == '/')
            return true;

        return white_space(c);
    }

    void ignore_white_space()
    {
        (void) std::signal(SIGSEGV, &__segfault_handler);

        std::size_t length = 0;
        for (const char* find = this->file + this->pos; ignore_char(*find); find++, length++) {
            if (*find == '/') {
                if (find[1] == '/') {
                    for (; *find != '\n'; find++, length++);
                    length++;
                    goto out;
                }

                if (find[1] == '*') {
                    find += 2;
                    length += 2;
                    for(; find[0] != '*' && find[1] != '/'; find++, length++);
                    length += 2;
                    goto out;
                }
            }
        }
    out:
        (void) std::signal(SIGSEGV, SIG_DFL);

        this->pos += length;

        if (this->pos > this->len)
            throw std::runtime_error("Invalid code caused error in finding end of comment");

        if (ignore_char(this->file[this->pos]))
            ignore_white_space();
    }

    const Token construct_from_delim()
    {

        #define inc_and_ret(start, inc) \
        do {                            \
            const Token t(start, inc);  \
            this->pos += inc;           \
            return t;                   \
        } while(0)

        cc_assert(delim_char(curr_char()), "invalid call to construct_from_delim");

        const char* curr = this->file + this->pos;

        if (can_pair(curr[0]) && can_double(curr[1]))
            inc_and_ret(curr, 2);
        
        inc_and_ret(curr, 1);
    }

    inline char curr_char() const 
    {
        cc_assert(this->pos < this->len, "pos is further than length");

        return this->file[this->pos];
    }

    inline const Token construct_common(char c)
    {
        const char* const start = this->file + this->pos;

        const char* curr = start + 1;

        for (; *curr != c && curr[-1] != '\\'; curr++);

        return Token(start, curr - start + 1);
    }

    inline const Token construct_from_str() 
    {
        cc_assert(curr_char() == '\"', "construct_from_str didn't start on '\"'");

        return construct_common('"');
    }

    inline const Token construct_from_char()
    {
        cc_assert(curr_char() == '\'', "construct_from_str didn't start on \"'\"");

        return construct_common('\'');
    }

public:

    friend class ScannerTest;
    
    Scanner(const char* file, std::size_t len) 
    : file(file), pos(0), len(len)
    {
        #ifndef NDEBUG
        if (!file)
            cc_assert(len == 0, "cannot have length at 0");
        #endif

        ignore_white_space();
    }

    Token next_token()
    {
        this->ignore_white_space();

        if (unlikely(this->pos == len))
            return Token();

        const char* const start = this->file + this->pos;
        const char* curr = start;

        if (*curr == '"')
            return this->construct_from_str();

        if (*curr == '\'')
            return this->construct_from_char();

        if (delim_char(*curr))
            return this->construct_from_delim();
        

        for (; !delim_char(*curr); curr++);

        const std::size_t length = curr - start;

        this->pos += length;

        //this->ignore_white_space();

        return Token(start, length);
    }

    Token operator()()
    {
        return this->next_token();
    }
    
};
