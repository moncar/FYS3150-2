# include <armadillo>
# include <iostream>
# include <cmath>

using namespace std;
using namespace arma;


class Planet {

    public:

        string name; // Name of planet, used when naming file.
	    double m; // Mass of planet.
		vec r; // Current position of planet.
        vec prevR; // Previous position of planets, needed in Verlet.
		vec v; // Current velocity of planet.
		vec a; // Current acceleration of planet.

        // The force should probably be calculated in the SolarSystem-class due to overview.
		vec F; // Current force on planet.

        void calculateNewForce(Planet thisOne, vec planets); // Calculate force from all planets. Use vec planets to find all forces needed.
        // Use this to find the new acceleration.

};
