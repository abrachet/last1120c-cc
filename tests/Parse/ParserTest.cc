#include <gtest/gtest.h>

#include "../../src/Parse/ParseUtil.h"
#include "ScanFile.h"
#include "TokenizedFile.h"
#include "TokenList.h"
#include "AST/Decl/GlobalVarDecl.h"
#include "AST/TranslationUnit.h"
#include "AST/AbstractVisitor.h"


struct GlobalVisitor : public AbstractVisitor {

    GlobalVarDecl last_decl;
    
    GlobalVisitor() : last_decl(Token("fake", 4))
    {}

    void visit(GlobalVarDecl& decl) override {
        last_decl = decl;
    }  
};

TEST(ParserTest, GlobalVars)
{
    TokenizedFile tf = scan_file("tests/Parse/global_var.c.test");

    const TranslationUnit tu = parse_tokenized_file(tf);
    
    const NodeList& nl = tu.get_decls();

    GlobalVisitor visitor;

    nl[0]->accept(visitor);

    EXPECT_EQ(visitor.last_decl.get_token(), Token("regtab", 6));
    EXPECT_EQ(visitor.last_decl.get_value(), 0);

    nl[1]->accept(visitor);

    EXPECT_EQ(visitor.last_decl.get_token(), Token("efftab", 6));
    EXPECT_EQ(visitor.last_decl.get_value(), 1);

    nl[2]->accept(visitor);

    EXPECT_EQ(visitor.last_decl.get_token(), Token("cctab", 5));
    EXPECT_EQ(visitor.last_decl.get_value(), 2);

    nl[3]->accept(visitor);

    EXPECT_EQ(visitor.last_decl.get_token(), Token("sptab", 5));
    EXPECT_EQ(visitor.last_decl.get_value(), 3);
}

TEST(ParserTest, GlobalArrays)
{
    TokenizedFile tf = scan_file("tests/Parse/global_array.c.test");

    TranslationUnit tu = parse_tokenized_file(tf);

    const NodeList& nl = tu.get_decls();

    GlobalVisitor visitor;

    nl[0]->accept(visitor);

    EXPECT_EQ(visitor.last_decl.get_token(), Token("global_three", 12));
    EXPECT_EQ(visitor.last_decl.get_value(), 3);
    EXPECT_FALSE(visitor.last_decl.is_array());

    nl[1]->accept(visitor);

    EXPECT_EQ(visitor.last_decl.get_token(), Token("array_10", 8));
    EXPECT_EQ(visitor.last_decl.get_value(), 10);
    EXPECT_TRUE(visitor.last_decl.is_array());
}
