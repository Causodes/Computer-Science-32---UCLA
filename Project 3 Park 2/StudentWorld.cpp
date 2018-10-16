#include "StudentWorld.h"
#include <string>
#include <vector>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

StudentWorld::StudentWorld(string assetDir)
: GameWorld(assetDir)
{
	m_player = nullptr;
}

StudentWorld::~StudentWorld()
{
	cleanUp();
}

void StudentWorld::addActor(Actor* element)
{
	m_vector.push_back(element);
}

void StudentWorld::checkCollision()
{
	vector<Actor*>::iterator cabIt = m_vector.begin();

	while (cabIt != m_vector.end())
	{
		// Cabbage Collision Check

		if ((*cabIt)->getIID() == IID_CABBAGE && (*cabIt)->isAlive())
		{
			double cabX = (*cabIt)->getX();
			double cabY = (*cabIt)->getY();
			double cabR = (*cabIt)->getRadius();

			vector<Actor*>::iterator it = m_vector.begin();

			while (it != m_vector.end())
			{
			if ((*it)->isAlive() && ((*it)->getIID() == IID_SMALLGON || (*it)->getIID() == IID_SMOREGON || (*it)->getIID() == IID_SNAGGLEGON))
				{
					double alienX = (*it)->getX();
					double alienY = (*it)->getY();
					double alienR = (*it)->getRadius();

					if (distance(cabX, cabY, alienX, alienY) < .75 * (cabR + alienR))
					{
						(*cabIt)->setDead();
						if ((*it)->takeDamage(IID_CABBAGE))
						{
							if ((*it)->getIID() == IID_SNAGGLEGON)
							{
								if(randInt(1,6) == 6)
									addActor(new ExtraLifeGoodie(alienX, alienY, this));
								increaseScore(750);
							}
							else if ((*it)->getIID() == IID_SMOREGON)
							{
								if (randInt(1, 3) == 1)
								{
									if (randInt(1, 2) == 1)
										addActor(new RepairGoodie(alienX, alienY, this));
									else
										addActor(new TorpedoGoodie(alienX, alienY, this));
								}
							}
							increaseScore(250);
							(*it)->setDead();
							playSound(SOUND_DEATH);
							addActor(new Explosion(alienX, alienY, this));
							m_destroyedEnemies++;
						}
						else
							playSound(SOUND_BLAST);
					}
				}
				it++;
			}
		}

		// Turnip Collision Check

		else if ((*cabIt)->getIID() == IID_TURNIP && (*cabIt)->isAlive())
		{
			double cabX = (*cabIt)->getX();
			double cabY = (*cabIt)->getY();
			double cabR = (*cabIt)->getRadius();

			if (m_player->isAlive())
			{
				double playerX = m_player->getX();
				double playerY = m_player->getY();
				double playerR = m_player->getRadius();

				if (distance(cabX, cabY, playerX, playerY) < .75 * (cabR + playerR))
				{
					(*cabIt)->setDead();
					if (m_player->takeDamage(IID_TURNIP))
						m_player->setDead();
					playSound(SOUND_BLAST);
				}
			}
		}

		// FlatulanTorpedo Collision Check

		else if ((*cabIt)->getIID() == IID_TORPEDO && (*cabIt)->isAlive())
		{
			double cabX = (*cabIt)->getX();
			double cabY = (*cabIt)->getY();
			double cabR = (*cabIt)->getRadius();

			if ((*cabIt)->getDirection() == 0)
			{
				vector<Actor*>::iterator it = m_vector.begin();

				while (it != m_vector.end())
				{
					if ((*it)->isAlive() && ((*it)->getIID() == IID_SMALLGON || (*it)->getIID() == IID_SMOREGON || (*cabIt)->getIID() == IID_SNAGGLEGON))
					{
						double alienX = (*it)->getX();
						double alienY = (*it)->getY();
						double alienR = (*it)->getRadius();

						if (distance(cabX, cabY, alienX, alienY) < .75 * (cabR + alienR))
						{
							(*cabIt)->setDead();
							if ((*it)->takeDamage(IID_TORPEDO))
							{
								increaseScore(250);
								(*it)->setDead();
								playSound(SOUND_DEATH);
								addActor(new Explosion(alienX, alienY, this));
								m_destroyedEnemies++;
							}
							else
								playSound(SOUND_BLAST);
						}
					}
					it++;
				}
			}

			else if ((*cabIt)->getDirection() == 180)
			{
				if (m_player->isAlive())
				{
					double playerX = m_player->getX();
					double playerY = m_player->getY();
					double playerR = m_player->getRadius();

					if (distance(cabX, cabY, playerX, playerY) < .75 * (cabR + playerR))
					{
						(*cabIt)->setDead();
						if (m_player->takeDamage(IID_TORPEDO))
							m_player->setDead();
						playSound(SOUND_BLAST);
					}
				}
			}
			
		}

		// Alien Ship Collision Check

		else if ((*cabIt)->isAlive() && ((*cabIt)->getIID() == IID_SMALLGON || (*cabIt)->getIID() == IID_SMOREGON || (*cabIt)->getIID() == IID_SNAGGLEGON))
		{
			double alienX = (*cabIt)->getX();
			double alienY = (*cabIt)->getY();
			double alienR = (*cabIt)->getRadius();

			if (m_player->isAlive())
			{
				double playerX = m_player->getX();
				double playerY = m_player->getY();
				double playerR = m_player->getRadius();

				if (distance(alienX, alienY, playerX, playerY) < .75 * (alienR + playerR))
				{
					(*cabIt)->setDead();
					if ((*cabIt)->getIID() == IID_SNAGGLEGON)
					{
						if (randInt(1, 6) == 6)
							addActor(new ExtraLifeGoodie(alienX, alienY, this));
						increaseScore(750);
					}
					else if ((*cabIt)->getIID() == IID_SMOREGON)
					{
						if (randInt(1, 3) == 1)
						{
							if (randInt(1, 2) == 1)
								addActor(new RepairGoodie(alienX, alienY, this));
							else
								addActor(new TorpedoGoodie(alienX, alienY, this));
						}
					}
					increaseScore(250);
					addActor(new Explosion(alienX, alienY, this));
					playSound(SOUND_DEATH);
					if(m_player->takeDamage(IID_SMALLGON))
						m_player->setDead();
					m_destroyedEnemies++;
				}
			}
			
		}

		// ExtraLifeGoodie Collision Check

		else if ((*cabIt)->isAlive() && (*cabIt)->getIID() == IID_LIFE_GOODIE)
		{
			double cabX = (*cabIt)->getX();
			double cabY = (*cabIt)->getY();
			double cabR = (*cabIt)->getRadius();


			if (m_player->isAlive())
			{
				double playerX = m_player->getX();
				double playerY = m_player->getY();
				double playerR = m_player->getRadius();

				if (distance(cabX, cabY, playerX, playerY) < .75 * (cabR + playerR))
				{
					(*cabIt)->setDead();
					increaseScore(100);
					playSound(SOUND_GOODIE);
					incLives();
					return;
				}
			}
		}

		// RepairGoodie Collision Check

		else if ((*cabIt)->isAlive() && (*cabIt)->getIID() == IID_REPAIR_GOODIE)
		{
			double cabX = (*cabIt)->getX();
			double cabY = (*cabIt)->getY();
			double cabR = (*cabIt)->getRadius();


			if (m_player->isAlive())
			{
				double playerX = m_player->getX();
				double playerY = m_player->getY();
				double playerR = m_player->getRadius();

				if (distance(cabX, cabY, playerX, playerY) < .75 * (cabR + playerR))
				{
					(*cabIt)->setDead();
					m_player->takeDamage(IID_REPAIR_GOODIE);
					increaseScore(100);
					playSound(SOUND_GOODIE);
					return;
				}
			}
		}

		// TorpedoGoodie Collision Check

		else if ((*cabIt)->isAlive() && (*cabIt)->getIID() == IID_TORPEDO_GOODIE)
		{
			double cabX = (*cabIt)->getX();
			double cabY = (*cabIt)->getY();
			double cabR = (*cabIt)->getRadius();


			if (m_player->isAlive())
			{
				double playerX = m_player->getX();
				double playerY = m_player->getY();
				double playerR = m_player->getRadius();

				if (distance(cabX, cabY, playerX, playerY) < .75 * (cabR + playerR))
				{
					(*cabIt)->setDead();
					m_player->takeDamage(IID_TORPEDO_GOODIE);
					increaseScore(100);
					playSound(SOUND_GOODIE);
					return;
				}
			}
		}

		cabIt++;
	}


}

