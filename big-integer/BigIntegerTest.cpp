#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <utility>
#include <gtest/gtest.h>
#include <iostream>

#include "BigInteger.h"
#include "exception.cpp"

TEST(correctness, default_ctor)
{
    BigInteger a;
    BigInteger b = 0;
    EXPECT_EQ(a, 0);
    EXPECT_EQ(a, b);
}

TEST(correctness, copy_ctor)
{
    BigInteger a = 3;
    BigInteger b = a;

    EXPECT_EQ(a, b);
    EXPECT_EQ(b, 3);
}