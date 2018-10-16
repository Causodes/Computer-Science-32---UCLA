#include "Actor.h"
#include <random>

// Actor

Actor::Actor(int imageID, double startX, double startY, int startDirection, double size, int depth, StudentWorld* world)
	:GraphObject(imageID, startX, startY, startDirection, size, depth)
{
	m_alive = true;
	m_world = world;
}

Actor::~Actor()
{

}

bool Actor::takeDamage(int type)
{
	return false;
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

// Alien

Alien::Alien(int imageID, int health, int level, StudentWorld* world)
	:Actor(imageID, VIEW_WIDTH - 1, randInt(0, VIEW_HEIGHT - 1), 0, 1.5, 1, world)
{
	setAlive();
	m_health = health;
	m_flightPlan = 0;
	m_travelSpeed = 2.0;
	m_level = level;
}

Alien::~Alien()
{
	setDead();
}

bool Alien::takeDamage(int type)
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

	else if (type == IID_TORPEDO)
	{
		m_health -= 8;
		if (m_health <= 0)
		{
			setDead();
			return true;
		}
		return false;
	}
	return false;
}

void Alien::setPath(int direction, int length, double speed)
{
	m_direction = direction;
	m_flightPlan = length;
	m_travelSpeed = speed;
}

void Alien::decrementPlan()
{
	m_flightPlan--;
}

double Alien::getSpeed()
{
	return m_travelSpeed;
}

int Alien::getPlan()
{
	return m_flightPlan;
}

int Alien::getDirection()
{
	return m_direction;
}

int Alien::getLevel()
{
	return m_level;
}

// Projectile

Projectile::Projectile(int imageID, double x_start, double y_start, StudentWorld* world)
	:Actor(imageID, x_start, y_start, 0, 0.5, 1, world)
{
	setAlive();
}

Projectile::~Projectile()
{
	setDead();
}

// Drop

Drop::Drop(int imageID, double x_start, double y_start, StudentWorld* world)
	:Actor(imageID, x_start, y_start, 0, 0.5, 1, world)
{
	setAlive();
}

Drop::~Drop()
{
	setDead();
}

void Drop::doSomething()
{
	double x = getX();
	double y = getY();

	moveTo(x - 0.75, y - 0.75);

	if (x - 0.75 < 0 || y - 0.75 < 0)
	{
		setDead();
	}
}

// Smallgon

Smallgon::Smallgon(int level, StudentWorld* world)
	:Alien(IID_SMALLGON, 5 * (1 + (level - 1) * 0.1), level, world)
{
}

Smallgon::~Smallgon()
{
	setDead();
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

	NachenBlaster* player = getWorld()->getPlayer();

	if (player->getPlayerX() < getX())
	{
		if (getY() <= player->getPlayerY() + 4 && getY() >= player->getPlayerY() - 4)
		{
			if (randInt(1, (20 / getLevel()) + 5) == 1)
			{
				getWorld()->addActor(new Turnip(getX() - 14, getY(), getWorld()));
				getWorld()->playSound(SOUND_ALIEN_SHOOT);
			}
		}
	}

	if (getY() >= VIEW_HEIGHT - 1)
		setPath(-1, randInt(1, 32), 2.0); // Down and left

	else if (getY() <= 0)
		setPath(1, randInt(1, 32), 2.0); // Up and left

	else if (getPlan() == 0)
		setPath(randInt(-1, 1), randInt(1, 32), 2.0);

	switch (Alien::getDirection()) // Movement
	{
	case -1: // Down and left
		moveTo(getX() - getSpeed(), getY() - getSpeed());
		decrementPlan();
		break;
	case 0: // Left
		moveTo(getX() - getSpeed(), getY());
		decrementPlan();
		break;
	case 1: // Up and left
		moveTo(getX() - getSpeed(), getY() + getSpeed());
		decrementPlan();
		break;
	}
}

int Smallgon::getIID()
{
	return IID_SMALLGON;
}

// Smoregon

Smoregon::Smoregon(int level, StudentWorld* world)
	:Alien(IID_SMOREGON, 5 * (1 + (level - 1) * 0.1), level, world)
{
}

Smoregon::~Smoregon()
{
	setDead();
}

