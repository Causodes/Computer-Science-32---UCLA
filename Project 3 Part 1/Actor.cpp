#include "Actor.h"
#include <random>

// Actor

Actor::Actor(int imageID, int startX, int startY, int startDirection, double size, int depth, StudentWorld* world)
	:GraphObject(imageID, startX, startY, startDirection, size, depth)
{
}

Actor::~Actor()
{
}

bool Actor::isAlive()
{
	return m_alive;
}

void Actor::setAlive()
{
	m_alive = true;
}

void Actor::setDead()
{
	m_alive = false;
}

void Actor::setWorld(StudentWorld* world)
{
	m_world = world;
}

StudentWorld* Actor::getWorld()
{
	return m_world;
}

// NachenBlaster

NachenBlaster::NachenBlaster(StudentWorld* world)
	:Actor(IID_NACHENBLASTER, 0, VIEW_HEIGHT / 2, 0, 1.0, 0, world)
{
	setAlive();
	setWorld(world);
	m_cabbageEnergy = 30;
	m_health = 50;
	m_torpedoCount = 0;
}

NachenBlaster::~NachenBlaster()
{
	setDead();
	setVisible(false);
}

void NachenBlaster::doSomething()
{
	if (!isAlive())
		return;

	if(m_cabbageEnergy < 30)
		m_cabbageEnergy++;

	int ch;

	if (getWorld()->getKey(ch))
	{
		switch (ch)
		{

		// Movement

		case KEY_PRESS_LEFT:
			if (getX() - 6 > 0)
			{
				double x = getX() - 6;
				double y = getY();

				moveTo(x, y);
			}
			break;
		case KEY_PRESS_RIGHT:
			if (getX() + 6 < VIEW_WIDTH - 1)
			{
				double x = getX() + 6;
				double y = getY();

				moveTo(x, y);
			}
			break;
		case KEY_PRESS_DOWN:
			if (getY() - 6 > 0)
			{
				double x = getX();
				double y = getY() - 6;

				moveTo(x, y);
			}
			break;
		case KEY_PRESS_UP:
			if (getY() + 6 < VIEW_HEIGHT - 1)
			{
				double x = getX();
				double y = getY() + 6;

				moveTo(x, y);
			}
			break;

		// Shooting

		case KEY_PRESS_SPACE:
			if (m_cabbageEnergy >= 5)
			{
				double x = getX() + 12;
				double y = getY();
				getWorld()->addActor(new Cabbage(x, y));
				getWorld()->playSound(SOUND_PLAYER_SHOOT);
				m_cabbageEnergy -= 5;
			}
			break;
		case KEY_PRESS_TAB:
			if (m_torpedoCount >= 1)
			{
				double x = getX() + 12;
				double y = getY();
				getWorld()->addActor(new FlatulanTorpedo(x, y, 0));
				getWorld()->playSound(SOUND_TORPEDO);
				m_torpedoCount--;
			}
		}

	}
}

int NachenBlaster::getIID()
{
	return IID_NACHENBLASTER;
}

bool NachenBlaster::takeDamage(int type)
{
	return false;
}

int NachenBlaster::getHealth()
{
	return m_health;
}

int NachenBlaster::getCabbageEnergy()
{
	return m_cabbageEnergy;
}

int NachenBlaster::getTorpedoCount()
{
	return m_torpedoCount;
}

int NachenBlaster::getPlayerX()
{
	return getX();
}

int NachenBlaster::getPlayerY()
{
	return getY();
}

// Star

Star::Star(int x_min, int x_max, int y_min, int y_max)
	:Actor(IID_STAR, randInt(x_min, x_max), randInt(y_min, y_max), 0, randInt(5,50)/100.0, 3, getWorld())
{
	setAlive();
}

Star::~Star()
{
	setDead();
	setVisible(false);
}

void Star::doSomething()
{
	double x = getX();
	double y = getY();

	moveTo(x-1, y);

	if (x-1 < 0)
	{
		setDead();
	}
}

