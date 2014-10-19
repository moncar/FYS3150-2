# include "CelestialBody.h"
# include <iostream>

class vec3;

CelestialBody::CelestialBody(std::string n, double m, vec3* r0, vec3* v0) {
    name = n;
    mass = m;
    r = r0;
    v = v0;
}

void CelestialBody::calculateNewForce() {
    std::cout << "TUILL" << std::endl;
}

int main() {return 0;}
