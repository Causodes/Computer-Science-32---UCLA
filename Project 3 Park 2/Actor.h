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
	Actor(int imageID, double startX, double startY, int startDirection, double size, int depth, StudentWorld* world);
	virtual ~Actor();
	virtual void doSomething() = 0;
	virtual int getIID() = 0;
	virtual bool takeDamage(int type);
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

class Alien : public Actor
{
public:
	Alien(int imageID, int health, int level, StudentWorld* world);
	virtual ~Alien();
	virtual void doSomething() = 0;
	virtual int getIID() = 0;
	virtual bool takeDamage(int type);
	void setPath(int direction, int length, double speed);
	void decrementPlan();
	double getSpeed();
	int getPlan();
	int getDirection();
	int getLevel();
private:
	int m_health;
	int m_flightPlan;
	double m_travelSpeed;
	int m_direction;
	int m_level;
};

class Projectile : public Actor
{
public:
	Projectile(int imageID, double x_start, double y_start, StudentWorld* world);
	virtual ~Projectile();
	virtual void doSomething() = 0;
	virtual int getIID() = 0;
};

class Drop : public Actor
{
public:
	Drop(int imageID, double x_start, double y_start, StudentWorld* world);
	virtual ~Drop();
	virtual void doSomething();
	virtual int getIID() = 0;
};

class Smallgon : public Alien
{
public:
	Smallgon(int level, StudentWorld* world);
	virtual ~Smallgon();
	virtual void doSomething();
	virtual int getIID();
};

class Smoregon : public Alien
{
public:
	Smoregon(int level, StudentWorld* world);
	virtual ~Smoregon();
	virtual void doSomething();
	virtual int getIID();
};

class Snagglegon : public Alien
{
public:
	Snagglegon(int level, StudentWorld* world);
	virtual ~Snagglegon();
	virtual void doSomething();
	virtual int getIID();
};

class Cabbage : public Projectile
{
public:
	Cabbage(double x_start, double y_start, StudentWorld* world);
	virtual ~Cabbage();
	virtual void doSomething();
	virtual int getIID();
};

class Turnip : public Projectile
{
public:
	Turnip(double x_start, double y_start, StudentWorld* world);
	virtual ~Turnip();
	virtual void doSomething();
	virtual int getIID();
};

class FlatulanTorpedo : public Projectile
{
public:
	FlatulanTorpedo(double x_start, double y_start, int direction, StudentWorld* world);
	virtual ~FlatulanTorpedo();
	virtual void doSomething();
	virtual int getIID();
private:
	int m_direction;
};

class ExtraLifeGoodie : public Drop
{
public:
	ExtraLifeGoodie(double x_start, double y_start, StudentWorld* world);
	virtual ~ExtraLifeGoodie();
	virtual int getIID();
};

class RepairGoodie : public Drop
{
public:
	RepairGoodie(double x_start, double y_start, StudentWorld* world);
	virtual ~RepairGoodie();
	virtual int getIID();
};

class TorpedoGoodie : public Drop
{
public:
	TorpedoGoodie(double x_start, double y_start, StudentWorld* world);
	virtual ~TorpedoGoodie();
	virtual int getIID();
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
	double getPlayerX();
	double getPlayerY();
private:
	int m_health;
	int m_cabbageEnergy;
	int m_torpedoCount;
};

class Star : public Actor
{
public:
	Star(int x_min, int x_max, int y_min, int y_max, StudentWorld* world);
	virtual ~Star();
	virtual void doSomething();
	virtual int getIID();
};

class Explosion : public Actor
{
public:
	Explosion(double x, double y, StudentWorld* world);
	virtual ~Explosion();
	virtual void doSomething();
	virtual int getIID();
private:
	int m_ticks;
};
#endif // ACTOR_H_
