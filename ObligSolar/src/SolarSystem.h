# ifndef __SOLARSYSTEM_H_INCLUDED__
# define __SOLARSYSTEM_H_INCLUDED__
# include <iostream>
# include "CBList.h"

class SolarSystem {

    public:

        int numberOfBodies;
        double dt;
        int time;
        int N = (int) (time/dt);
        CBList bodies;

        SolarSystem(int NOB, CBList b, double delta, int t);
        void calculateForce();
        void verlet();
        void RK4();
        

};

# endif // SOLARSYSTEM_H
