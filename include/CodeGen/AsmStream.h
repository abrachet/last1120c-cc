/**
 * @file AsmStream.h
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief Stream for pretty printing assembly files. I hate C++ streams...
 * This is just a wrapper around C's standard IO streams
 * @version 0.1
 * @date 2019-05-21
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdarg>

template <int indent_size = 4, int max_indents = 4, 
    int total_buf_size = 256>
class AsmStream {
    FILE* f;
    char buffer[total_buf_size];
    
    static constexpr int space_size = max_indents * indent_size;
    static constexpr int buff_size  = total_buf_size - space_size;  

    void write(unsigned indent, const char* fmt, va_list args)
    {
        const char* start = buffer + space_size - (indent * indent_size);

        const size_t len = strlen(fmt);

        assert(len + 2 < buff_size && "too long fmt string");

        // always want to print a newline
        memcpy(buffer + space_size, fmt, len);
        memcpy(buffer + space_size + len, "\n\0", 2);

        vfprintf(f, start, args);
    }

public:
    AsmStream(int fd = STDOUT_FILENO)
    {
        memset(buffer, ' ', space_size);

        if (fd == STDOUT_FILENO)
            f = stdout;
        else if (fd == STDERR_FILENO)
            f = stderr;
        else
            f = fdopen(fd, "w");

        assert(f && "couldn't open file");
    }

    AsmStream(const char* filename)
    : f(fopen(filename, "w+"))
    {
        memset(buffer, ' ', space_size);
        assert(f && "couldn't open file");
    }

    ~AsmStream()
    {
        fclose(f);
    }

    #define __WRITE(i) va_list a; va_start(a, fmt); write(i, fmt, a);

    template <int indent = 1>
    inline void write(const char* fmt, ...)
    {
        __WRITE(indent);
    }

    inline void write_label(const char* fmt, ...)
    {
        __WRITE(0);
    }

    inline void newline()
    {
        fprintf(f, "\n");
    }
};
