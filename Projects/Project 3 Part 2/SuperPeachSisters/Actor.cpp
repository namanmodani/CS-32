//
// CS 32 Project 3
// Naman Modani
// Actor.cpp
//

#include "Actor.h"
#include "StudentWorld.h"
using namespace std;

Actor::Actor(int imageID, int startX, int startY, int startDirection, int depth, StudentWorld* studentWorldPtr)
        : GraphObject(imageID, startX, startY, startDirection, depth, 1.0), m_studentWorldPtr(studentWorldPtr), m_isAlive(true), m_hasTakenDmg(false)
{
    if (startX < 0 || startX > VIEW_WIDTH - 1)
    {
        exit(1);
    }
    if (startY < 0 || startY > VIEW_HEIGHT - 1)
    {
        exit(1);
    }
}

void Actor::takeDamage()
{
    if (!isDamageable())
    {
        return;
    }
    unalive();
}

void Actor::reverseDirection()
{
    setDirection(getDirection() + 180);
}

Peach::Peach(int startX, int startY, StudentWorld* studentWorldPtr)
        : Actor(IID_PEACH, startX, startY, 0, 0, studentWorldPtr), jumpDistanceLeft(0),
          rechargeTime(0), hasFlowerPower(false), hasJumpPower(false),
          hasStarPower(false), numHitPoints(1), tempInvincibility(0)
{}

void Peach::doSomething()
{
    if (!isAlive())
    {
        return;
    }

    if (tempInvincibility > 0)
    {
        tempInvincibility--;
    }
    else {
        hasStarPower = false;
    }

    if (rechargeTime > 0)
    {
        rechargeTime--;
    }

    getWorld()->bonkObjectsAt(getX(), getY());

    if (jumpDistanceLeft > 0)
    {
        int potentialY = getY() + PEACH_STEP;
        if (getWorld()->isBlockingObjectAt(getX(), potentialY))
        {
            getWorld()->bonkObjectsAt(getX(), potentialY);
            jumpDistanceLeft = 0;
        }
        else
        {
            moveTo(getX(), potentialY);
            jumpDistanceLeft--;
        }
    }
    else {
        if (getWorld()->isBlockingObjectAt(getX(), getY() - PEACH_STEP) == false)
        {
            moveTo(getX(), getY() - PEACH_STEP);
        }
    }

    int keyPressed;
    if (getWorld()->getKey(keyPressed))
    {
        int potentialX;
        switch (keyPressed)
        {
            case KEY_PRESS_LEFT:
                setDirection(180);
                potentialX = getX() - PEACH_STEP;
                if (getWorld()->isBlockingObjectAt(potentialX, getY()) == false)
                {
                    moveTo(potentialX, getY());
                }
                else {
                    getWorld()->bonkObjectsAt(potentialX, getY());
                }
                break;
            case KEY_PRESS_RIGHT:
                setDirection(0);
                potentialX = getX() + PEACH_STEP;
                if (getWorld()->isBlockingObjectAt(potentialX, getY()) == false)
                {
                    moveTo(potentialX, getY());
                }
                else {
                    getWorld()->bonkObjectsAt(potentialX, getY());
                }
                break;
            case KEY_PRESS_UP:
                if (getWorld()->isBlockingObjectAt(getX(), getY() - 1) == true)
                {
                    if (useJumpPower() == false)
                    {
                        jumpDistanceLeft = 2*PEACH_STEP;
                    }
                    else
                    {
                        jumpDistanceLeft = 3*PEACH_STEP;
                    }
                    getWorld()->playSound(SOUND_PLAYER_JUMP);
                }
                break;
            case KEY_PRESS_SPACE:
                if (useFlowerPower() == true && rechargeTime == 0)
                {
                    getWorld()->playSound(SOUND_PLAYER_FIRE);
                    rechargeTime = 8;
                    if (getDirection() == 0)
                    {
                        getWorld()->addActor(new PeachFireball(getX() + PEACH_STEP, getY(), getDirection(), getWorld()));
                    }
                    else
                    {
                        getWorld()->addActor(new PeachFireball(getX() - PEACH_STEP, getY(), getDirection(), getWorld()));
                    }
                }
        }
    }
}

void Peach::gainFlowerPower()
{
    hasFlowerPower = true;
    numHitPoints = 2;
}

void Peach::gainJumpPower()
{
    hasJumpPower = true;
    numHitPoints = 2;
}

void Peach::gainStarPower()
{
    hasStarPower = true;
    tempInvincibility = 150;
}

void Peach::takeDamage()
{
    bonk();
}

void Peach::bonk()
{
    if (tempInvincibility > 0)
    {
        return;
    }

    numHitPoints--;
    tempInvincibility = 10;
    if (hasFlowerPower)
    {
        hasFlowerPower = false;
    }
    if (hasJumpPower)
    {
        hasJumpPower = false;
    }

    if (numHitPoints >= 1)
    {
        getWorld()->playSound(SOUND_PLAYER_HURT);
    }
    else
    {
        unalive();
    }
}

