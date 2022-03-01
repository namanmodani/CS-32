// Circle.cpp

#include "Circle.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

Circle::Circle(double x, double y, double r)
        : m_x(x), m_y(y), m_r(r)
{
    if (r <= 0)
    {
        cerr << "Cannot create a circle of radius " << r << endl;
        exit(1);
    }
}

void Circle::draw() const
{
    ... draw the circle ...
}

bool Circle::scale(double factor)
{
    if (factor <= 0)
        return false;
    m_r *= factor;
    return true;
}

double Circle::radius() const
{
    return m_r;
}

double area(const Circle& circ)
{
    const double PI = 4 * atan(1.0);
    return PI * circ.radius() * circ.radius();
}