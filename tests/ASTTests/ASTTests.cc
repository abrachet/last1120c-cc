#include <gtest/gtest.h>

#include "AST/AbstractVisitor.h"
#include "AST/TranslationUnit.h"
#include "AST/GloabalVarDecl.h"
#include "AST/FunctionDecl.h"
#include <string>

TEST(TUTest, Ctor)
{
    TranslationUnit tu("fake.c");

    // unfinished
}

struct Visitor : public AbstractVisitor {
    std::string func_name = "";
    int init_value = -1;

    Visitor() {}

    void visit(GlobalVarDecl& gv) override {
        init_value = gv.get_value();
    }

    void visit(FunctionDecl& fd) override {
        func_name = fd.get_name().to_string();
    }


};

TEST(TUTest, Insert)
{
    TranslationUnit tu("fake.c");

    tu.add_node(GlobalVarDecl(Token("global", 5), 3));
    tu.add_node(FunctionDecl(Token("main", 4)));

    auto decls = tu.get_decls();

    Visitor visitor;

    for (int i = 0; i < decls.size(); i++)
        decls[i]->accept(visitor);
    

    ASSERT_EQ(visitor.init_value, 3);
    ASSERT_EQ(visitor.func_name, "main");

}
