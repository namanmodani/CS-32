//
// CS 32 Project 3
// Naman Modani
// StudentWorld.cpp
//

// Import library headers
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

// Import header files
#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"

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

int StudentWorld::init()
{
    gameWinStatus = false;
    levelCompleteStatus = false;
    Level lev(assetPath());
    ostringstream oss;
    oss << "level";
    oss.fill('0');
    oss << setw(2) << getLevel() << ".txt";
    string level_file = oss.str();

    Level::LoadResult result = lev.loadLevel(level_file);
    if (result == Level::load_fail_file_not_found)
    {
        return GWSTATUS_LEVEL_ERROR;
    }
    else if (result == Level::load_fail_bad_format)
    {
        return GWSTATUS_LEVEL_ERROR;
    }
    else if (result == Level::load_success)
    {
        Level::GridEntry ge;

        for (int row = 0; row < GRID_HEIGHT; row++)
        {
            for (int col = 0; col < GRID_WIDTH; col++)
            {
                Level::GridEntry ge = lev.getContentsOf(col, row);
                switch (ge)
                {
                    case Level::empty:
                        break;
                    case Level::peach:
                        actorVector.push_back(new Peach(col * SPRITE_WIDTH, row * SPRITE_HEIGHT, this));
                        break;
                    case Level::goomba:
                        actorVector.push_back(new Goomba(col * SPRITE_WIDTH, row * SPRITE_HEIGHT, this));
                        break;
                    case Level::koopa:
                        actorVector.push_back(new Koopa(col * SPRITE_WIDTH, row * SPRITE_HEIGHT, this));
                        break;
                    case Level::piranha:
                        actorVector.push_back(new Piranha(col * SPRITE_WIDTH, row * SPRITE_HEIGHT, this));
                        break;
                    case Level::block:
                        actorVector.push_back(new Block(col * SPRITE_WIDTH, row * SPRITE_HEIGHT, this));
                        break;
                    case Level::star_goodie_block:
                        actorVector.push_back(new Block(col * SPRITE_WIDTH, row * SPRITE_HEIGHT, this, STAR_GOODIE));
                        break;
                    case Level::mushroom_goodie_block:
                        actorVector.push_back(new Block(col * SPRITE_WIDTH, row * SPRITE_HEIGHT, this, MUSHROOM_GOODIE));
                        break;
                    case Level::flower_goodie_block:
                        actorVector.push_back(new Block(col * SPRITE_WIDTH, row * SPRITE_HEIGHT, this, FLOWER_GOODIE));
                        break;
                    case Level::pipe:
                        actorVector.push_back(new Pipe(col * SPRITE_WIDTH, row * SPRITE_HEIGHT, this));
                        break;
                    case Level::flag:
                        actorVector.push_back(new Flag(col * SPRITE_WIDTH, row * SPRITE_HEIGHT, this));
                        break;
                    case Level::mario:
                        actorVector.push_back(new Mario(col * SPRITE_WIDTH, row * SPRITE_HEIGHT, this));
                        break;
                }
            }
        }
    }
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    std::vector<Actor*>::iterator it = actorVector.begin();
    Actor* tempPeach = getPeach();
    for (; it != actorVector.end(); it++)
    {
        if ((*it)->isAlive() == false)
        {
            continue;
        }

        (*it)->doSomething();

        if (tempPeach->isAlive() == false)
        {
            playSound(SOUND_PLAYER_DIE);
            decLives();
            return GWSTATUS_PLAYER_DIED;
        }

        if (gameWinStatus)
        {
            playSound(SOUND_GAME_OVER);
            return GWSTATUS_PLAYER_WON;
        }

        if (levelCompleteStatus)
        {
            playSound(SOUND_FINISHED_LEVEL);
            return GWSTATUS_FINISHED_LEVEL;
        }
    }

    it = actorVector.begin();
    while (it != actorVector.end())
    {
        if ((*it)->isAlive() == false)
        {
            delete (*it);
            it = actorVector.erase(it);
        }
        else
        {
            it++;
        }
    }

    ostringstream oss;
    oss.fill(' ');
    oss << "Lives: " << setw(2) << getLives() << "  ";
    oss.fill('0');
    oss << "Level: " << setw(2) << getLevel() << "  ";
    oss.fill('0');
    oss << "Points: " << setw(6) << getScore();
    oss.fill(' ');

    if (tempPeach->useStarPower())
    {
        oss << " StarPower!";
    }
    if (tempPeach->useFlowerPower())
    {
        oss << " ShootPower!";
    }
    if (tempPeach->useJumpPower())
    {
        oss << " JumpPower!";
    }

    setGameStatText(oss.str());
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    std::vector<Actor*>::iterator it = actorVector.begin();
    while (it != actorVector.end())
    {
        delete (*it);
        it = actorVector.erase(it);
    }
}

Actor* StudentWorld::getPeach() {
    std::vector<Actor*>::iterator it = actorVector.begin();
    for (; it != actorVector.end(); it++)
    {
        if ((*it)->isPlayerControlled())
        {
            return *it;
        }
    }
    return nullptr;
}

bool StudentWorld::isOverlappingWithPeach(int x, int y)
{
    Actor* tempPeach = getPeach();
    return areOverlapping(tempPeach->getX(), tempPeach->getY(), x, y);
}

bool StudentWorld::isOverlappingWithEnemy(int x, int y)
{
    std::vector<Actor*>::iterator it = actorVector.begin();
    for (; it != actorVector.end(); it++)
    {
        if ((*it)->isDamageable() && (*it)->isPlayerControlled() == false && (*it)->isAlive())
        {
            if (areOverlapping(x, y, (*it)->getX(), (*it)->getY()))
            {
                (*it)->takeDamage();
                return true;
            }
        }
    }
    return false;
}

bool StudentWorld::isBlockingObjectAt(int x, int y)
{
    std::vector<Actor*>::iterator it = actorVector.begin();
    for (; it != actorVector.end(); it++) {
        if (areOverlapping(x, y, (*it)->getX(), (*it)->getY()))
        {
            if ((*it)->canBeOverlappedWith() == false)
            {
                return true;
            }
        }
    }

    return false;
}

bool StudentWorld::areOverlapping(int x1, int y1, int x2, int y2)
{
    int differenceX = x1 - x2;
    if (differenceX < 0)
    {
        differenceX *= -1;
    }
    int differenceY = y1 - y2;
    if (differenceY < 0)
    {
        differenceY *= -1;
    }
    if (differenceX < SPRITE_WIDTH && differenceY < SPRITE_HEIGHT)
    {
        return true;
    }
    return false;
}

void StudentWorld::bonkObjectsAt(int x, int y)
{
    std::vector<Actor*>::iterator it = actorVector.begin();
    for (; it != actorVector.end(); it++)
    {
        if (areOverlapping(x, y, (*it)->getX(), (*it)->getY()) && (*it)->isPlayerControlled() == false)
        {
            (*it)->bonk();
            if ((*it)->canBeOverlappedWith() == false)
            {
                return;
            }
        }
    }
}

void StudentWorld::addActor(Actor* actor)
{
    actorVector.push_back(actor);
}

void StudentWorld::gameWon()
{
    gameWinStatus = true;
    increaseScore(1000);
}

void StudentWorld::levelCompleted()
{
    levelCompleteStatus = true;
    increaseScore(1000);
}