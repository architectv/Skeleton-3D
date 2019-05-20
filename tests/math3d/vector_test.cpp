#include "gtest/gtest.h"

#include "math3d/vector4.h"

#include <iostream>
#include <iomanip>

TEST(math3d, init) {
  Vector<10, int> v = {1, 2, 3, 4, 5};
  ASSERT_EQ(v[0], 1);
  ASSERT_EQ(v[1], 2);
  ASSERT_EQ(v[2], 3);
  ASSERT_EQ(v[3], 4);
  ASSERT_EQ(v[4], 5);
  ASSERT_EQ(v[5], 0);
}

TEST(math3d, init2) {
  Vector<10, int> v(-3);
  ASSERT_EQ(v[0], -3);
  ASSERT_EQ(v[1], -3);
  ASSERT_EQ(v[9], -3);
}

TEST(math3d, init3) {
  Vector<10, int> v(10);
  Vector<5, int> vv(v);
  ASSERT_EQ(v[0], vv[0]);
  ASSERT_EQ(v[4], vv[4]);
}

TEST(math3d, at) {
  Vector<10, int> v = {1, 10, 2, 9, 3, 4};
  ASSERT_EQ(v.at(0), 1);
  ASSERT_EQ(v.at(1), 10);
  ASSERT_EQ(v.at(2), 2);
  ASSERT_EQ(v.at(3), 9);
  ASSERT_EQ(v.at(4), 3);
  ASSERT_EQ(v.at(5), 4);
}

TEST(math3d, frontbackbeginend) {
  Vector<10, int> v = {1, 10, 2, 9, 3, 4};
  ASSERT_EQ(v.front(), 1);
  ASSERT_EQ(v.back(), 0);

  v[9] = 5;

  ASSERT_EQ(*(v.begin()), 1);
  ASSERT_EQ(*(v.end() - 1), 5);
}

TEST(math3d, coordaccess) {
  Vector2i v1(1);
  ASSERT_TRUE(v1.x() && v1.y());

  Vector3i v2(1);
  ASSERT_TRUE(v2.x() && v2.y() && v2.z());

  Vector4i v3(1);
  ASSERT_TRUE(v3.x() && v3.y() && v3.z() && v3.w());
}

TEST(math3d, coordchange) {
  Vector2i v1(1);
  ASSERT_TRUE(v1.x() && v1.y());
  v1.y() = 0;
  ASSERT_FALSE(v1.x() && v1.y());

  Vector3i v2(1);
  ASSERT_TRUE(v2.x() && v2.y() && v2.z());
  v2.z() = 0;
  ASSERT_FALSE(v2.x() && v2.y() && v2.z());

  Vector4i v3(1);
  ASSERT_TRUE(v3.x() && v3.y() && v3.z() && v3.w());
  v3.w() = 0;
  ASSERT_FALSE(v3.x() && v3.y() && v3.z() && v3.w());
}

TEST(math3d, equal) {
  Vector<10, float> v1(5);
  Vector<10, float> v2(5);
  ASSERT_TRUE(v1 == v2);
  ASSERT_TRUE(FuzzyCompare(v1, v2));
  ASSERT_TRUE(FuzzyCompare(v2, v1));

  Vector3f v3(3);
  Vector3f v4(4);
  ASSERT_FALSE(v3 == v4);
  ASSERT_FALSE(FuzzyCompare(v3, v4));
  ASSERT_FALSE(FuzzyCompare(v4, v3));
}

TEST(math3d, isnull) {
  Vector<10, int> v1(0);
  ASSERT_TRUE(v1.IsNull());

  Vector2i v2(1);
  ASSERT_FALSE(v2.IsNull());
}

TEST(math3d, isnormal) {
  Vector2f v1 = {0, 1};
  ASSERT_TRUE(v1.IsNormalized());

  Vector<5, float> v2 = {0, 1, 2, 3};
  ASSERT_FALSE(v2.IsNormalized());
}

TEST(math3d, length) {
  Vector2i v1 = {0, 1};
  ASSERT_TRUE(v1.length() == 1);

  Vector2i v2 = {3, 4};
  ASSERT_TRUE(v2.length() == 5);

  Vector2i v3 = {5, 12};
  ASSERT_TRUE(v3.length() == 13);

  Vector3i v4 = {1, 2, 2};
  ASSERT_TRUE(v4.length() == 3);
}

TEST(math3d, vectorcross) {
  Vector3i v1 = {2, 1, -3};
  Vector3i v2 = {0, -1, 1};
  Vector3i vres = Vector3i::CrossProduct(v1, v2);

  Vector3i right = {-2, -2, -2};
  ASSERT_TRUE(vres == right);
}

TEST(math3d, mathvector) {
  Vector3i v1 = {2, 1, -3};
  Vector3i v2 = {0, -1, 1};
  Vector3i vres1 = {2, 0, -2};
  ASSERT_TRUE(vres1 == (v1 + v2));

  Vector3i vres2 = {2, 2, -4};
  ASSERT_TRUE(vres2 == (v1 - v2));

  Vector3i vres3 = {-2, -2, 4};
  ASSERT_TRUE(vres3 == (v2 - v1));
}

TEST(math3d, normalizing) {
  Vector3f v1 = {2, 1, -3};
  ASSERT_TRUE(v1.normalized().IsNormalized());
}