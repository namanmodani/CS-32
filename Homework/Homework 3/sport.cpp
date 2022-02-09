//
// CS 32 Homework 3
// Naman Modani
// sport.cpp
//

#include <iostream>
#include <string>
using namespace std;

Your declarations and implementations would go here

void display(const Sport* sp)
{
    cout << sp->name() << " is ";
    if (sp->isOutdoor())
        cout << "an outdoor sport ";
    else
        cout << "an indoor sport ";
    cout << "with an icon showing " << sp->icon() << "." << endl;
}

int main()
{
    Sport* sports[4];
    sports[0] = new Snowboarding("Women's halfpipe");
    // Biathlon events have a distance in kilometers
    sports[1] = new Biathlon("Men's pursuit", 12.5);
    sports[2] = new Biathlon("Women's sprint", 7.5);
    sports[3] = new FigureSkating("Pair skating free");

    cout << "Here are the sports." << endl;
    for (int k = 0; k < 4; k++)
        display(sports[k]);

    // Clean up the sports before exiting
    cout << "Cleaning up." << endl;
    for (int k = 0; k < 4; k++)
        delete sports[k];
}