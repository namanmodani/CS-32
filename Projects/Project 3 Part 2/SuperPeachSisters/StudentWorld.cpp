//
// CS 32 Project 3
// Naman Modani
// StudentWorld.cpp
//

// Import library headers
#include <iostream>
#include <vector>
#include <string>

// Import header files
#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include "Level.h"

using namespace std;

class GameWorld;
class Peach;

GameWorld* createStudentWorld(string assetPath)
{
    return new StudentWorld(assetPath);
}

// Constructor
StudentWorld::StudentWorld(string assetPath): GameWorld(assetPath)
{}

// Destructor
StudentWorld::~StudentWorld()
{
    cleanUp();
}

// Loader of data from "LEVELXY.TXT"
int StudentWorld::init()
{
    Level lev(assetPath());
    string level_file = "level0" + to_string(getLevel()) + ".txt";
    Level::LoadResult result = lev.loadLevel(level_file);

    if(result == Level::load_success)
    {
        cerr << level_file << ": Successfully loaded!" << endl;
        Level::GridEntry ge;

        for (int x = 0; x < GRID_WIDTH; x++)
        {
            for (int y = 0; y < GRID_HEIGHT; y++)
            {
                ge = lev.getContentsOf(x, y);
                switch (ge)
                {
                    case Level::empty:
                        break;
                    case Level::peach:
                        m_peach = new Peach(this, x, y);
                        break;
                    case Level::block:
                        actors.push_back(new Block(this, x, y, false));
                        break;
                    default:
                        break;
                }
            }
        }
    }
    return GWSTATUS_CONTINUE_GAME;
}

// Call Actors to doSomething()
int StudentWorld::move()
{
    m_peach->doSomething();
    for(vector<Actor*>::iterator it = actors.begin(); it != actors.end(); ++it)
    {
        if ((*it)->is_Alive())
        {
            (*it)->doSomething();
        }
    }
    return GWSTATUS_CONTINUE_GAME;
}

// Avoid dangling pointers or memory leaks
void StudentWorld::cleanUp()
{
    delete m_peach;
    m_peach = nullptr;

    while(!actors.empty())
    {
        delete actors[0];
        actors[0] = nullptr;
        actors.erase(actors.begin());
    }
}

// Check actor overlap with other objects
bool StudentWorld::isBlockingObjectAt(double x, double y)
{
    for(Actor* a: actors) {
        if (x + SPRITE_WIDTH - 1 > a->getX() && x < a->getX() + SPRITE_WIDTH - 1)
            if (y + SPRITE_HEIGHT - 1 > a->getY() && y < a->getY() + SPRITE_HEIGHT - 1)
                return true;
    }
    return false;
}