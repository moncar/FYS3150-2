# include <armadillo>
# include <iostream>
# include <cmath>

using namespace std;
using namespace arma;


class Planet {

    public:

	    double m; // Mass of planet.
		vec r; // Current position of planet.
		vec v; // Current velocity of planet.
		vec a; // Current acceleration of planet.

        // The force should probably be calculated in the SolarSystem-class due to overview.
		vec F; // Current force on planet.

};
