//
// CS 32 Homework 1
// Naman Modani
// CarMap.cpp
//

#include "CarMap.h"
#include <iostream>

using namespace std;

CarMap::CarMap() {}

bool CarMap::addCar(std::string license)
{
    return car_map.insert(license, 0);
}

double CarMap::miles(std::string license) const
{
    double milesDriven;
    if (car_map.get(license, milesDriven))
        return milesDriven;
    else
        return -1;
}

bool CarMap::drive(std::string license, double distance)
{
    double currentDistance;
    if (!car_map.get(license, currentDistance) || distance < 0)
        return false;
    else
    {
        car_map.update(license, currentDistance + distance);
        return true;
    }
}

int CarMap::fleetSize() const
{
    return car_map.size();
}

void CarMap::print() const
{
    for (int i = 0; i < car_map.size(); i++)
    {
        string license;
        double miles;
        car_map.get(i, license, miles);
        cout << license << " " << miles << endl;
    }
}