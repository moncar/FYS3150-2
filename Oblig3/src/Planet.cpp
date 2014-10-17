# include "Planet.h"

Planet::Planet(std::string n, double m, vec3 *r0, vec3 *v0) {
    name = n;
    mass = m;
    r = r0;
    v = v0;
}

void Planet::calculateNewForce() {

}

int main() {return 0;}
