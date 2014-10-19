# ifndef __CELESTIALBODY_H_INCLUDED__
# define __CELESTIALBODY_H_INCLUDED__
# include <iostream>
# include <fstream>

class vec3;

class CelestialBody {

    public:

        std::string name; // Name of body, used when naming file.
        double mass; // Mass of body.
        vec3* r; // Pointer to current position of body.
        vec3* prevR; // Previous position of body, needed in Verlet.
        vec3* v; // Current velocity of body.
        vec3* a; // Current acceleration of body.
        // The force should probably be calculated in the SolarSystem-class due to overview.
        vec3* F; // Current force on body.
        std::ofstream file;

        CelestialBody* next;
        CelestialBody* temp;

        CelestialBody(std::string n, double m, vec3* r0, vec3* v0);
        void calculateNewForce();

};

# endif // CELESTIALBODY_H
