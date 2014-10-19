# ifndef __CBLIST_H_INCLUDED__
# define __CBLIST_H_INCLUDED__
# include <iostream>
# include "CelestialBody.h"
# include "vec3.h"

class CBList {
    
    public:

        CelestialBody* first;
        CelestialBody* last;
        int numberOfBodies;

        CBList();
        void insertFirst(CelestialBody* newBody);
        void insertLast(CelestialBody* newBody);
        void insertBehind(CelestialBody* thisOne, CelestialBody* newBody);
        CelestialBody* getBody(std::string n);
};

# endif // PLANETLIST_H
