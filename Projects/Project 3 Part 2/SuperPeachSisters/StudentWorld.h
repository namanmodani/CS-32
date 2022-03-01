//
// CS 32 Project 3
// Naman Modani
// StudentWorld.h
//

#ifndef STUDENTWORLD_H
#define STUDENTWORLD_H

#include "GameWorld.h"
#include "Level.h"
#include <string>
#include <vector>
using namespace std;

class Actor;

class StudentWorld: public GameWorld
{
public:
    StudentWorld(string assetPath);
    ~StudentWorld();

    // Initializes each level - game start, new level, restart level
    virtual int init();
    // 20x per second, update game actors, introduce new actors, delete actors
    virtual int move();
    // Current level, loses a life, frees all actors
    virtual void cleanUp();

    Actor* getPeach();

    // x and y are pixel coordinates
    bool isBlockingObjectAt(int x, int y);
    bool overlapsWithPeach(int x, int y);
    bool overlapsWithEnemy(int x, int y);
    void bonkObjectsAt(int x, int y);
    void addActor(Actor* actor);
    void gameWon();
    void levelCompleted();

private:
    vector<Actor*> actorVector;
    bool gameWinStatus;
    bool levelCompleteStatus;
    bool areOverlapping(int x1, int y1, int x2, int y2);
};

#endif // STUDENTWORLD_H