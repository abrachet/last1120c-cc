#include <gtest/gtest.h>

#include "../../src/Parse/TopLevel.h"
#include "Parse.h"
#include "ScanFile.h"
#include "TokenizedFile.h"
#include "TokenList.h"
#include "AST/Decl/FunctionDecl.h"
#include "AST/TranslationUnit.h"
#include "AST/AbstractVisitor.h"

struct FuncVisitor : public AbstractVisitor {
    Token function_name;
    std::vector<Variable> arguments;

    void visit(FunctionDecl& fd) override {
        function_name = fd.get_name();
        arguments = fd.get_args();
    }

};

TEST(ParseFunction, NoArgs)
{
    TokenizedFile tf = scan_file("tests/Parse/no_arg_func.c.test");

    const TranslationUnit tu = parse_tokenized_file(tf);
    
    const NodeList& nl = tu.get_decls();

    FuncVisitor visitor;

    nl[0]->accept(visitor);

    EXPECT_EQ(visitor.function_name, Token("func", 4));

    EXPECT_EQ(visitor.arguments.size(), 0);
}

TEST(ParseFunction, IntArgs)
{
    TokenizedFile tf = scan_file("tests/Parse/int_arg.c.test");

    const TranslationUnit tu = parse_tokenized_file(tf);
    
    const NodeList& nl = tu.get_decls();

    FuncVisitor visitor;

    nl[0]->accept(visitor);

    ASSERT_EQ(visitor.arguments.size(), 2);

    EXPECT_EQ(visitor.arguments[0].name, Token("a", 1));
    EXPECT_EQ(visitor.arguments[1].name, Token("b", 1));
}

TEST(ParseFunction, ComplexArgs)
{
    TokenizedFile tf = scan_file("tests/Parse/complex_arg.c.test");

    const TranslationUnit tu = parse_tokenized_file(tf);
    
    const NodeList& nl = tu.get_decls();

    FuncVisitor visitor;

    nl[0]->accept(visitor);

    EXPECT_EQ(visitor.arguments.size(), 4);

    std::vector<Variable> args = visitor.arguments;

    EXPECT_TRUE(args[0].type.get_modifier().is_func_arg());
    EXPECT_TRUE(args[0].type.get_modifier().is_pointer());
    EXPECT_NE(args[0].type.get_size(), 1);
}
