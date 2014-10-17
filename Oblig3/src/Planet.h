# pragma once
# ifndef __PLANET_H_INCLUDED__
# define __PLANET_H_INCLUDED__
# include <iostream>
# include <fstream>

class vec3;

class Planet {

    public:

        std::string name; // Name of planet, used when naming file.
	    double mass; // Mass of planet.
        vec3 *r; // Pointer to current position of planet.
        vec3 *prevR; // Previous position of planets, needed in Verlet.
		vec3 *v; // Current velocity of planet.
		vec3 *a; // Current acceleration of planet.
        // The force should probably be calculated in the SolarSystem-class due to overview.
		vec3 *F; // Current force on planet.
        std::ofstream file;

        Planet *next;
        Planet *temp;

        Planet(std::string n, double m, vec3 *r0, vec3 *v0);

        void calculateNewForce();

};

# endif // PLANET_H
