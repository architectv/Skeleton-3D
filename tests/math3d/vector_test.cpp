#include "gtest/gtest.h"

#include "math3d/vector.h"
#include "math3d/matrix.h"
#include "math3d/transform.h"

#include <iostream>
#include <iomanip>

TEST(math3d, init)
{
    Vector<10> v = {1, 2, 3, 4, 5};
    ASSERT_EQ(v[0], 1);
    ASSERT_EQ(v[1], 2);
    ASSERT_EQ(v[2], 3);
    ASSERT_EQ(v[3], 4);
    ASSERT_EQ(v[4], 5);
    ASSERT_EQ(v[5], 0);
}

TEST(math3d, init2)
{
    Vector<10> v(-3);
    ASSERT_EQ(v[0], -3);
    ASSERT_EQ(v[1], -3);
    ASSERT_EQ(v[9], -3);
}

TEST(math3d, init3)
{
    Vector<10> v(10);
    Vector<5> vv(v);
    ASSERT_EQ(v[0], vv[0]);
    ASSERT_EQ(v[4], vv[4]);
}

TEST(math3d, at)
{
    Vector<10> v = {1, 10, 2, 9, 3, 4};
    ASSERT_EQ(v.at(0), 1);
    ASSERT_EQ(v.at(1), 10);
    ASSERT_EQ(v.at(2), 2);
    ASSERT_EQ(v.at(3), 9);
    ASSERT_EQ(v.at(4), 3);
    ASSERT_EQ(v.at(5), 4);
}

TEST(math3d, frontbackbeginend)
{
    Vector<10> v = {1, 10, 2, 9, 3, 4};
    ASSERT_EQ(v.front(), 1);
    ASSERT_EQ(v.back(), 0);

    v[9] = 5;

    ASSERT_EQ(*(v.begin()), 1);
    ASSERT_EQ(*(v.end() - 1), 5);
}

TEST(math3d, coordaccess)
{
    Vector2 v1(1);
    ASSERT_TRUE(v1.x() && v1.y());

    Vector3 v2(1);
    ASSERT_TRUE(v2.x() && v2.y() && v2.z());

    Vector4 v3(1);
    ASSERT_TRUE(v3.x() && v3.y() && v3.z() && v3.w());
}

TEST(math3d, coordchange)
{
    Vector2 v1(1);
    ASSERT_TRUE(v1.x() && v1.y());
    v1.set_y(0);
    ASSERT_FALSE(v1.x() && v1.y());

    Vector3 v2(1);
    ASSERT_TRUE(v2.x() && v2.y() && v2.z());
    v2.set_z(0);
    ASSERT_FALSE(v2.x() && v2.y() && v2.z());

    Vector4 v3(1);
    ASSERT_TRUE(v3.x() && v3.y() && v3.z() && v3.w());
    v3.set_w(0);
    ASSERT_FALSE(v3.x() && v3.y() && v3.z() && v3.w());
}

TEST(math3d, equal)
{
    Vector<10> v1(5);
    Vector<10> v2(5);
    ASSERT_TRUE(v1 == v2);
    ASSERT_TRUE(v1.FuzzyCompare(v1, v2));
    ASSERT_TRUE(v1.FuzzyCompare(v2, v1));

    Vector3 v3(3);
    Vector3 v4(4);
    ASSERT_FALSE(v3 == v4);
    ASSERT_FALSE(v3.FuzzyCompare(v3, v4));
    ASSERT_FALSE(v4.FuzzyCompare(v4, v3));
}

TEST(math3d, isnull)
{
    Vector<10> v1(0);
    ASSERT_TRUE(v1.IsNull());

    Vector2 v2(1);
    ASSERT_FALSE(v2.IsNull());
}

TEST(math3d, isnormal)
{
    Vector2 v1 = {0, 1};
    ASSERT_TRUE(v1.IsNormalized());

    Vector<5> v2 = {0, 1, 2, 3};
    ASSERT_FALSE(v2.IsNormalized());
}

TEST(math3d, length)
{
    Vector2 v1 = {0, 1};
    ASSERT_TRUE(v1.length() == 1);

    Vector2 v2 = {3, 4};
    ASSERT_TRUE(v2.length() == 5);

    Vector2 v3 = {5, 12};
    ASSERT_TRUE(v3.length() == 13);

    Vector3 v4 = {1, 2, 2};
    ASSERT_TRUE(v4.length() == 3);
}

TEST(math3d, vectorcross)
{
    Vector3 v1 = {2, 1, -3};
    Vector3 v2 = {0, -1, 1};
    Vector3 vres = v1.CrossProduct(v1, v2);

    Vector3 right = {-2, -2, -2};
    ASSERT_TRUE(vres == right);
}

TEST(math3d, mathvector)
{
    Vector3 v1 = {2, 1, -3};
    Vector3 v2 = {0, -1, 1};
    Vector3 vres1 = {2, 0, -2};
    ASSERT_TRUE(vres1 == (v1 + v2));

    Vector3 vres2 = {2, 2, -4};
    ASSERT_TRUE(vres2 == (v1 - v2));

    Vector3 vres3 = {-2, -2, 4};
    ASSERT_TRUE(vres3 == (v2 - v1));
}

TEST(math3d, normalizing)
{
    Vector3 v1 = {2, 1, -3};
    ASSERT_TRUE(v1.Normalized().IsNormalized());
}
