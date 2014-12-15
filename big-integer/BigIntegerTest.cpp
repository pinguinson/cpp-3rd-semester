#include <algorithm>
#include <gtest/gtest.h>

#include "BigInteger.h"
#include "exception.cpp"

TEST(correctness, twoPlusTwo)
{
    BigInteger a = BigInteger(2) + 2,
            b = BigInteger(2) + 2;

    EXPECT_EQ(BigInteger(4), BigInteger(2) + BigInteger(2));
    EXPECT_EQ(4,             BigInteger(2) + 2            );
    EXPECT_EQ(4,             2             + BigInteger(2));
}

TEST(correctness, defaultConstructor)
{
    BigInteger a;
    BigInteger b = 0;
    EXPECT_EQ(0, a);
    EXPECT_EQ(b, a);
}

TEST(correctness, copyConstructor)
{
    BigInteger a = 3;
    BigInteger b = a;

    EXPECT_EQ(b, a);
    EXPECT_EQ(3, b);
}

TEST(correctness, copyConstructorRealCopy)
{
    BigInteger a = 3;
    BigInteger b = a;
    a = 5;

    EXPECT_EQ(3, b);
}

TEST(correctness, copyConstructorRealCopy2)
{
    BigInteger a = 3;
    BigInteger b = a;
    b = 5;

    EXPECT_EQ(3, a);
}

TEST(correctness, assignmentOperator)
{
    BigInteger a = 4;
    BigInteger b = 7;
    b = a;

    EXPECT_TRUE(a == b);
}

TEST(correctness, selfAssignment)
{
    BigInteger a = 5;
    a = a;

    EXPECT_TRUE(a == 5);
}

TEST(correctness, assignmentReturnValue)
{
    BigInteger a = 4;
    BigInteger b = 7;
    (a = b) = a;

    EXPECT_TRUE(a == 7);
    EXPECT_TRUE(b == 7);
}

TEST(correctness, comparisons)
{
    BigInteger a = 100;
    BigInteger b = 100;
    BigInteger c = 200;

    EXPECT_TRUE(a == b);
    EXPECT_TRUE(a != c);
    EXPECT_TRUE(a < c);
    EXPECT_TRUE(c > a);
    EXPECT_TRUE(a <= a);
    EXPECT_TRUE(a <= b);
    EXPECT_TRUE(a <= c);
    EXPECT_TRUE(c >= a);
}

TEST(correctness, compareZeroAndMinusZero)
{
    BigInteger a;
    BigInteger b = -a;

    EXPECT_TRUE(a == b);
}

TEST(correctness, add)
{
    BigInteger a = 5;
    BigInteger b = 20;

    EXPECT_TRUE(a + b == 25);

    a += b;
    EXPECT_TRUE(a == 25);
}

TEST(correctness, addSigned)
{
    BigInteger a = 5;
    BigInteger b = -20;

    EXPECT_TRUE(a + b == -15);

    a += b;
    EXPECT_TRUE(a == -15);
}

TEST(correctness, addReturnValue)
{
    BigInteger a = 5;
    BigInteger b = 1;

    (a += b) += b;
    EXPECT_EQ(7, a);
}

TEST(correctness, sub)
{
    BigInteger a = 20;
    BigInteger b = 5;

    EXPECT_TRUE(a - b == 15);

    a -= b;
    EXPECT_TRUE(a == 15);
}

TEST(correctness, subSigned)
{
    BigInteger a = 5;
    BigInteger b = 20;

    EXPECT_TRUE(a - b == -15);

    a -= b;
    EXPECT_TRUE(a == -15);

    a -= -100;
    EXPECT_TRUE(a == 85);
}

TEST(correctness, subReturnValue)
{
    BigInteger a = 5;
    BigInteger b = 1;

    (a -= b) -= b;
    EXPECT_EQ(3, a);
}

TEST(correctness, mul)
{
    BigInteger a = 5;
    BigInteger b = 20;

    EXPECT_TRUE(a * b == 100);

    a *= b;
    EXPECT_TRUE(a == 100);
}

TEST(correctness, mulSigned)
{
    BigInteger a = -5;
    BigInteger b = 20;

    EXPECT_TRUE(a * b == -100);

    a *= b;
    EXPECT_TRUE(a == -100);
}

