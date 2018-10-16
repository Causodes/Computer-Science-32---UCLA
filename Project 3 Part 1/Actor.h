#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"
#include "GameConstants.h"
#include "GameWorld.h"

class StudentWorld;

class Actor : public GraphObject
{
public:
	Actor(int imageID, int startX, int startY, int startDirection, double size, int depth, StudentWorld* world);
	virtual ~Actor();
	virtual void doSomething() = 0;
	virtual int getIID() = 0;
	virtual bool takeDamage(int type) = 0;
	bool isAlive();
	void setAlive();
	void setDead();
	void setWorld(StudentWorld* world);
	StudentWorld* getWorld();
private:
	int m_imageID;
	bool m_alive;
	StudentWorld* m_world;
};

class NachenBlaster : public Actor
{
public:
	NachenBlaster(StudentWorld* world);
	virtual ~NachenBlaster();
	virtual void doSomething();
	virtual int getIID();
	virtual bool takeDamage(int type);
	int getHealth();
	int getCabbageEnergy();
	int getTorpedoCount();
	int getPlayerX();
	int getPlayerY();
private:
	int m_health;
	int m_cabbageEnergy;
	int m_torpedoCount;
};

class Star : public Actor
{
public:
	Star(int x_min, int x_max, int y_min, int y_max);
	virtual ~Star();
	virtual void doSomething();
	virtual int getIID();
	virtual bool takeDamage(int type);
};

class Cabbage : public Actor
{
public:
	Cabbage(int x_start, int y_start);
	virtual ~Cabbage();
	virtual void doSomething();
	virtual int getIID();
	virtual bool takeDamage(int type);
};

class FlatulanTorpedo : public Actor
{
public:
	FlatulanTorpedo(int x_start, int y_start, int direction);
	virtual ~FlatulanTorpedo();
	virtual void doSomething();
	virtual int getIID();
	virtual bool takeDamage(int type);
private:
	int m_direction;
};

class Smallgon : public Actor
{
public:
	Smallgon(int level);
	virtual ~Smallgon();
	virtual void doSomething();
	virtual int getIID();
	virtual bool takeDamage(int type);
	int getHealth();
private:
	int m_health;
	int m_flightPlan;
	double m_travelSpeed;
	int m_direction;
};

#endif // ACTOR_H_
