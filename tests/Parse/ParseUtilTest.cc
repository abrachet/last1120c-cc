#include <gtest/gtest.h>

#include "../../src/Parse/ParseUtil.h"
#include "TokenList.h"

TEST(ParseUtilTest, IsInt)
{
    Token itok("int", 3);

    EXPECT_EQ(itok, ParseUtil::LiteralTokens::INT);
}

TEST(ParseUtilTest, ParseList)
{
    TokenList tl;

    for (int i = 0; i < 3; i++) {
        tl.push_back(Token("tok", 3));
        tl.push_back(Token(",", 1));
    }

    tl.push_back(Token(";", 1));

    auto vec = ParseUtil::parse_list<Token>(tl.begin(), [](Token t) { return t; });

    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], Token("tok", 3));
    EXPECT_EQ(vec[2], Token("tok", 3));
}

TEST(ParseUtilTest, ParseIntList)
{
    TokenList tl;

    tl.push_back(Token("23", 2));
    tl.push_back(Token(",", 1));
    tl.push_back(Token("45", 2));
    tl.push_back(Token(",", 1));
    tl.push_back(Token("67", 2));
    tl.push_back(Token(";", 1));

    auto vec = ParseUtil::parse_list<long>(tl.begin(), [](Token t) { return ParseUtil::parse_number(t); });


    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 23);
    EXPECT_EQ(vec[1], 45);
    EXPECT_EQ(vec[2], 67);
}

TEST(ParseUtilTest, ParseArgList)
{
    TokenList tl;

    tl.push_back(Token("a", 1));
    tl.push_back(Token(",", 1));
    tl.push_back(Token("arg", 3));
    tl.push_back(Token(",", 1));
    tl.push_back(Token("third", 5));
    tl.push_back(Token(")", 1));

    auto vec = ParseUtil::parse_list<Token>(tl.begin(), 
        [](Token t) { return t; }, ParseUtil::LiteralTokens::RIGHT_PAREN);

    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], Token("a", 1));
    EXPECT_EQ(vec[1], Token("arg", 3));
    EXPECT_EQ(vec[2], Token("third", 5));

}


#if 0
TEST(ParseTest, IsInt)
{
    Token itok("int", 3);

    EXPECT_TRUE(ParsingUtil::is_int(itok));

    Token ctok("char", 4);

    EXPECT_FALSE(ParsingUtil::is_int(ctok));
    EXPECT_TRUE(ParsingUtil::is_char(ctok));
}

TEST(ParseTest, FalseTokens)
{
    Token itok("inta", 4);

    EXPECT_FALSE(ParsingUtil::is_int(itok));
}

TEST(ParseTest, ParseInt)
{
    Token fifty_two("52", 2);
    EXPECT_EQ(ParsingUtil::parse_number(fifty_two), 52);

    Token negative_5("-5", 2);
    EXPECT_EQ(ParsingUtil::parse_number(negative_5), -5);

    Token hexa("0x34", 4);
    EXPECT_EQ(ParsingUtil::parse_number(hexa), 52);

    Token octal("064", 3);
    EXPECT_EQ(ParsingUtil::parse_number(octal), 52);

    Token binary("0b110100", 8);
    EXPECT_EQ(ParsingUtil::parse_number(binary), 52);

    Token neg_bin("-0b110100", 9);
    EXPECT_EQ(ParsingUtil::parse_number(neg_bin), -52);

    Token neg_hexa("-0x34", 5);
    EXPECT_EQ(ParsingUtil::parse_number(neg_hexa), -52);

    Token fake("int", 3);
    EXPECT_ANY_THROW(ParsingUtil::parse_number(fake)); 
}
#endif
