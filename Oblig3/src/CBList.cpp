# include "CBList.h"
# include "vec3.h"
# include "CelestialBody.h"
# include <iostream>

class vec3;
class CelestialBody;

CBList::CBList() {
    std::string head = "Listhead";
    vec3* null = new vec3(0.0, 0.0, 0.0);
    CelestialBody lh (head, (double) 0, null, null);
    first = &lh;
    last = &lh;
    numberOfBodies = 0;
}

void CBList::insertLast(CelestialBody* newBody) {
    (*last).next = newBody;
    last = newBody;
    numberOfBodies++;
}

void CBList::insertFirst(CelestialBody* newBody) {
    (*newBody).next = (*first).next;
    (*first).next = newBody;
    if ((*last).next == newBody) last = newBody; // newBody is last.
    numberOfBodies++;
}

void CBList::insertBehind(CelestialBody* thisOne, CelestialBody* newBody) {
    if ((*thisOne).next != NULL) {
        (*newBody).next = (*thisOne).next;
        (*thisOne).next = newBody;
    }
    if ((*last).next == newBody) {
        last = newBody; // newBody is last.
        numberOfBodies++;
    } else insertLast(newBody);
}

CelestialBody* CBList::getBody(std::string n) {
    CelestialBody *p;
    p = (*first).next;
    for (int i = numberOfBodies; i > 0; i--) {
        if ((*p).name == n) return p;
        else p = (*p).next;
    }
    return p;
}

int main() {return 0;}