void StudentWorld::endGame()
{
	while (getLives() > 0)
		decLives();
}

double StudentWorld::distance(double x1, double y1, double x2, double y2)
{
	double x = x1 - x2;
	double y = y1 - y2;
	return sqrt(x * x + y * y);
}

NachenBlaster* StudentWorld::getPlayer()
{
	return m_player;
}

int StudentWorld::init()
{
	m_destroyedEnemies = 0;
	m_numberOfCurrent = 0;
	m_enemiesPerLevel = 6 + (4 * getLevel());
	m_maxEnemies = 4 + 0.5 * getLevel();

	// NachenBlaster initialization

	m_player = new NachenBlaster(this);

	// Star background initialization

	for (int i = 0; i < 30; i++)
	{
		addActor(new Star(0, VIEW_WIDTH - 1, 0, VIEW_HEIGHT - 1, this));
	}
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{

	// Stat line initialization

	setGameStatText("Lives: " + std::to_string(getLives()) + "  Health: " + std::to_string(m_player->getHealth()*2) + "%  Score: " + std::to_string(getScore()) + "  Level: " + std::to_string(getLevel()) + "  Cabbages: " + std::to_string(m_player->getCabbageEnergy()*10/3) + "%  Torpedoes: " + std::to_string(m_player->getTorpedoCount()));
	//setGameStatText("Current: " + std::to_string(m_numberOfCurrent) + " Destroyed: " + std::to_string(m_destroyedEnemies) + " Per Level: " + std::to_string(m_enemiesPerLevel) + " Max: " + std::to_string(m_maxEnemies));
	
	// Add alien ships

	if (m_destroyedEnemies < m_enemiesPerLevel && m_numberOfCurrent < m_maxEnemies && m_numberOfCurrent < m_enemiesPerLevel - m_destroyedEnemies)
	{
		int S1 = 60;
		int S2 = 20 + getLevel() * 5;
		int S3 = 5 + getLevel() * 10;

		int S = S1 + S2 + S3;

		int probability = randInt(1, S);

		if (probability > 0 && probability <= S1)
		{
			addActor(new Smallgon(getLevel(), this));
			m_numberOfCurrent++;
		}
		else if (probability > S1 && probability <= S1 + S2)
		{
			addActor(new Smoregon(getLevel(), this));
			m_numberOfCurrent++;
		}
		else if (probability > S1 + S2 && probability <= S)
		{
			addActor(new Snagglegon(getLevel(), this));
			m_numberOfCurrent++;
		}
	}

	// Check for collision before movement

	checkCollision();

	// Animate alive actors

	if (!m_player->isAlive())
	{
		decLives();
		return GWSTATUS_PLAYER_DIED;
	}
	else
	{
		m_player->doSomething();
	}

	for(vector<Actor*>::iterator it_1 = m_vector.begin(); it_1 != m_vector.end(); it_1++)
	{
		if ((*it_1)->isAlive())
			(*it_1)->doSomething();
	}

	// Delete dead actors

	if (!m_player->isAlive())
	{
		decLives();
		return GWSTATUS_PLAYER_DIED;
	}

	vector<Actor*>::iterator it_2 = m_vector.begin();

	while (it_2 != m_vector.end())
	{
		if (!(*it_2)->isAlive())
		{
			if ((*it_2)->getIID() == IID_SMALLGON || (*it_2)->getIID() == IID_SMOREGON || (*it_2)->getIID() == IID_SNAGGLEGON)
				m_numberOfCurrent--;
			delete *it_2;
			it_2 = m_vector.erase(it_2);
		}
		else
		{
			it_2++;
		}
	}

	// Check for collision after movement

	checkCollision();

	// Delete dead actors

	vector<Actor*>::iterator it_3 = m_vector.begin();

	while (it_3 != m_vector.end())
	{
		if (!(*it_3)->isAlive())
		{
			if ((*it_3)->getIID() == IID_SMALLGON || (*it_3)->getIID() == IID_SMOREGON || (*it_3)->getIID() == IID_SNAGGLEGON)
				m_numberOfCurrent--;
			delete *it_3;
			it_3 = m_vector.erase(it_3);
		}
		else
		{
			it_3++;
		}
	}

	// Add new Star

	if (randInt(1, 15) == 15)
		addActor(new Star(VIEW_WIDTH - 1, VIEW_WIDTH - 1, 0, VIEW_HEIGHT - 1, this));

	// Check Game Status

	if (!m_player->isAlive())
	{
		decLives();
		m_destroyedEnemies = 0;
		m_numberOfCurrent = 0;
		m_enemiesPerLevel = 6 + (4 * getLevel());
		m_maxEnemies = 4 + 0.5 * getLevel();
		return GWSTATUS_PLAYER_DIED;
	}

	if (m_destroyedEnemies >= m_enemiesPerLevel)
	{
		playSound(SOUND_FINISHED_LEVEL);
		return GWSTATUS_FINISHED_LEVEL;
	}
	else
	{
		return GWSTATUS_CONTINUE_GAME;
	}
}

void StudentWorld::cleanUp()
{
	vector<Actor*>::iterator it;
	it = m_vector.begin();
	while (it != m_vector.end())
	{
		delete *it;
		it = m_vector.erase(it);
	}
	delete m_player;
	m_player = nullptr;
}