Enemy::Enemy(int imageID, int startX, int startY, StudentWorld* studentWorldPtr)
        : Actor(imageID, startX, startY, 0, 0, studentWorldPtr)
{
    if (randInt(0, 1) == 1)
    {
        setDirection(180);
    }
}

void Enemy::takeDamage()
{
    getWorld()->increaseScore(100);
    unalive();
}

void Enemy::move()
{
    if (!canMove())
    {
        return;
    }

    double dx, dy, dx2, dy2;
    getPositionInThisDirection(getDirection(), ENEMY_STEP, dx, dy);
    getPositionInThisDirection(getDirection(), SPRITE_WIDTH, dx2, dy2);
    if (getWorld()->isBlockingObjectAt(dx, getY())
        || getWorld()->isBlockingObjectAt(dx2, getY() - 1) == false)
    {
        reverseDirection();
    }

    getPositionInThisDirection(getDirection(), ENEMY_STEP, dx, dy);
    if (getWorld()->isBlockingObjectAt(dx, getY()) == false)
    {
        moveForward(ENEMY_STEP);
    }
}

void Enemy::bonk()
{
    if (getWorld()->getPeach()->useStarPower())
    {
        getWorld()->playSound(SOUND_PLAYER_KICK);
        takeDamage();
    }
}

Goomba::Goomba(int startX, int startY, StudentWorld* studentWorldPtr)
        : Enemy(IID_GOOMBA, startX, startY, studentWorldPtr)
{}

void Goomba::doSomething()
{
    if (!isAlive())
    {
        return;
    }

    if (getWorld()->isOverlappingWithPeach(getX(), getY()))
    {
        getWorld()->getPeach()->bonk();
        return;
    }

    move();
}

Koopa::Koopa(int startX, int startY, StudentWorld* studentWorldPtr)
        : Enemy(IID_KOOPA, startX, startY, studentWorldPtr)
{}

void Koopa::doSomething()
{
    if (!isAlive())
    {
        return;
    }

    if (getWorld()->isOverlappingWithPeach(getX(), getY()))
    {
        getWorld()->getPeach()->bonk();
        return;
    }

    move();
}

void Koopa::takeDamage()
{
    getWorld()->increaseScore(100);
    unalive();
    getWorld()->addActor(new Shell(getX(), getY(), getDirection(), getWorld()));
}

Piranha::Piranha(int startX, int startY, StudentWorld* studentWorldPtr)
        : Enemy(IID_PIRANHA, startX, startY, studentWorldPtr), firing_delay(0)
{}

void Piranha::doSomething()
{
    if (isAlive() == false)
    {
        return;
    }

    increaseAnimationNumber();

    if (getWorld()->isOverlappingWithPeach(getX(), getY()))
    {
        getWorld()->getPeach()->bonk();
        return;
    }

    if (getWorld()->isOverlappingWithPeach(getX(), getY()))
    {
        return;
    }

    int diffY = getWorld()->getPeach()->getY() - getY();
    if (diffY < 0)
    {
        diffY *= -1;
    }
    if (diffY > 1.5 * SPRITE_HEIGHT)
    {
        return;
    }

    if (getX() > getWorld()->getPeach()->getX())
    {
        setDirection(180);
    }
    else
    {
        setDirection(0);
    }

    if (firing_delay > 0)
    {
        firing_delay--;
        return;
    }

    if (firing_delay == 0)
    {
        int diffX = getWorld()->getPeach()->getX() - getX();
        if (diffX < 0)
        {
            diffX *= -1;
        }
        if (diffX < 8 * SPRITE_WIDTH)
        {
            getWorld()->addActor(new PiranhaFireball(getX(), getY(), getDirection(), getWorld()));
            getWorld()->playSound(SOUND_PIRANHA_FIRE);
            firing_delay = 40;
        }
    }
}

Terrain::Terrain(int imageID, int startX, int startY, StudentWorld* studentWorldPtr)
        : Actor(imageID, startX, startY, 0, 2, studentWorldPtr)
{}

void Terrain::bonk()
{
    getWorld()->playSound(SOUND_PLAYER_BONK);
}

Block::Block(int startX, int startY, StudentWorld* studentWorldPtr, int hasGoodieType)
        : Terrain(IID_BLOCK, startX, startY, studentWorldPtr), m_hasGoodieType(hasGoodieType), m_hadGoodieReleased(false)
{}

void Block::bonk()
{
    if (m_hasGoodieType == NO_GOODIE || m_hadGoodieReleased)
    {
        getWorld()->playSound(SOUND_PLAYER_BONK);
        return;
    }
    else
    {
        getWorld()->playSound(SOUND_POWERUP_APPEARS);
        switch (m_hasGoodieType)
        {
            case FLOWER_GOODIE:
                getWorld()->addActor(new Flower(getX(), getY() + SPRITE_HEIGHT, getWorld()));
                break;
            case MUSHROOM_GOODIE:
                getWorld()->addActor(new Mushroom(getX(), getY() + SPRITE_HEIGHT, getWorld()));
                break;
            case STAR_GOODIE:
                getWorld()->addActor(new Star(getX(), getY() + SPRITE_HEIGHT, getWorld()));
                break;
        }
        m_hadGoodieReleased = true;
    }
}

