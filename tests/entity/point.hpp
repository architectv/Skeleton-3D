#include "../../tests/gtest/gtest.h"
#include "../../entity/point.hpp"

TEST(Point, simplest) {
    Point p;
}

TEST(Point, constr1) {
    Point p;

    EXPECT_TRUE(p == { 0, 0, 0 });
}

TEST(Point, constr2) {
    Point p(1, -2, 3);

    EXPECT_TRUE(p1 == { 1, -2, 3 });
}

TEST(Point, constr3) {
    Point p1;
    Point p2(p1);

    EXPECT_TRUE(p1 == p2);
}

TEST(Point, constr4) {
    Point p1 { 1, -2, 3 };
    Point p2(1, -2, 3);

    EXPECT_TRUE(p1 == p2);
}

TEST(Point, move) {
    Point p(1, -2, 3);
    p.Move(5, 6, 7);

    EXPECT_TRUE(p == { 6, 4, 10 });
}

TEST(Point, rotate) {
    Point p(1, -2, 3);
    p.Rotate({ 0, 0, 0 }, 90, 90, 90);

    EXPECT_TRUE(p == { 3, -2, -1 });
}

TEST(Point, scale) {
    Point p(1, -2, 3);
    p.Scale({ 0, 0, 0 }, 3, 3, 3);

    EXPECT_TRUE(p == { 3, -6, 9 });
}
