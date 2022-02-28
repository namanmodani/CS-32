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

    virtual int init();
    virtual int move();
    virtual void cleanUp();

    Actor* getPeach();

    bool isBlockingObjectAt(int x, int y);
    bool isOverlappingWithPeach(int x, int y);
    bool isOverlappingWithEnemy(int x, int y);
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