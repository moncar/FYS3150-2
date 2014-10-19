# include <iostream>
# include <cmath>
# include "gtest/gtest.h"
# include "../src/CelestialBody.h"
# include "../src/vec3.h"

TEST(ParameterInitialization, Celest) {
    std::string name = "TestPlanet";
    double mass = 1.0e+24;
    vec3 r (0.0, 0.0, 0.0);
    vec3 v (0.0, 0.0, 0.0);
    CelestialBody cb (name, mass, &r, &v);
    ASSERT_EQ(name, cb.name);
    ASSERT_EQ(mass, cb.mass);
    ASSERT_EQ(r.x(), (cb.r)->x());
    ASSERT_EQ(v.x(), (cb.v)->x());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
