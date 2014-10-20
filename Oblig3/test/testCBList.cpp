# include <iostream>
# include "gtest/gtest.h"
# include "../src/CBList.h"

TEST(Constructor, Pointers) {
    CBList cbl ();
    CelestialBody cb = cbl->first;
    EXPECT_EQ("Listhead", cbl->first.name);
    EXPECT_EQ("Listhead", *(cbl.last).name);
    EXPECT_EQ(0, cbl.numberOfBodies);

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
