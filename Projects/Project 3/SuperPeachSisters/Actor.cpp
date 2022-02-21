//
// CS 32 Project 3
// Naman Modani
// Actor.cpp
//

#include "Actor.h"
#include "StudentWorld.h"
using namespace std;

Actor::Actor(StudentWorld* sw, int imageID, int x, int y, int dir, int depth, double size, bool is_alive)
:GraphObject(imageID, x * SPRITE_WIDTH, y * SPRITE_HEIGHT)
{
    m_ID = imageID;
    m_alive = is_alive;
}

bool Actor::is_alive()
{
    if (m_alive)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Actor::~Actor() {}

Peach::Peach(StudentWorld* sw, int x, int y): Actor(sw, IID_PEACH, x, y, 0, 0, 1, true),
                                                    m_world(sw)
{
    int health_point = 1;
}

void Peach::doSomething()
{
    int key;
    if (m_world->getKey(key))
    {
        switch(key)
        {
            case KEY_PRESS_LEFT:
                if(getDirection() == left && !(m_world->isBlockingObjectAt(getX() - 4, getY())))
                    moveTo(getX() - 4, getY());
                else if(m_world->isBlockingObjectAt(getX() - 4, getY()))
                    m_world->playSound(SOUND_PLAYER_BONK);
                else if(!(getDirection() == left))
                    setDirection(left);
                break;

            case KEY_PRESS_RIGHT:
                if(getDirection() == right && !(m_world->isBlockingObjectAt(getX() + 4, getY())))
                    moveTo(getX() + 4, getY());
                else if(m_world->isBlockingObjectAt(getX() + 4, getY()))
                    m_world->playSound(SOUND_PLAYER_BONK);
                else if(!(getDirection() == right))
                    setDirection(right);
                break;

            default:
                break;
        }
    }
}

void Peach::bonked() {}
Peach::~Peach() {}

Block::Block(StudentWorld* sw, int x, int y, bool goodie_released = false)
:Actor(sw, IID_BLOCK, x, y, 0, 2, 1, true), m_world(sw)
{
    int goodie = 0;
    m_goodie = goodie;
}

void Block::bonked()
{
    if (m_goodie == 0)
    {
        getWorld()->playSound(SOUND_PLAYER_BONK);
    }
}

void Block::doSomething() {}
Block::~Block() {}