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

// Actor Specific Constants

const int PEACH_STEP = 4;
const int ENEMY_STEP = 1;
const int GOODIE_STEP = 2;
const int PROJECTILE_STEP = 2;
const int NO_GOODIE = 0;
const int STAR_GOODIE = 1;
const int FLOWER_GOODIE = 2;
const int MUSHROOM_GOODIE = 3;

// Actor Declarations

class Actor: public GraphObject {
public:
    Actor(int imageID, int startX, int startY, int startDirection, int depth, StudentWorld* studentWorldPtr);
    virtual ~Actor() {}
    virtual void doSomething() = 0;
    StudentWorld* getWorld()
    {
        return m_studentWorld;
    }
    bool isAlive()
    {
        return m_isAlive;
    }
    virtual bool Overlappable()
    {
        // Default true
        return true;
    }
    virtual bool isPlayerControlled()
    {
        // Default false
        return false;
    }
    virtual bool isDamageable()
    {
        // Default false
        return false;
    }
    virtual void takeDamage(); // Default: call unalive() if damageable
    virtual void bonk()
    {
        // Default: do nothing
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
        // Default false
        return false;
    }
    virtual bool useJumpPower()
    {
        // Default false
        return false;
    }
    virtual bool useStarPower()
    {
        // Default false
        return false;
    }
    void unalive()
    {
        // Default false
        m_isAlive = false;
    }
    void reverseDirection();
private:
    StudentWorld* m_studentWorld;
    bool m_isAlive;
    bool m_isDamaged;
};

// Peach Declarations

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
    int hitPoints;
    int tempInvincibility;
};

// Enemy Declarations

class Enemy: public Actor
{
public:
    Enemy(int imageID, int startX, int startY, StudentWorld* studentWorldPtr);
    virtual ~Enemy()
    {}
    virtual void doSomething() = 0;
    virtual bool canMove()
    {
        // Default true
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

// Goomba Declarations

class Goomba: public Enemy
{
public:
    Goomba(int startX, int startY, StudentWorld* studentWorldPtr);
    virtual ~Goomba()
    {}
    virtual void doSomething();
private:
};

// Koopa Declarations

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

// Piranha Declarations

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

// Terrain Declarations

class Terrain: public Actor
{
public:
    Terrain(int imageID, int startX, int startY, StudentWorld* studentWorldPtr);
    virtual ~Terrain() {}
    // Keep terrain abstract since Pipe and Block have the same implementation
    virtual void doSomething() = 0;
    virtual bool Overlappable()
    {
        return false;
    }
    virtual void bonk();
private:
};

// Block Declarations

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
    bool m_GoodieReleased;
};

// Pipe Declarations

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

// Goal Declarations

class Goal: public Actor
{
public:
    Goal(int imageID, int startX, int startY, StudentWorld* studentWorldPtr);
    virtual ~Goal()
    {}
    virtual void doSomething() = 0;
private:
};

// Flag Declarations

class Flag: public Goal
{
public:
    Flag(int startX, int startY, StudentWorld* studentWorldPtr);
    virtual ~Flag()
    {}
    virtual void doSomething();
private:
};

// Mario Declarations

class Mario: public Goal
{
public:
    Mario(int startX, int startY, StudentWorld* studentWorldPtr);
    virtual ~Mario()
    {}
    virtual void doSomething();
private:
};

// Goodie Declarations

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

// Flower Declarations

class Flower: public Goodie
{
public:
    Flower(int startX, int startY, StudentWorld* studentWorldPtr);
    virtual ~Flower()
    {}
    virtual void doOwnThing();
private:
};

// Mushroom Declarations

class Mushroom: public Goodie
{
public:
    Mushroom(int startX, int startY, StudentWorld* studentWorldPtr);
    virtual ~Mushroom()
    {}
    virtual void doOwnThing();
private:
};

// Star Declarations

class Star: public Goodie
{
public:
    Star(int startX, int startY, StudentWorld* studentWorldPtr);
    virtual ~Star()
    {}
    virtual void doOwnThing();
private:
};

// Projectile Declarations

class Projectile: public Actor
{
public:
    Projectile(int imageID, int startX, int startY, int startDirection, StudentWorld* studentWorldPtr);
    virtual ~Projectile()
    {}
    virtual void doSomething();
    // Pure virtual to keep Projectile abstract, since Shell and PeachFireball have the same implementation
    virtual bool hitTarget() = 0;
    void move();
private:
};

// Shell Declarations

class Shell: public Projectile
{
public:
    Shell(int startX, int startY, int startDirection, StudentWorld* studentWorldPtr);
    virtual ~Shell()
    {};
    bool hitTarget();
private:
};

// PeachFireball Declarations

class PeachFireball: public Projectile
{
public:
    PeachFireball(int startX, int startY, int startDirection, StudentWorld* studentWorldPtr);
    virtual ~PeachFireball()
    {}
    bool hitTarget();
private:
};

// PiranhaFireball Declarations

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