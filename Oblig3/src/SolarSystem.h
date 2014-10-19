# pragma once
# ifndef __SOLARSYSTEM_H_INCLUDED__
# define __SOLARSYSTEM_H_INCLUDED__
# include <fstream>
# include <iostream>
# include "vec3.h"
# include "CelestialBody.h"
# include "CBList.h"

class SolarSystem {

    public:

        int numberOfBodies;
        double dt;
        int time;
        int N = (int) (time/dt);
        CBList bodies;

        SolarSystem(int NOB, CBList b, double delta, int t) {
            numberOfBodies = NOB;
            bodies = b;
            dt = delta;
            time = t;
        }

        void calculateForce() {

        }
        

}

# endif // SOLARSYSTEM_H
