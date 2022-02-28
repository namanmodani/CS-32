//
// CS 32 Project 3
// Naman Modani
// Actor.h
//

#ifndef ACTOR_H
#define ACTOR_H

#include "GraphObject.h"
#include "StudentWorld.h"

class StudentWorld;

const int PEACH_STEP = 4;
const int ENEMY_STEP = 1;
const int GOODIE_STEP = 2;
const int PROJECTILE_STEP = 2;
const int NO_GOODIE = 0;
const int STAR_GOODIE = 1;
const int FLOWER_GOODIE = 2;
const int MUSHROOM_GOODIE = 3;

class Actor: public GraphObject {
public:
    Actor(int imageID, int startX, int startY, int startDirection, int depth, StudentWorld* studentWorldPtr);
    virtual ~Actor() {}
    virtual void doSomething() = 0;
    StudentWorld* getWorld()
    {
        return m_studentWorldPtr;
    }
    bool isAlive()
    {
        return m_isAlive;
    }
    virtual bool canBeOverlappedWith()
    {
        return true;
    }
    virtual bool isPlayerControlled()
    {
        return false;
    }
    virtual bool isDamageable()
    {
        return false;
    }
    virtual void takeDamage();
    virtual void bonk()
    {
        return;
    }
    virtual void gainFlowerPower()
    {
        return;
    }
    virtual void gainJumpPower()
    {
        return;
    }
    virtual void gainStarPower()
    {
        return;
    }
    virtual bool useFlowerPower()
    {
        return false;
    }
    virtual bool useJumpPower()
    {
        return false;
    }
    virtual bool useStarPower()
    {
        return false;
    }
    void unalive()
    {
        m_isAlive = false;
    }
    void reverseDirection();
private:
    StudentWorld* m_studentWorldPtr;
    bool m_isAlive;
    bool m_hasTakenDmg;
};

class Peach: public Actor {
public:
    Peach(int startX, int startY, StudentWorld* studentWorldPtr);
    virtual ~Peach() {}
    virtual bool isPlayerControlled()
    {
        return true;
    }
    virtual bool isDamageable()
    {
        return true; 
    }
    virtual void doSomething();
    virtual void gainFlowerPower();
    virtual void gainJumpPower();
    virtual void gainStarPower();
    virtual bool useFlowerPower()
    {
        return hasFlowerPower;
    }
    virtual bool useJumpPower()
    {
        return hasJumpPower;
    }
    virtual bool useStarPower()
    {
        return hasStarPower;
    }
    virtual void takeDamage();
    virtual void bonk();
private:
    int jumpDistanceLeft;
    int rechargeTime;
    bool hasFlowerPower;
    bool hasJumpPower;
    bool hasStarPower;
    int numHitPoints;
    int tempInvincibility;
};

class Enemy: public Actor
{
public:
    Enemy(int imageID, int startX, int startY, StudentWorld* studentWorldPtr);
    virtual ~Enemy()
    {}
    virtual void doSomething() = 0;
    virtual bool canMove()
    {
        return true;
    }
    virtual bool isDamageable()
    {
        return true;
    }
    virtual void takeDamage();
    void move();
    void bonk();
private:
};

class Goomba: public Enemy
{
public:
    Goomba(int startX, int startY, StudentWorld* studentWorldPtr);
    virtual ~Goomba()
    {}
    virtual void doSomething();
private:
};

class Koopa: public Enemy
{
public:
    Koopa(int startX, int startY, StudentWorld* studentWorldPtr);
    virtual ~Koopa()
    {}
    virtual void doSomething();
    virtual void takeDamage();
private:
};

class Piranha: public Enemy
{
public:
    Piranha(int startX, int startY, StudentWorld* studentWorldPtr);
    virtual ~Piranha() {}
    virtual void doSomething();
    virtual bool canMove()
    {
        return false;
    }
private:
    int firing_delay;
};

class Terrain: public Actor
{
public:
    Terrain(int imageID, int startX, int startY, StudentWorld* studentWorldPtr);
    virtual ~Terrain() {}
    virtual void doSomething() = 0;
    virtual bool canBeOverlappedWith()
    {
        return false;
    }
    virtual void bonk();
private:
};

class Block: public Terrain
        {
public:
    Block(int startX, int startY, StudentWorld* studentWorldPtr, int hasGoodieType = NO_GOODIE);
    virtual ~Block() {}
    virtual void doSomething()
    {
        return;
    }
    virtual void bonk();
private:
    int m_hasGoodieType;
    bool m_hadGoodieReleased;
};

class Pipe: public Terrain
{
public:
    Pipe(int startX, int startY, StudentWorld* studentWorldPtr);
    virtual ~Pipe() {}
    virtual void doSomething()
    {
        return;
    }
private:
};

class Goal: public Actor
{
public:
    Goal(int imageID, int startX, int startY, StudentWorld* studentWorldPtr);
    virtual ~Goal()
    {}
    virtual void doSomething() = 0;
private:
};

class Flag: public Goal
{
public:
    Flag(int startX, int startY, StudentWorld* studentWorldPtr);
    virtual ~Flag()
    {}
    virtual void doSomething();
private:
};

class Mario: public Goal
{
public:
    Mario(int startX, int startY, StudentWorld* studentWorldPtr);
    virtual ~Mario()
    {}
    virtual void doSomething();
private:
};

class Goodie: public Actor
{
public:
    Goodie(int imageID, int startX, int startY, StudentWorld* studentWorldPtr);
    virtual ~Goodie()
    {}
    void doSomething();
    virtual void doOwnThing() = 0;
private:
};

class Flower: public Goodie
{
public:
    Flower(int startX, int startY, StudentWorld* studentWorldPtr);
    virtual ~Flower()
    {}
    virtual void doOwnThing();
private:
};

class Mushroom: public Goodie
{
public:
    Mushroom(int startX, int startY, StudentWorld* studentWorldPtr);
    virtual ~Mushroom()
    {}
    virtual void doOwnThing();
private:
};

class Star: public Goodie
{
public:
    Star(int startX, int startY, StudentWorld* studentWorldPtr);
    virtual ~Star()
    {}
    virtual void doOwnThing();
private:
};

class Projectile: public Actor
{
public:
    Projectile(int imageID, int startX, int startY, int startDirection, StudentWorld* studentWorldPtr);
    virtual ~Projectile()
    {}
    virtual void doSomething();
    virtual bool hitTarget() = 0;
    void move();
private:
};

class Shell: public Projectile
{
public:
    Shell(int startX, int startY, int startDirection, StudentWorld* studentWorldPtr);
    virtual ~Shell()
    {};
    bool hitTarget();
private:
};

class PeachFireball: public Projectile
{
public:
    PeachFireball(int startX, int startY, int startDirection, StudentWorld* studentWorldPtr);
    virtual ~PeachFireball()
    {}
    bool hitTarget();
private:
};

class PiranhaFireball: public Projectile
{
public:
    PiranhaFireball(int startX, int startY, int startDirection, StudentWorld* studentWorldPtr);
    virtual ~PiranhaFireball()
    {}
    bool hitTarget();
private:
};

#endif // ACTOR_H_