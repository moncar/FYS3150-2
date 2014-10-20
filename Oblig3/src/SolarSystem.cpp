# include "SolarSystem.h"
# include <iostream>

SolarSystem::SolarSystem(int NOB, CBList b, double delta, int t) {
    numberOfBodies = NOB;
    bodies = b;
    dt = delta;
    time = t;
}

void SolarSystem::calculateForce() {

}

void SolarSystem::verlet() {
    vec3 newPosition;

    // First iteration.
    // Remember to update which body you are using.
    CelestialBody *cb = bodies.first->next;
    for (int i = 0; i < numberOfBodies; i++) {
        (*cb).file.open("../RESULTS/Verlet" + cb->name + ".txt");
        newPosition = cb->r + cb->v + (cb->a)*(0.5*dt*dt);
        (*cb).prevR = (*cb).r;
        cb->r = newPosition;
        if (cb->file.is_open()) {
            cb->file << 0 << "\t" << cb->prevR << "\n";
            cb->file << dt << "\t" << cb->r << "\n";
        } else std::cout << "Unable to write to file." << std::endl;
    }

    // Verlet integration.
    for (int i = 2; i < N; i++) {
        for (int j = 0; j < numberOfBodies; j++) {
            newPosition = 2*(*(cb.r)) - *(cb.prevR) + (*(cb.a))*dt*dt;
            cb.prevR = cb.r;
            cb.r = &newPosition;
            if (cb.file.is_open()) {
                cb.file << i*dt << "\t" << *(cb.r) << "\n";
            } else std::cout << "Unable to write to file." << endl;
        }
    }
    for (int i = 0; i < numberOfBodies; i++) {
        // Close files
    }
}

void SolarSystem::RK4() {
    vec3 newPosition;
    vec3 newSpeed;
    vec3 K1;
    vec3 K2;
    vec3 K3;
    vec3 K4;

    //Runge-Kutta 4 integration.
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < numberOfBodies; j++) {
            K1 = *(cb.a);
            K2 = *(cb.a) + 0.5*dt*K1;
            K3 = *(cb.a) + 0.5*dt*K2;
            K4 = *(cb.a) + dt*K3;
            cb.prevV = cb.v;
            cb.v = &(dt*(K1 + 2*K2 + 2*K3 + K4)/6.0);

            K1 = *(cb.prevV);
            K2 = *(cb.prevV) + 0.5*dt*K1;
            K3 = *(cb.prevV) + 0.5*dt*K2;
            K4 = *(cb.prevV) + dt*K3;
            cb.prevR = cb.r;
            cb.r = &(dt*(K1 + 2*K2 + 2*K3 + K4)/6.0);
            if (cb.file.is_open()) {
                cb.file << i*dt << "\t" << *(cb.r) << "\n";
            } else std::cout << "Unable to write to file." << endl;
        }
    }
}

