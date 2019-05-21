/**
 * @file TokenList.hh
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief TokenList provides a fast and space effient way to hold many tokens.
 * @version 0.1
 * @date 2019-05-06
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#include <cstddef>
#include <cstdint>

#include <memory>
#include <iostream>
#include <array>
#include <iterator>

#include <sys/mman.h>

#include "last-cc_assert.h"
#include "Token.h"

// forward decl to be friend class for testing
class TokenListTest;

/**
 * @brief TokenList is an extremly fast linked list of array of tokens. 
 * 
 * It's strange size is derived from pagesize which is pretty standard 4096.
 * sizeof(TokenList) == 4088, which is PAGESIZE - 8. We leave 8 for malloc's 
 * book keeping overhead. 
 * 
 */

//TODO: Need to look if mapping a page at a time is faster with mmap.
struct TokenList {
    static constexpr std::size_t node_size = 508;

private:
    
    struct ArrayVec {
        std::array<Token, node_size> array;
        std::size_t _size;

        ArrayVec() : _size(0)
        {}

        inline std::size_t size() const noexcept { return _size; }
        inline bool has_space() const noexcept { return _size < node_size; }
        inline bool is_full() const noexcept { return _size == node_size; }

        inline const Token& operator[](std::size_t pos) const
        {
            cc_assert(pos < _size, "cannot access elements beyound max_size."
                "operator[] should only be used for reads not writes");

            return array[pos];
        }

        inline void push_back(const Token t)
        {
            cc_assert(_size != node_size, "cannot push_back on full array");

            array[_size++] = t;
        }
    };

    class const_iterator {
        std::size_t pos;
        const TokenList* cur_list;
        bool inacessable;

        const_iterator(const TokenList* list, std::size_t pos = 0) 
        : pos(pos), cur_list(list), inacessable(false)
        {}

        

    public:

        // this is the 'false' iterator, used by the parser 
        // to mean that the path did not match
        constexpr const_iterator() 
        : pos(-1), cur_list(nullptr), inacessable(true)
        {}

        constexpr const_iterator(bool b)
        : pos(-1), cur_list(nullptr), inacessable(true)
        {
            cc_assert(!b, "cannot initiliaze with boolean literal true");
        } 

        friend TokenList;

        using iterator_category = std::bidirectional_iterator_tag;

        const_iterator& operator++() noexcept
        {
            if (this->pos < this->cur_list->tokens.size() - 1) {
                this->pos++;
            }  else if (this->pos == node_size - 1) { // last token of this node, go next
                // end() should be last pointer to last node and pos node->size() + 1
                if (this->cur_list->next == nullptr) {
                    this->pos++;
                    this->inacessable = true;
                } else {
                    this->pos = 0;
                    this->cur_list = this->cur_list->next.get();
                }
            } else { // we are at already at the max token on the final node
                this->pos++;
                this->inacessable = true;  
            }

            return *this;
        }

        const_iterator& operator--() noexcept
        {
            if (this->pos == 0) {
                if (this->cur_list->prev == nullptr)
                    this->pos = (std::size_t)-1;
                else {
                    // back() should be first node and pos -1
                    this->pos = node_size - 1;
                    this->inacessable = true;
                    this->cur_list = this->cur_list->prev;
                }
            } else
                this->pos--;

            return *this; 
        }

        inline bool operator==(const_iterator t) const noexcept
        {
            #if 0
            std::cerr << "operator==() was called\n" 
                "t.pos: " << t.pos << " this->pos: " << this->pos
                << "\nt.cur_list: " << t.cur_list << " this->cur_list: " <<
                this->cur_list << std::endl;
            #endif
            
            return t.pos == this->pos && t.cur_list == this->cur_list;
        }

        inline bool operator!=(const_iterator t) const noexcept
        {
            return !(*this == t);
        }

        /// TODO: Fix this to use a better way than just operator++
        const_iterator operator+(int num)
        {
            cc_assert(num > 0, "cannot add negative");

            auto a = *this;
            for (int i = 0; i < num; i++)
                ++a;
            
            return a;
        }

        const_iterator operator-(int num)
        {
            cc_assert(num > 0, "cannot add negative");

            auto a = *this;
            for (int i = num; i > 0; i--)
                --a;
            
            return a;
        }

        inline operator bool() const noexcept
        {
            return this->pos != -1 && this->cur_list != nullptr;
        }

        inline const Token operator*() const
        {
            cc_assert(!inacessable, "tried to access end or cend");

            return (this->cur_list->tokens[this->pos]);
        }

        inline const Token* operator->() const
        {
            cc_assert(!inacessable, "tried to access end or cend");

            return this->cur_list->tokens.array.data() + this->pos;
        }

        void print_it() const
        {
            std::cout << "cur list: " << this->cur_list << " pos: " << this->pos << std::endl;
        }
    };

    // doesn't do bounds checking unlike other *::at methods
    // this one is clearly just for debugging
    const Token& __debug_at(std::size_t pos) const
    {
        #ifdef DEBUG
        const TokenList* list = this;

        for (; pos > node_size - 1; list = list->next.get(), pos -= node_size);

        return list->tokens[pos];

        #endif
        std::terminate();
    }

    void add_node() noexcept
    {
        this->next = std::make_unique<TokenList>();
        next->prev = this;
    }

    std::unique_ptr<TokenList> next;
    TokenList* prev;
    
    ArrayVec                 tokens;

public:

    using iterator = const_iterator;

    friend class TokenListTest;
    
    TokenList() : next(nullptr), prev(nullptr), tokens()
    {}

    /**
     * @brief inserts a Token into the end of the list
     * 
     * @param t token to insert
     */
    void push_back(const Token t) noexcept
    {
        TokenList* list = this;

        for(; !list->tokens.has_space(); list = list->next.get())
            if (!list->next.get())
                list->add_node();

        list->tokens.push_back(t);
    }

    const_iterator cend() const 
    {
        const TokenList* list = this;

        for(; list->tokens.is_full(); list = list->next.get());

        return const_iterator(list, list->tokens.size());
    }

    const_iterator rend() const
    {
        const_iterator it = this->cbegin();
        return --it;
    }

    const_iterator cbegin() const 
    {
        return const_iterator(this, 0);
    }

    // provided for 'for-each' loops
    // it is still a const_iterator of course
    const_iterator begin() const
    {
        return cbegin();
    }

    const_iterator end() const 
    {
        return cend();
    }

    
};

static_assert(sizeof(TokenList) == 4096 - 8, "not proper size");
