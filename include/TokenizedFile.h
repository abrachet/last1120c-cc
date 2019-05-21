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

#include "TokenList.h"
#include <sys/mman.h>
#include <cstddef>
#include <memory>
#include <utility>
#include <string>

struct TokenizedFile {
    TokenList list;

    const void* const mapping;
    const std::size_t file_size;
    const std::string filename;

    const bool unmap;

    TokenizedFile(TokenList& list, void* file = nullptr, 
        std::size_t len = 0, std::string filename = "") 
    : list(std::move(list)), mapping(file), file_size(len), 
      filename(filename), unmap(file != nullptr)
    {}

    TokenizedFile(TokenList& list)
    : list(std::move(list)), mapping(nullptr), file_size(0), unmap(false)
    {}

    ~TokenizedFile()
    {
        if (unmap) {
            assert(mapping && "would have tried to munmap a nullptr");
            (void) munmap((void*)mapping, file_size);
        }
    }

};