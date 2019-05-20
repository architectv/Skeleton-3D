#include "gtest/gtest.h"

#include "math3d/matrix4.h"
#include "math3d/matrix3.h"

#include <iostream>
#include <iomanip>

TEST(matrix, init)
{
    Matrix3i m(2);
    ASSERT_TRUE(m[0][0] == 2);
    ASSERT_FALSE(m[2][2] == 0);
}

TEST(matrix, inits)
{
    Matrix3i m{{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};
    ASSERT_TRUE(m[0][0] == 0);
    ASSERT_TRUE(m[0][1] == 1);
    ASSERT_TRUE(m[0][2] == 2);
    ASSERT_TRUE(m[1][0] == 3);
    ASSERT_TRUE(m[1][1] == 4);
    ASSERT_TRUE(m[1][2] == 5);
    ASSERT_TRUE(m[2][0] == 6);
    ASSERT_TRUE(m[2][1] == 7);
    ASSERT_TRUE(m[2][2] == 8);
}

TEST(matrix, ident)
{
    Matrix3i m1;
    ASSERT_TRUE(m1[0][0] == 1);
    ASSERT_TRUE(m1[0][1] == 0); 
}

TEST(matrix, plus)
{
    Matrix3i m{{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};
    Matrix3i m1{{8, 7, 6}, {5, 4, 3}, {2, 1, 0}};
    Matrix3i mres(m + m1);
    ASSERT_TRUE(mres[0][0] == mres[2][2]);
    ASSERT_TRUE(m1[0][0] == 8); 
}


TEST(matrix, Xtest)
{
    Matrix3i m{{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};
    Matrix3i m1{{8, 7, 6}, {5, 4, 3}, {2, 1, 0}};
    Matrix3i mres{m * m1};
    ASSERT_EQ(mres[0][0], 57);
    ASSERT_EQ(mres[0][1], 78);
    ASSERT_EQ(mres[0][2], 99);
    ASSERT_EQ(mres[1][0], 30);
    ASSERT_EQ(mres[1][1], 42);
    ASSERT_EQ(mres[1][2], 54);
    ASSERT_EQ(mres[2][0], 3);
    ASSERT_EQ(mres[2][1], 6);
    ASSERT_EQ(mres[2][2], 9);
}

TEST(matrix, matrXvect)
{
    Matrix3i m{{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};
    Vector2i v = {-3, -2};

    Vector2i vecres{m.map_point(v)};
    ASSERT_EQ(vecres[0], 0);
    ASSERT_EQ(vecres[1], -4);
}