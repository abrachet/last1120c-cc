#include <gtest/gtest.h>
#include "Token.hh"

TEST(TokenTest, DefaultCtor)
{
    Token t;

    long l = *(long*)&t;

    EXPECT_EQ(l, 0);
}

TEST(TokenTest, Equality)
{
    const Token t1;
    const Token t2;

    EXPECT_EQ(t1, t2);

    const Token t3("hello", 3);
    const Token t4("hello", 3);

    EXPECT_EQ(t3, t4);

    const Token t5("hello", 4);

    EXPECT_NE(t4, t5);
}

TEST(TokenTest, NullptrCtor)
{
    EXPECT_ANY_THROW(new Token(nullptr, 1)) << "can't be a size at nullptr";
}

TEST(TokenTest, ToString)
{
    const Token t1("int", 3);

    std::string int_str("_int_", 1, 3);

    EXPECT_EQ(t1.to_string(), int_str);
}