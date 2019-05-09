/**
 * @file TokenizedFile.hh
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief Wrapper around a TokenList so the file's mapping may be unmaped after
 * @version 0.1
 * @date 2019-05-06
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#include <cstddef>
#include <memory>
#include <utility>

#include <sys/mman.h>

#include "TokenList.h"

struct TokenizedFile {
    TokenList list;

    const void* const mapping;
    const std::size_t file_size;

    const bool unmap;

    TokenizedFile(TokenList& list, void* file, std::size_t len) 
    : list(std::move(list)), mapping(file), file_size(len), unmap(true)
    {}

    TokenizedFile(TokenList& list)
    : list(std::move(list)), mapping(nullptr), file_size(0), unmap(false)
    {}

    ~TokenizedFile()
    {
        if (unmap)
            (void) munmap((void*)mapping, file_size);
    }

};