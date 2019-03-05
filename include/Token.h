/**
 * @file Token.h
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief Defines struct token. Tokens do not own the strings to which they point
 * they are only valid so long as the mmaped file still exists in memory. 
 * This saves calls to strdup at th expensive of more work. This is why this header also
 * defines functions for comparing tokens as if they were strings
 * 
 * @version 0.1
 * @date 2019-02-25
 * 
 * @copyright Copyright (c) 2019
 * @license GNU GPLv3 
 */
#include <stddef.h>
#include <stdint.h>

/**
 * @brief Token type. 
 * Pointer to the start of the token and its length
 * 
 * Safe to use only 48 bits of the pointer because I don't
 * have 256 terbytes of memory, 
 */
struct token {  // alignas(64)
    uintptr_t    start:48;  ///< const char *, start of the string
    size_t        size:16;  ///< size of the string
};


/**
 * @brief Aligns on pagesize - malloc info assumed to be 8
 * Doubly linked list of array of tokens
 */
struct tokens {
    struct tokens* next;
    struct tokens* prev;

    uint16_t       length;
    char           __padding[6];
    struct token   tokens[506];
};

/**
 * @brief compares a token with a string
 * 
 * @param token 
 * @param str 
 * @return int same return style of strcmp, 0 if they are the same
 */
int tk_strcmp(struct token* token, const char* str);
