//
// CS 32 Project 3
// Naman Modani
// Actor.h
//

#ifndef ACTOR_H
#define ACTOR_H

#include "GraphObject.h"

class StudentWorld;

class Actor: public GraphObject
{
public:
    Actor(StudentWorld* sw, int imageID, int x, int y, int dir, int depth, double size, bool is_alive);
    virtual ~Actor();

    virtual void doSomething() = 0;
    virtual void bonk() = 0;

    StudentWorld* getWorld()
    {
        return m_world;
    }

    void setTick(int tick)
    {
        m_tick = tick;
    }
    void setDead()
    {
        m_alive = false;
    }

    int getTick()
    {
        return m_tick;
    }
    int getImageID()
    {
        return m_ID;
    }

    bool is_Alive();

private:
    int m_tick;
    int m_ID;
    int m_alive;
    StudentWorld* m_world;
};

class Peach: public Actor
{
public:
    Peach(StudentWorld* sw, int x, int y);
    virtual ~Peach();

    virtual void doSomething();
    virtual void bonk();

    int getHP()
    {
        return m_HP;
    }

    void getInviciblility()
    {
        m_Invincibility = true;
    }

    void getStarPower()
    {
        m_StarPower = true;
    }

    void getShootPower()
    {
        m_ShootPower = true;
    }

    void getSuperJumpPower()
    {
        m_SuperJumpPower = true;
    }

    bool hasInvincibility()
    {
        return m_Invincibility;
    }

    bool hasStarPower()
    {
        return m_StarPower;
    }

    bool hasShootPower()
    {
        return m_ShootPower;
    }

    bool hasSuperJumpPower()
    {
        return m_SuperJumpPower;
    }

private:
    int m_HP;
    bool m_Invincibility;
    bool m_StarPower;
    bool m_ShootPower;
    bool m_SuperJumpPower;
    StudentWorld* m_world;
};

class Block: public Actor
{
public:
    Block(StudentWorld* sw, int x, int y, bool goodie_released);
    virtual ~Block();

    virtual void doSomething();
    virtual void bonk();

private:
    int m_goodie;
    bool m_goodie_released;
    StudentWorld* m_world;
};

#endif //ACTOR_H