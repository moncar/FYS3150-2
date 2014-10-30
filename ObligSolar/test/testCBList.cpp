# include <iostream>
# include "gtest/gtest.h"
# include "../src/CBList.h"

TEST(Constructor, Pointers) {
    CBList cbl = CBList();
    CelestialBody *cb = cbl.first;
    CelestialBody c = *cb;
    EXPECT_EQ("Listhead", c.name);
    std::cout << "YO" << std::endl;
    cb = cbl.last;
    EXPECT_EQ("Listhead", (*cb).name);
    EXPECT_EQ(0, cbl.numberOfBodies);

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
