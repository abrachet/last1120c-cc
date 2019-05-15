/**
 * @file Parser.cc
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief Parses list of tokens into an AST
 * @version 0.1
 * @date 2019-05-09
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "ParseUtil.h"
#include "last-cc_assert.h"
#include "Token.h"
#include "TokenList.h"
#include "TokenizedFile.h"
#include "AST/Variable.h"
#include "AST/ASTNodeBase.h"
#include "AST/TranslationUnit.h"
#include "AST/Decl/GlobalVarDecl.h"
#include "AST/Decl/FunctionDecl.h"
#include <cstring>
#include <memory>
#include <algorithm>


long parse_number(Token t) noexcept(false)
{   
    const char* start = (const char*) t.start;
    int negative = 1;

    if (*start == '-') {
        start++;
        negative = -1;
    }

    auto try_fail = [&](int base) -> long {
        char* endptr = nullptr;

        long ret = std::strtol(start, &endptr, base);

        if ((uintptr_t) endptr == t.start + t.size)
            return ret * negative;

        throw "Couldn't parse token as number";
    };

    if (start[0] == '0') {

        if (start[1] == 'x') // 0x => hex
            return try_fail(16);

        if (start[1] == 'b') { // 0b => binary
            start += 2;
            return try_fail(2);
        }
        // 0 => octal
        return try_fail(8); 
    }

    return try_fail(10);
}
