# include <iostream>
# include <fstream>
# include <cmath>

using namespace std;

class SolarSystem {

    public:
        int numberOfPlanets;
        int dt; // Timestep.
        int time; // Amount of time.
        int N = int(time/((double) dt)); // Calculating number of timesteps.
        vec T = zeros<vec>(N);

        vec planets; // Array containing the planets of the solar system.

        // Constructor creating and adding all the parameters needed.
        SolarSystem(int NOP, int timestep, int t) {
            numberOfPlanets = NOP;
            planets = zeros<Planet>(NOP); // Find out how to initialize this properly.
            dt = timestep;
            time = t;
        }

        void verlet() {

            vec newPosition;
            vec files = zeros<ofstream>(numberOfPlanets); // This might also be wrong.

            T[1] = T[0] + dt;
            // First iteration.
            for (int i = 0; i < numberOfPlanets; i++) {
                files[i]("../RESULTS/Verlet" + p.name + ".txt");
                newPosition = planets[i].r + planets[i].v*dt + 0.5*planets[i].a*dt*dt;
                planets[i].prevR = planets[i].r;
                planets[i].r = newPosition;
                if (files[i].is_open()) {
                    files[i] << T[0] << "\t" << planets[i].prevR << "\n";
                    files[i] << T[1] << "\t" << planets[i].r << "\n";
                } else cout << "Unable to write to file." << endl;
                planets[i].calculateNewForce(planets[i], planets); // Needs to be implemented.
            }

            // Verlet integration.
            for (int i = 2; i < N; i++) {
                for (int j = 0; j < numberOfPlanets; j++) {
                    newPosition = 2*planets[j].r - planets[j].prevR + planets[j]*dt*2;
                    planets[j].prevR = planets[j].r;
                    planets[j].r = newPosition;
                    if (files[j].is_open()) {
                        files[j] << T[i] << "\t" << planets[j].r << "\n";
                    } else cout << "Unable to write to file." << endl;
                }
                T[i+1] = T[i] + dt;
            }
        }
};