TEST(correctness, mulReturnValue)
{
    BigInteger a = 5;
    BigInteger b = 2;

    (a *= b) *= b;
    EXPECT_EQ(20, a);
}

TEST(correctness, unaryPlus)
{
    BigInteger a = 123;
    BigInteger b = +a;

    EXPECT_TRUE(a == b);

    // this code should not compile:
    // &+a;
}

TEST(correctness, negation)
{
    BigInteger a = 666;
    BigInteger b = -a;

    EXPECT_TRUE(b == -666);
}

TEST(correctness, not_)
{
    BigInteger a = 0xaa;

    EXPECT_TRUE(~a == (-a - 1));
}

TEST(correctness, addLong)
{
    BigInteger a("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    BigInteger b(                                                     "100000000000000000000000000000000000000");
    BigInteger c("10000000000000000000000000000000000000000000000000000100000000000000000000000000000000000000");

    EXPECT_EQ(c, a + b);
}

TEST(correctness, addLongSigned)
{
    BigInteger a("-1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    BigInteger b( "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");

    EXPECT_EQ(0, a + b);
}

TEST(correctness, addLongSigned2)
{
    BigInteger a("-1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    BigInteger b(                                                     "100000000000000000000000000000000000000");
    BigInteger c( "-999999999999999999999999999999999999999999999999999900000000000000000000000000000000000000");

    EXPECT_EQ(c, a + b);
}

TEST(correctness, addLongPow)
{
    BigInteger a( "18446744073709551616");
    BigInteger b("-18446744073709551616");
    BigInteger c( "36893488147419103232");

    EXPECT_EQ(c, a + a);
    EXPECT_EQ(a, b + c);
    EXPECT_EQ(a, c + b);
}

TEST(correctness, subLong)
{
    BigInteger a("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    BigInteger b(                                                     "100000000000000000000000000000000000000");
    BigInteger c( "9999999999999999999999999999999999999999999999999999900000000000000000000000000000000000000");

    EXPECT_EQ(c, a - b);
}

TEST(correctness, mulLong)
{
    BigInteger a("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    BigInteger b(                                                     "100000000000000000000000000000000000000");
    BigInteger c("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
            "00000000000000000000000000000000000000");

    EXPECT_EQ(c, a * b);
}

TEST(correctness, mulLongSigned)
{
    BigInteger a("-1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    BigInteger b(                                                     "100000000000000000000000000000000000000");
    BigInteger c("-1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
            "00000000000000000000000000000000000000");

    EXPECT_EQ(c, a * b);
}

TEST(correctness, mulLongSigned2)
{
    BigInteger a("-100000000000000000000000000");
    BigInteger c( "100000000000000000000000000"
                   "00000000000000000000000000");

    EXPECT_EQ(c, a * a);
}

TEST(correctness, mulLongPow)
{
    BigInteger a("18446744073709551616");
    BigInteger b("340282366920938463463374607431768211456");
    BigInteger c("115792089237316195423570985008687907853269984665640564039457584007913129639936");

    EXPECT_EQ(b, a * a);
    EXPECT_EQ(c, b * b);
}

TEST(correctness, negationLong)
{
    BigInteger a( "10000000000000000000000000000000000000000000000000000");
    BigInteger c("-10000000000000000000000000000000000000000000000000000");

    EXPECT_EQ(c, -a);
    EXPECT_EQ(-c, a);
}

TEST(correctness, stringConversion)
{
    EXPECT_EQ("100",               to_string(BigInteger("100")));
    EXPECT_EQ("100",               to_string(BigInteger("0100")));
    EXPECT_EQ("0",                 to_string(BigInteger("0")));
    EXPECT_EQ("0",                 to_string(BigInteger("-0")));
    EXPECT_EQ("-1000000000000000", to_string(BigInteger("-1000000000000000")));
}

TEST(correctness, stringExceptions) {
    EXPECT_NO_THROW(BigInteger("1000000000000000000000000000000000000"));
    EXPECT_THROW(BigInteger("0abc1"), parse_exception);
    EXPECT_THROW(BigInteger("--1"),   parse_exception);
    EXPECT_THROW(BigInteger("1.0"),   parse_exception);
    EXPECT_THROW(BigInteger(""),      parse_exception);
}