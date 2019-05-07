/**
 * @file ScanFile.cc
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief 
 * @version 0.1
 * @date 2019-05-07
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "ScanFile.hh"

#include <optional>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include "last-cc.hh"
#include "Scanner.hh"
#include "TokenList.hh"
#include "Token.hh"


scan_file(const char* filename) noexcept
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
        return std::nullopt;

    struct stat stat_buf;
    if ( fstat(fd, &stat_buf) == -1)
        return std::nullopt;

    const char* const file = (const char*) 
        mmap(0, stat_buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);

    if (file == MAP_FAILED)
        return std::nullopt;

    TokenList list;

    Scanner scanner(file, stat_buf.st_size);

    Token empty;

    for (Token tok = scanner(); tok != empty; tok = scanner())
        list.push_back(tok);

    // We cannot munmap here!!!
    // this implementation doesn't strdup for every token
    // they are only valid as long as the mapping is in the address space

    // TODO implement a weak_ptr in TokenList so that it can munmap when done

    return std::optional<std::reference_wrapper<TokenList>>{list};
}