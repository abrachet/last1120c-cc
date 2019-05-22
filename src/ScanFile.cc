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

#include "last-cc.h"
#include "Scanner.h"
#include "TokenList.h"
#include "Token.h"
#include "ScanFile.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

TokenizedFile
scan_file(const char* filename) noexcept(false)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
        throw "couldn't open file";

    struct stat stat_buf;
    if ( fstat(fd, &stat_buf) == -1)
        throw "couldn't stat file";

    // we always map 1 extra byte that should never be written to. 
    // it will always be 0 so we can use that to know the file is over.
    const char* const file = (const char*) 
        mmap(0, stat_buf.st_size + 1, PROT_READ, MAP_PRIVATE, fd, 0);

    if (file == MAP_FAILED)
        throw "couldn't mmap file";

    TokenList list;

    Scanner scanner(file, stat_buf.st_size);

    Token empty;

    for (Token tok = scanner(); tok != empty; tok = scanner())
        list.push_back(tok);

    // We cannot munmap here!!!
    // this implementation doesn't strdup for every token
    // they are only valid as long as the mapping is in the address space

    return TokenizedFile(list, (void*) file, stat_buf.st_size);
}