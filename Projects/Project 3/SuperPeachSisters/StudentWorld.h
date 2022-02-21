//
// CS 32 Project 3
// Naman Modani
// StudentWorld.h
//

#ifndef STUDENTWORLD_H
#define STUDENTWORLD_H

#include "GameWorld.h"
#include "Level.h"
#include "Actor.h"
#include <string>
#include <vector>
#include <cmath>
using namespace std;

class Actor;
class Peach;
class Block;

class StudentWorld: public GameWorld
{
public:
    StudentWorld(string assetPath);
    ~StudentWorld();

    virtual int init();
    virtual int move();
    virtual void cleanUp();

    bool isBlockingObjectAt(double x, double y);

private:
    vector<Actor*> actors;
    Peach* m_peach;
};

#endif //STUDENTWORLD_H