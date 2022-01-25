//
// CS 32 Homework 1
// Naman Modani
// testCarMap.cpp
//

#include "CarMap.h"
#include <iostream>
#include <cassert>
using namespace std;

int main() {
    CarMap carMap;
    assert(carMap.addCar("Toucan"));
    assert(carMap.fleetSize() == 1);

    assert(!carMap.addCar("Toucan"));
    assert(carMap.addCar("Gallardo"));
    assert(carMap.fleetSize() == 2);

    assert(!carMap.addCar("Toucan"));
    assert(!carMap.addCar("Gallardo"));
    assert(carMap.addCar(""));
    assert(carMap.fleetSize() == 3);

    assert(!carMap.drive("Agera", 13));
    assert(carMap.drive("Toucan", 0));
    assert(!carMap.drive("Agera", -13));
    assert(!carMap.drive("Gallardo", -100));
    assert(!carMap.drive("Toucan", -100));
    assert(carMap.drive("Toucan", 100));
    assert(carMap.drive("Gallardo", 19));
    assert(carMap.drive("Gallardo", 15));
    assert(carMap.drive("", 21));
    
    assert(abs(carMap.miles("Toucan") - 100) < 0.000001);
    assert(abs(carMap.miles("Gallardo") - 34) < 0.000001);
    assert(abs(carMap.miles("") - 21) < 0.000001);
    assert(abs(carMap.miles("Agera") + 1) < 0.000001);

    assert(carMap.fleetSize() == 3);
    cout << "Passed all tests" << endl;
}