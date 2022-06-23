// myapp.cpp

#include "Circle.h"
#include <iostream>
using namespace std;

int main()
{
    Circle c(-2, 5, 10);
    c.scale(2);
    c.draw();
    cout << area(c);
}