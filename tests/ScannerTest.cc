
#include "Scanner.h"
#include <gtest/gtest.h>

class ScannerTest : public ::testing::Test
{
public:
    static inline std::size_t get_pos(Scanner& s)
    {
        return s.pos;
    }

    static inline const char* get_start(Scanner& s)
    {
        return s.file;
    }

    static inline std::size_t get_len(Scanner& s)
    {
        return s.len;
    }

    static inline char get_curr_char(Scanner& s)
    {
        return s.curr_char();
    }

    static inline void remove_white_space(Scanner& s)
    {
        return s.ignore_white_space();
    }
};

TEST(ScannerTest, Ctor)
{
    Scanner s("int main() {}", 13);

    EXPECT_EQ(ScannerTest::get_pos(s), 0);
    EXPECT_EQ(ScannerTest::get_len(s), 13);
}

TEST(ScannerTest, IgnoreWhiteSpaceCtor)
{
    Scanner s(" abc", 4);

    ASSERT_EQ(ScannerTest::get_curr_char(s), 'a');

    Scanner s1("   abc", 6);

    ASSERT_EQ(ScannerTest::get_curr_char(s1), 'a');
}


TEST(ScannerTest, ExtractChar)
{
    Scanner s("int main() {}", 13);

    EXPECT_EQ(ScannerTest::get_curr_char(s), 'i');
}

TEST(ScannerTest, IgnoreSingleLine)
{
    Scanner s("//abc\na", 7);

    EXPECT_EQ(ScannerTest::get_curr_char(s), 'a');

    ScannerTest::remove_white_space(s);

    EXPECT_EQ(ScannerTest::get_curr_char(s), 'a');
}

TEST(ScannerTest, MultilineComment)
{
    Scanner s("/*  comment */a", 15);

    EXPECT_EQ(ScannerTest::get_curr_char(s), 'a') << ScannerTest::get_pos(s);
}

TEST(ScannerTest, MultipleComments)
{
    Scanner s("/* comment *//* */a", 19);

    EXPECT_EQ(ScannerTest::get_curr_char(s), 'a');

    Scanner s1("/* comment */  /* */a", 21);

    EXPECT_EQ(ScannerTest::get_curr_char(s1), 'a');

    Scanner s2("//  \n /* */a", 12);

    EXPECT_EQ(ScannerTest::get_curr_char(s2), 'a');
}

TEST(ScannerTest, MalformedComment)
{
    EXPECT_ANY_THROW(Scanner s("/* ", 3));
}

TEST(ScannerTest, NextToken)
{
    Scanner s("int main()", 10);

    Token expect_int("int", 3);
    Token int_tok = s.next_token();
    ASSERT_EQ(int_tok, expect_int) << "token is: " << int_tok.to_string();

    EXPECT_EQ(s.next_token().to_string(), "main");

    EXPECT_EQ(s.next_token().to_string(), "(");

    EXPECT_EQ(s.next_token().to_string(), ")");
}

TEST(ScannerTest, MultiCharOperators)
{
    Scanner s("++i;", 4);

    Token expected_pp("++", 2);
    Token expected_i("i", 1);
    Token expected_sc(";", 1);

    EXPECT_EQ(s.next_token(), expected_pp);
    EXPECT_EQ(s.next_token(), expected_i);
    EXPECT_EQ(s.next_token(), expected_sc);
}

TEST(ScannerTest, Strings)
{
    Scanner s("char a[] = \"hello\";\nint b = 4;", 30);

    Token ex_char("char", 4);
    Token ex_a("a", 1);
    Token ex_brack("[]", 2);
    Token ex_eq("=", 1);
    Token ex_str("\"hello\"", 7);

    EXPECT_EQ(s.next_token(), ex_char);
    EXPECT_EQ(s.next_token(), ex_a);
    EXPECT_EQ(s.next_token(), ex_brack);
    EXPECT_EQ(s.next_token(), ex_eq);
    EXPECT_EQ(s.next_token(), ex_str);
}

TEST(ScannerTest, CharLit)
{
    Scanner s("char a = 'a';", 13);

    Token ex_char("char", 4);
    Token ex_a("a", 1);
    Token ex_eq("=", 1);
    Token ex_ac("'a'", 3);

    EXPECT_EQ(s.next_token(), ex_char);
    EXPECT_EQ(s.next_token(), ex_a);
    EXPECT_EQ(s.next_token(), ex_eq);
    EXPECT_EQ(s.next_token(), ex_ac);
}
