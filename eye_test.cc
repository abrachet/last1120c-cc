#include "Parse.h"
#include "ScanFile.h"
#include "TokenizedFile.h"
#include "TokenList.h"
#include "AST/Decl/FunctionDecl.h"
#include "AST/TranslationUnit.h"
#include "AST/AbstractVisitor.h"
#include "CodeGen/ARM64.h"

#include <iostream>

int main()
{
    TokenizedFile tf = scan_file("global_var.c.test");

    auto tu = parse_tokenized_file(tf);

    auto decls = tu.get_decls();

    ARM64Backend visitor("global_var.s");

    for (auto& i : decls)
        i->accept(visitor);


    return 0;
}