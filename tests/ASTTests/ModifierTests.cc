#include <gtest/gtest.h>

#include "AST/Modifier.h"

TEST(ModTest, Ctor)
{
    Modifier mod;

    ASSERT_EQ(mod.as_int(), 0);
}

TEST(ModTest, OrEq)
{
    Modifier arg(Modifier::FuncArgs);
    Modifier aut0(Modifier::Auto);

    arg |= aut0;

    ASSERT_EQ(arg.as_int(), 5);
}

TEST(ModTest, Is_)
{
    Modifier mod(Modifier::FuncArgs);

    ASSERT_TRUE(mod.is_func_arg());
    ASSERT_FALSE(mod.is_auto());
    ASSERT_FALSE(mod.is_none());
}