void Smoregon::doSomething()
{
	if (!isAlive())
		return;

	if (getX() < 0)
	{
		setDead();
		return;
	}

	NachenBlaster* player = getWorld()->getPlayer();

	if (player->getPlayerX() < getX())
	{
		if (getY() <= player->getPlayerY() + 4 && getY() >= player->getPlayerY() - 4)
		{
			if (randInt(1, (20 / getLevel()) + 5) == 1)
			{
				getWorld()->addActor(new Turnip(getX() - 14, getY(), getWorld()));
				getWorld()->playSound(SOUND_ALIEN_SHOOT);
			}
			else if(randInt(1, (20 / getLevel()) + 5) == 2)
			{
				setPath(0, VIEW_WIDTH, 5.0);
			}
		}
	}

	if (getY() >= VIEW_HEIGHT - 1)
		setPath(-1, randInt(1, 32), 2.0); // Down and left

	else if (getY() <= 0)
		setPath(1, randInt(1, 32), 2.0); // Up and left

	else if (getPlan() == 0)
		setPath(randInt(-1, 1), randInt(1, 32), 2.0);

	switch (Alien::getDirection()) // Movement
	{
	case -1: // Down and left
		moveTo(getX() - getSpeed(), getY() - getSpeed());
		decrementPlan();
		break;
	case 0: // Left
		moveTo(getX() - getSpeed(), getY());
		decrementPlan();
		break;
	case 1: // Up and left
		moveTo(getX() - getSpeed(), getY() + getSpeed());
		decrementPlan();
		break;
	}
}

int Smoregon::getIID()
{
	return IID_SMOREGON;
}

// Snagglegon

Snagglegon::Snagglegon(int level, StudentWorld* world)
	:Alien(IID_SNAGGLEGON, 10 * (1 + (level - 1) * 0.1), level, world)
{
	setPath(-1, VIEW_HEIGHT, 1.75);
}

Snagglegon::~Snagglegon()
{
	setDead();
}

void Snagglegon::doSomething()
{
	if (!isAlive())
		return;

	if (getX() < 0)
	{
		setDead();
		return;
	}

	NachenBlaster* player = getWorld()->getPlayer();

	if (player->getPlayerX() < getX())
	{
		if (getY() <= player->getPlayerY() + 4 && getY() >= player->getPlayerY() - 4)
		{
			if (randInt(1, (15 / getLevel()) + 10) == 1)
			{
				getWorld()->addActor(new FlatulanTorpedo(getX() - 14, getY(), 1, getWorld()));
				getWorld()->playSound(SOUND_TORPEDO);
			}
		}
	}

	if (getY() >= VIEW_HEIGHT - 1)
		setPath(-1, VIEW_HEIGHT, 2.0); // Down and left

	else if (getY() <= 0)
		setPath(1, VIEW_HEIGHT, 2.0); // Up and left

	switch (Alien::getDirection()) // Movement
	{
	case -1: // Down and left
		moveTo(getX() - getSpeed(), getY() - getSpeed());
		decrementPlan();
		break;
	case 1: // Up and left
		moveTo(getX() - getSpeed(), getY() + getSpeed());
		decrementPlan();
		break;
	}
}

int Snagglegon::getIID()
{
	return IID_SNAGGLEGON;
}

// Cabbage

Cabbage::Cabbage(double x_start, double y_start, StudentWorld* world)
	:Projectile(IID_CABBAGE, x_start, y_start, world)
{
	setAlive();
}

