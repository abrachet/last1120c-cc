#include <gtest/gtest.h>

#include "AST/AbstractVisitor.h"
#include "AST/TranslationUnit.h"
#include "AST/GloabalVarDecl.h"
#include "AST/FunctionDecl.h"

TEST(TUTest, Ctor)
{
    TranslationUnit tu("fake.c");

    // unfinished
}

class Visitor : public AbstractVisitor {
    void visit(ASTNodeBase& ) override {

    }
};

TEST(TUTest, Insert)
{
    TranslationUnit tu("fake.c");

    tu.add_node(GlobalVarDecl(Token("global", 5), 3));
    tu.add_node(FunctionDecl(Token("main", 4)));


    auto decls = tu.get_decls();

    Visitor visitor;

    for (int i = 0; i < decls.size(); i++) {
        decls[i]->accept(visitor);
    }

}