Pipe::Pipe(int startX, int startY, StudentWorld* studentWorldPtr)
        : Terrain(IID_PIPE, startX, startY, studentWorldPtr)
{}

Goal::Goal(int imageID, int startX, int startY, StudentWorld* studentWorldPtr)
        : Actor(imageID, startX, startY, 0, 1, studentWorldPtr)
{}

Flag::Flag(int startX, int startY, StudentWorld* studentWorldPtr)
        :Goal(IID_FLAG, startX, startY, studentWorldPtr)
{}

void Flag::doSomething()
{
    if (isAlive() == false)
    {
        return;
    }
    if (getWorld()->isOverlappingWithPeach(getX(), getY()))
    {
        unalive();
        getWorld()->levelCompleted();
    }
}

Mario::Mario(int startX, int startY, StudentWorld* studentWorldPtr)
        : Goal(IID_MARIO, startX, startY, studentWorldPtr)
{}

void Mario::doSomething()
{
    if (isAlive() == false)
    {
        return;
    }
    if (getWorld()->isOverlappingWithPeach(getX(), getY()))
    {
        unalive();
        getWorld()->gameWon();
    }
}

Goodie::Goodie(int imageID, int startX, int startY, StudentWorld* studentWorldPtr)
        : Actor(imageID, startX, startY, 0, 1, studentWorldPtr)
{}

void Goodie::doSomething()
{
    if (!isAlive())
    {
        return;
    }

    if (getWorld()->isOverlappingWithPeach(getX(), getY()))
    {
        doOwnThing();

        unalive();
        getWorld()->playSound(SOUND_PLAYER_POWERUP);
        return;
    }

    if (getWorld()->isBlockingObjectAt(getX(), getY() - 1) == false)
    {
        moveTo(getX(), getY() - GOODIE_STEP);
    }

    double dx, dy;
    getPositionInThisDirection(getDirection(), GOODIE_STEP, dx, dy);
    if (getWorld()->isBlockingObjectAt(dx, getY()))
    {
        reverseDirection();
    }
    else
    {
        moveForward(GOODIE_STEP);
    }
}

Flower::Flower(int startX, int startY, StudentWorld* studentWorldPtr)
        : Goodie(IID_FLOWER, startX, startY, studentWorldPtr)
{}

void Flower::doOwnThing()
{
    getWorld()->getPeach()->gainFlowerPower();
    getWorld()->increaseScore(50);
}

Mushroom::Mushroom(int startX, int startY, StudentWorld* studentWorldPtr)
        : Goodie(IID_MUSHROOM, startX, startY, studentWorldPtr)
{}

void Mushroom::doOwnThing()
{
    getWorld()->getPeach()->gainJumpPower();
    getWorld()->increaseScore(75);
}

Star::Star(int startX, int startY, StudentWorld* studentWorldPtr)
        : Goodie(IID_STAR, startX, startY, studentWorldPtr)
{}

void Star::doOwnThing()
{
    getWorld()->getPeach()->gainStarPower();
    getWorld()->increaseScore(100);
}

Projectile::Projectile(int imageID, int startX, int startY, int startDirection, StudentWorld* studentWorldPtr)
        : Actor(imageID, startX, startY, startDirection, 1, studentWorldPtr)
{}

void Projectile::doSomething()
{
    if (hitTarget()) {
        unalive();
        return;
    }
    move();
}

void Projectile::move()
{
    if (getWorld()->isBlockingObjectAt(getX(), getY() - 1) == false)
    {
        moveTo(getX(), getY() - PROJECTILE_STEP);
    }

    double dx, dy;
    getPositionInThisDirection(getDirection(), PROJECTILE_STEP, dx, dy);
    if (getWorld()->isBlockingObjectAt(dx, getY()))
    {
        unalive();
    }
    else
    {
        moveForward(PROJECTILE_STEP);
    }
}

Shell::Shell(int startX, int startY, int startDirection, StudentWorld* studentWorldPtr)
        : Projectile(IID_SHELL, startX, startY, startDirection, studentWorldPtr)
{}

bool Shell::hitTarget()
{
    return getWorld()->isOverlappingWithEnemy(getX(), getY());
}

PeachFireball::PeachFireball(int startX, int startY, int startDirection, StudentWorld* studentWorldPtr)
        : Projectile(IID_PEACH_FIRE, startX, startY, startDirection, studentWorldPtr)
{}

bool PeachFireball::hitTarget()
{
    return getWorld()->isOverlappingWithEnemy(getX(), getY());
}

PiranhaFireball::PiranhaFireball(int startX, int startY, int startDirection, StudentWorld* studentWorldPtr)
        : Projectile(IID_PIRANHA_FIRE, startX, startY, startDirection, studentWorldPtr)
{}

bool PiranhaFireball::hitTarget()
{
    if (getWorld()->isOverlappingWithPeach(getX(), getY()))
    {
        getWorld()->getPeach()->takeDamage();
        return true;
    }
    return false;
}