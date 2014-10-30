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

    // First iteration.
    // Remember to update which body you are using.
    CelestialBody *cb = bodies.first->next;
    for (int i = 0; i < numberOfBodies; i++) {
        (*cb).file.open("../RESULTS/Verlet" + cb->name + ".txt");
        // Check whether or not this has updated cb->r.
        (*cb).prevR = (*cb).r;
        cb->r.addAndMultiply(cb->v, dt);
        cb->r.addAndMultiply(cb->a, 0.5*dt*dt);
        if (cb->file.is_open()) {
            cb->file << 0 << "\t" << cb->prevR << "\n";
            cb->file << dt << "\t" << cb->r << "\n";
        } else std::cout << "Unable to write to file." << std::endl;
    }

    // Verlet integration.
    for (int i = 2; i < N; i++) {
        for (int j = 0; j < numberOfBodies; j++) {
            (*cb).prevR = (*cb).r;
            cb->r*2;
            cb->r - cb->prevR;
            cb->r.addAndMultiply(cb->a, dt*dt);
            if (cb->file.is_open()) {
                cb->file << i*dt << "\t" << cb->r << "\n";
            } else std::cout << "Unable to write to file." << endl;
        }
    }
    for (int i = 0; i < numberOfBodies; i++) {
        // Close files
    }
}

void SolarSystem::RK4() {
    vec3 K1;
    vec3 K2;
    vec3 K3;
    vec3 K4;
    CelestialBody *cb = bodies.first->next;

    //Runge-Kutta 4 integration.
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < numberOfBodies; j++) {
            (*cb).prevV = (*cb).v;
            // Carefull...
            // Does this change the values of the K's downwards?
            K1 = cb->a;
            cb->a.addAndMultiply(K1, 0.5*dt);
            K2 = cb->a;
            cb->a.addAndMultiply(K2, 0.5*dt);
            K3 = cb->a;
            cb->a.addAndMultiply(K3, dt);
            K4 = cb->a;
            cb->v.addAndMultiply(K1, dt/6.0);
            cb->v.addAndMultiply(K2, dt/3.0);
            cb->v.addAndMultiply(K3, dt/3.0);
            cb->v.addAndMultiply(K4, dt/6.0);

            (*cb).prevR = (*cb).r;
            K1 = cb->prevV;
            cb->prevV.addAndMultiply(K1, 0.5*dt);
            K2 = cb->prevV;
            cb->prevV.addAndMultiply(K2, 0.5*dt);
            K3 = cb->prevV;
            cb->prevV.addAndMultiply(K3, dt);
            K4 = cb->prevV;
            cb->r.addAndMultiply(K1, dt/6.0);
            cb->r.addAndMultiply(K2, dt/3.0);
            cb->r.addAndMultiply(K3, dt/3.0);
            cb->r.addAndMultiply(K4, dt/6.0);
            if (cb->file.is_open()) {
                cb->file << i*dt << "\t" << cb->r << "\n";
            } else std::cout << "Unable to write to file." << endl;
        }
    }
}

