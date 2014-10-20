# include "CBList.h"
# include <iostream>

CBList::CBList() {
    std::string head = "Listhead";
    vec3 null (0.0, 0.0, 0.0);
    CelestialBody lh (head, (double) 0, null, null);
    this->first = &lh;
    this->last = &lh;
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
    CelestialBody *p = (*first).next;
    for (int i = numberOfBodies; i > 0; i--) {
        if ((*p).name == n) return p;
        else p = (*p).next;
    }
    return p;
}
