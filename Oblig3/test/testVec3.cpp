# include <iostream>
# include <cmath>
# include "gtest/gtest.h"
# include "../src/vec3.h"

TEST(Constructors, Vec3) {
    vec3 nonNullVec (3.0, 2.0, 3.0);

    ASSERT_EQ(3.0, nonNullVec.x());
    ASSERT_EQ(2.0, nonNullVec.y());
    ASSERT_EQ(3.0, nonNullVec.z());
}

TEST(Operators, vec3) {
    vec3 lhs (3.0, 2.0, 3.0);
    vec3 rhs (-5.0, 2.0, 3.0);

    vec3 add = lhs + rhs;

    ASSERT_EQ(add.x(), lhs.x() + rhs.x());
    ASSERT_EQ(add.y(), lhs.y() + rhs.y());
    ASSERT_EQ(add.z(), lhs.z() + rhs.z());

    vec3 sub = lhs - rhs;

    ASSERT_EQ(sub.x(), lhs.x() - rhs.x());
    ASSERT_EQ(sub.y(), lhs.y() - rhs.y());
    ASSERT_EQ(sub.z(), lhs.z() - rhs.z());

    double dot = lhs.dot(rhs);

    ASSERT_EQ(dot, lhs.x() * rhs.x() + lhs.y() * rhs.y() + lhs.z() * rhs.z());

    vec3 aAM = lhs;
    aAM.addAndMultiply(rhs, 2.0);

    ASSERT_EQ(aAM.x(), lhs.x() + rhs.x()*2.0);
    ASSERT_EQ(aAM.y(), lhs.y() + rhs.y()*2.0);
    ASSERT_EQ(aAM.y(), lhs.y() + rhs.y()*2.0);

    vec3 aDD = lhs;
    aDD.add(rhs);

    ASSERT_EQ(aDD.x(), lhs.x() + rhs.x());
    ASSERT_EQ(aDD.y(), lhs.y() + rhs.y());
    ASSERT_EQ(aDD.y(), lhs.y() + rhs.y());

    vec3 crs = lhs.cross(rhs);
    
    ASSERT_EQ(crs.x(), lhs.y() * rhs.z() - lhs.z() * rhs.y());
    ASSERT_EQ(crs.y(), lhs.z() * rhs.x() - lhs.x() * rhs.z());
    ASSERT_EQ(crs.z(), lhs.x() * rhs.y() - lhs.y() * rhs.x());

    double nor = lhs.norm();

    ASSERT_EQ(nor, sqrt(lhs.x() * lhs.x() + lhs.y() * lhs.y() + lhs.z() * lhs.z()));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
