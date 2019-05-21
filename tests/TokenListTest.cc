#include <gtest/gtest.h>

#include <unistd.h> // getpagesize(3)

#include "TokenList.h"

class TokenListTest : public ::testing::Test {

public:

    inline static const TokenList* get_prev(const TokenList& tl)
    {
        return tl.prev;
    }

    inline static const std::unique_ptr<TokenList>& get_next(const TokenList& tl)
    {
        return tl.next;
    }

    inline static const TokenList::ArrayVec& get_array(const TokenList& tl)
    {
        return tl.tokens;
    }

    static std::size_t list_length(const TokenList& tl)
    {
        std::size_t ret = 0;
        for (auto it : tl) {
            (void) it;
            ret++;
        }

        return ret;
    }

    static const Token& at(const TokenList& tl, std::size_t pos)
    {
        return tl.__debug_at(pos);
    }

};

TEST(TokenListTest, SizeofTokenList)
{
    // already staticly asserted. If this doesn't match something very weird has gone on
    ASSERT_EQ(sizeof(TokenList), getpagesize() - 8) << "Must be page alligned";
}

TEST(TokenListTest, DefaultCtor)
{
    TokenList tl;

    EXPECT_EQ(TokenListTest::get_array(tl).size(), 0);
}

TEST(TokenListTest, InvalidIterDereference)
{
    TokenList tl;

    auto it = tl.rend();

    EXPECT_ANY_THROW(*it);

    tl.push_back(Token("tok", 3));

    it = tl.begin();
    ++it;
    ++it;

    EXPECT_ANY_THROW(*it);
}

TEST(TokenListTest, IterLength)
{
    TokenList tl;

    int count = TokenListTest::list_length(tl);

    EXPECT_EQ(count, 0);

    for (int i = 0; i < 5; i++)
        tl.push_back(Token("token", 5));

    count = TokenListTest::list_length(tl);

    EXPECT_EQ(count, 5);
}

TEST(TokenListTest, InsertMultipleNodes)
{
    TokenList tl;
    constexpr int three_nodes = TokenList::node_size * 2 + 1;

    for (int i = 0; i < three_nodes; i++)
        tl.push_back(Token("token", 5));

    EXPECT_EQ(three_nodes, TokenListTest::list_length(tl));
}

#include <cstring>
#include <random>

TEST(TokenListTest, Retrieval)
{
    TokenList tl;
    std::vector<Token> vec;

    std::vector<char*> to_free;

    constexpr int many = TokenList::node_size * 50 + 200;

    std::default_random_engine rng;

    for (int i = 0; i < many; i++) {

        char* str = (char*) malloc(20);
        (void) std::snprintf(str, 20, "%u.%u", rng(), rng());
        std::size_t len = std::strlen(str);
        Token to_push(str, len);

        vec.push_back(to_push);
        tl.push_back(to_push);

        to_free.push_back(str);
    }

    for (int i = 0; i < many; i++)
        ASSERT_EQ(vec[i], TokenListTest::at(tl, i));

    for (auto i : to_free)
        free(i);
}

TEST(TokenListTest, IteratorOperatorBool)
{
    TokenList::iterator it;

    ASSERT_FALSE(it);

    TokenList tl;

    for (int i = 0; i < 5; i++)
        tl.push_back(Token("tok", 3));

    auto iter = tl.begin();

    ASSERT_TRUE(iter);
}


TEST(TokenListTest, IterEnd)
{
    TokenList tl;

    for (int i = 0; i < 3; i++)
        tl.push_back(Token("tok", 3));


    auto it = tl.begin();
    for (int i = 0; i < 3; i++)
        ++it;

    bool b = it == tl.end();
    ASSERT_TRUE(b);
}