Cabbage::~Cabbage()
{
	setDead();
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

// Turnip

Turnip::Turnip(double x_start, double y_start, StudentWorld* world)
	:Projectile(IID_TURNIP, x_start, y_start, world)
{
	setAlive();
}

Turnip::~Turnip()
{
	setDead();
}

void Turnip::doSomething()
{
	double x = getX();
	double y = getY();

	moveTo(x - 6, y);

	Direction d = getDirection();
	setDirection(d + 20);

	if (x - 6 < 0)
	{
		setDead();
	}
}

int Turnip::getIID()
{
	return IID_TURNIP;
}

// FlatulanTorpedo

FlatulanTorpedo::FlatulanTorpedo(double x_start, double y_start, int direction, StudentWorld* world)
	:Projectile(IID_TORPEDO, x_start, y_start, world)
{
	setAlive();
	if (direction == 0)
	{
		m_direction = 0;
		setDirection(0);
	}

	if (direction == 1)
	{
		m_direction = 1;
		setDirection(180);
	}
}

FlatulanTorpedo::~FlatulanTorpedo()
{
	setDead();
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

// ExtraLifeGoodie

ExtraLifeGoodie::ExtraLifeGoodie(double x_start, double y_start, StudentWorld* world)
	:Drop(IID_LIFE_GOODIE, x_start, y_start, world)
{
	setAlive();
}

ExtraLifeGoodie::~ExtraLifeGoodie()
{
	setDead();
}

int ExtraLifeGoodie::getIID()
{
	return IID_LIFE_GOODIE;
}

// RepairGoodie

RepairGoodie::RepairGoodie(double x_start, double y_start, StudentWorld* world)
	:Drop(IID_REPAIR_GOODIE, x_start, y_start, world)
{
	setAlive();
}

RepairGoodie::~RepairGoodie()
{
	setDead();
}

int RepairGoodie::getIID()
{
	return IID_REPAIR_GOODIE;
}

// TorpedoGoodie

TorpedoGoodie::TorpedoGoodie(double x_start, double y_start, StudentWorld* world)
	:Drop(IID_TORPEDO_GOODIE, x_start, y_start, world)
{
	setAlive();
}

TorpedoGoodie::~TorpedoGoodie()
{
	setDead();
}

int TorpedoGoodie::getIID()
{
	return IID_TORPEDO_GOODIE;
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
}

void NachenBlaster::doSomething()
{
	if (!isAlive())
		return;

	if (m_cabbageEnergy < 30)
		m_cabbageEnergy++;

	int ch;

	if (getWorld()->getKey(ch))
	{
		switch (ch)
		{

			// Movement

		case KEY_PRESS_LEFT:
			if (getX() - 6 >= 0)
			{
				double x = getX() - 6;
				double y = getY();

				moveTo(x, y);
			}
			break;
		case KEY_PRESS_RIGHT:
			if (getX() + 6 <= VIEW_WIDTH - 1)
			{
				double x = getX() + 6;
				double y = getY();

				moveTo(x, y);
			}
			break;
		case KEY_PRESS_DOWN:
			if (getY() - 6 >= 0)
			{
				double x = getX();
				double y = getY() - 6;

				moveTo(x, y);
			}
			break;
		case KEY_PRESS_UP:
			if (getY() + 6 <= VIEW_HEIGHT - 1)
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
				getWorld()->addActor(new Cabbage(x, y, getWorld()));
				getWorld()->playSound(SOUND_PLAYER_SHOOT);
				m_cabbageEnergy -= 5;
			}
			break;
		case KEY_PRESS_TAB:
			if (m_torpedoCount >= 1)
			{
				double x = getX() + 12;
				double y = getY();
				getWorld()->addActor(new FlatulanTorpedo(x, y, 0, getWorld()));
				getWorld()->playSound(SOUND_TORPEDO);
				m_torpedoCount--;
			}
			break;

			// Quit

		case KEY_PRESS_ESCAPE:
		{
			getWorld()->endGame();
		}
		break;

		default:
			break;
		}
	}
}

int NachenBlaster::getIID()
{
	return IID_NACHENBLASTER;
}

bool NachenBlaster::takeDamage(int type)
{
	if (type == IID_TURNIP)
	{
		m_health -= 2;
		if (m_health <= 0)
		{
			setDead();
			return true;
		}
		return false;
	}

	else if (type == IID_TORPEDO)
	{
		m_health -= 8;
		if (m_health <= 0)
		{
			setDead();
			return true;
		}
		return false;
	}

	else if (type == IID_SMALLGON)
	{
		m_health -= 5;
		if (m_health <= 0)
		{
			setDead();
			return true;
		}
		return false;
	}

	else if (type == IID_REPAIR_GOODIE)
	{
		if (m_health <= 40 && isAlive())
		{
			m_health += 10;
			return false;
		}
		else if (m_health > 40)
		{
			m_health = 50;
			return false;
		}
	}

	else if (type == IID_TORPEDO_GOODIE)
	{
		m_torpedoCount += 5;
		return false;
	}
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

double NachenBlaster::getPlayerX()
{
	return getX();
}

double NachenBlaster::getPlayerY()
{
	return getY();
}


// Star

Star::Star(int x_min, int x_max, int y_min, int y_max, StudentWorld* world)
	:Actor(IID_STAR, randInt(x_min, x_max), randInt(y_min, y_max), 0, randInt(5,50)/100.0, 3, world)
{
	setAlive();
}

Star::~Star()
{
	setDead();
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

// Explosion

Explosion::Explosion(double x, double y, StudentWorld* world)
	:Actor(IID_EXPLOSION, x, y, 0, 1, 0, world)
{
	m_ticks = 0;
}

Explosion::~Explosion()
{
	setDead();
}

void Explosion::doSomething()
{
	if (m_ticks < 4)
	{
		double size = getSize();
		setSize(size*1.5);
		m_ticks++;
	}
	else if (m_ticks >= 4)
	{
		setDead();
	}
}

int Explosion::getIID()
{
	return IID_EXPLOSION;
}