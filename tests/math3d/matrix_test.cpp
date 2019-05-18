#include "gtest/gtest.h"

#include "math3d/vector.h"
#include "math3d/matrix.h"
#include "math3d/transform.h"

#include <iostream>
#include <iomanip>

TEST(math3d, init)
{
    Matrix3 m(2);
    ASSERT_TRUE(m[0][0] == 2);
    ASSERT_FALSE(m[2][2] == 0);
}

TEST(math3d, inits)
{
    Matrix3 m = {0, 1, 2, 3, 4, 5, 6, 7, 8};
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

TEST(math3d, ident)
{
    Matrix3 m = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    Matrix3 m1 = m.identity();
    ASSERT_TRUE(m1[0][0] == 1);
    ASSERT_TRUE(m1[0][1] == 0); 
}

TEST(math3d, plus)
{
    Matrix3 m = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    Matrix3 m1 = {8, 7, 6, 5, 4, 3, 2, 1, 0};
    Matrix3 mres = m + m1;
    ASSERT_TRUE(mres[0][0] == mres[2][2]);
    ASSERT_TRUE(m1[0][0] == 8); 
}


TEST(math3d, Xtest)
{
    Matrix3 m = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    Matrix3 m1 = {8, 7, 6, 5, 4, 3, 2, 1, 0};
    Matrix3 mres = m * m1;
    ASSERT_TRUE(mres[0][0] == 9);
    ASSERT_TRUE(mres[0][1] == 6);
    ASSERT_TRUE(mres[0][2] == 3);
    ASSERT_TRUE(mres[1][0] == 54);
    ASSERT_TRUE(mres[1][1] == 42);
    ASSERT_TRUE(mres[1][2] == 30);
    ASSERT_TRUE(mres[2][0] == 99);
    ASSERT_TRUE(mres[2][1] == 78);
    ASSERT_TRUE(mres[2][2] == 57);
}

TEST(math3d, matrXvect)
{
    Matrix3 m = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    Vector2 v = {-3, -2};

    Vector2 vecres = m * v;
    ASSERT_TRUE(vecres[0] == 0);
    ASSERT_TRUE(vecres[1] == -12);
}