int Star::getIID()
{
	return IID_STAR;
}

bool Star::takeDamage(int type)
{
	return false;
}

// Cabbage

Cabbage::Cabbage(int x_start, int y_start)
	:Actor(IID_CABBAGE ,x_start, y_start, 0, 0.5, 1, getWorld())
{
	setAlive();
}

Cabbage::~Cabbage()
{
	setDead();
	setVisible(false);
}

void Cabbage::doSomething()
{
	double x = getX();
	double y = getY();

	moveTo(x + 8, y);

	Direction d = getDirection();
	setDirection(d + 20);

	if (x + 8 > VIEW_WIDTH)
	{
		setDead();
	}
}

int Cabbage::getIID()
{
	return IID_CABBAGE;
}

bool Cabbage::takeDamage(int type)
{
	return false;
}

// FlatulanTorpedo

FlatulanTorpedo::FlatulanTorpedo(int x_start, int y_start, int direction)
	:Actor(IID_TORPEDO, x_start, y_start, 0, 0.5, 1, getWorld())
{
	setAlive();
	if (direction == 0)
	{
		m_direction = 0;
		setDirection(0);
	}

	if (direction == 1)
	{
		m_direction == 1;
		setDirection(180);
	}
}

FlatulanTorpedo::~FlatulanTorpedo()
{
	setDead();
	setVisible(false);
}

void FlatulanTorpedo::doSomething()
{
	double x = getX();
	double y = getY();

	if (m_direction == 0)
	{
		moveTo(x + 8, y);
		if (x + 8 > VIEW_WIDTH)
		{
			setDead();
		}
	}

	if (m_direction == 1)
	{
		moveTo(x - 8, y);
		if (x - 8 < 0)
		{
			setDead();
		}
	}
}

int FlatulanTorpedo::getIID()
{
	return IID_TORPEDO;
}

bool FlatulanTorpedo::takeDamage(int type)
{
	return false;
}

// Smallgon

Smallgon::Smallgon(int level)
	:Actor(IID_SMALLGON, VIEW_WIDTH - 1, randInt(0, VIEW_HEIGHT - 1), 0, 1.5, 1, getWorld())
{
	setAlive();
	m_health = 5 * (1 + (level - 1) * 0.1);
	m_flightPlan = 0;
	m_travelSpeed = 2.0;
}

Smallgon::~Smallgon()
{
	setDead();
	setVisible(false);
}

void Smallgon::doSomething()
{
	if (!isAlive())
		return;

	if (getX() < 0)
	{
		setDead();
		return;
	}

	if (getY() == VIEW_HEIGHT - 1)
	{
		m_direction = 1;
		m_flightPlan = randInt(1, 32);
	}

	else if (getY() == 0)
	{
		m_direction = -1; // Up and left
		m_flightPlan = randInt(1, 32);
	}

	else if (m_flightPlan == 0)
	{
		m_direction = randInt(-1, 1);
		m_flightPlan = randInt(1, 32);
	}

	switch (m_direction)
	{

	// Movement

	case -1: // Down and left
		moveTo(getX() - m_travelSpeed, getY() - m_travelSpeed);
		m_flightPlan--;
		break;
	case 0: // Left
		moveTo(getX() - m_travelSpeed, getY());
		m_flightPlan--;
		break;
	case 1: // Up and left
		moveTo(getX() - m_travelSpeed, getY() + m_travelSpeed);
		m_flightPlan--;
		break;
	}
}

int Smallgon::getIID()
{
	return IID_SMALLGON;
}

bool Smallgon::takeDamage(int type)
{
	if (type == IID_CABBAGE)
	{
		m_health -= 2;
		if (m_health <= 0)
		{
			setDead();
			return true;
		}
		return false;
	}
	return false;
}

int Smallgon::getHealth()
{
	return m_health;
}


