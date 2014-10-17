# pragma once
# ifndef __PLANETLIST_H_INCLUDED__
# define __PLANETLIST_H_INCLUDED__
# include <iostream>
# include "Planet.h"
# include "vec3.h"

class PlanetList {
    
    public:

        Planet *first;
        Planet *last;
        int numberOfPlanets;

        


        PlanetList() {
            std::string head = "Listhead";
            vec3 null = vec3();
            Planet lh (head, (double) 0, &null, &null);
            first = &lh;
            last = &lh;
            numberOfPlanets = 0;
        }




        void insertFirst(Planet *newPlanet) {
            (*newPlanet).next = (*first).next;
            (*first).next = newPlanet;
            if ((*last).next == newPlanet) last = newPlanet; // newPlanet is last.
            numberOfPlanets++;
        }




        void insertLast(Planet *newPlanet) {
            (*last).next = newPlanet;
            last = newPlanet;
            numberOfPlanets++;
        }




        void insertBehind(Planet *thisOne, Planet *newPlanet) {
            if ((*thisOne).next != NULL) {
                (*newPlanet).next = (*thisOne).next;
                (*thisOne).next = newPlanet;
            }
            if ((*last).next == newPlanet) {
                last = newPlanet; // newPlanet is last.
                numberOfPlanets++;
            } else insertLast(newPlanet);
        }




        Planet getPlanet(std::string n) {
            Planet p = *(*first).next;
            for (int i = numberOfPlanets; i > 0; i--) {
                // String equality?
                if (p.name == n) return p;
                else p = *p.next;
            }
            return p;
        }
};

# endif // PLANETLIST_H
