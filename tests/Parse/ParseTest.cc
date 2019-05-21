#include <gtest/gtest.h>

#include "../../src/Parse/ParseCommon.h"
#include "TokenList.h"

TEST(ParseTest, VarDecl)
{
    TokenList tl;

    tl.push_back(Token("int", 3));
    tl.push_back(Token("a", 1));
    tl.push_back(Token(",", 1));
    tl.push_back(Token("b", 1));
    tl.push_back(Token("[]", 2));
    tl.push_back(Token(";", 1));
    tl.push_back(Token("fake", 4));

    std::vector<Variable> vec;

    auto it = variable_declaration(tl.begin(), vec);

    ASSERT_TRUE(it);
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[0].name, Token("a", 1));
    EXPECT_TRUE(vec[1].type.get_modifier().is_pointer());
}

TEST(ParseTest, ExternAuto)
{
    TokenList tl;
    tl.push_back(Token("extern", 6));
    tl.push_back(Token("a", 1));
    tl.push_back(Token(",", 1));
    tl.push_back(Token("b", 1));
    tl.push_back(Token("[]", 2));
    tl.push_back(Token(";", 1));

    std::vector<Variable> vec;
    variable_declaration(tl.begin(), vec);

    
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[0].name, Token("a", 1));
    EXPECT_EQ(vec[0].type, BuiltinTypes::builtin_int);
    EXPECT_TRUE(vec[1].type.get_modifier().is_pointer());
}
