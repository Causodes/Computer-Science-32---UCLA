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

double StudentWorld::distance(double x1, double y1, double x2, double y2)
{
	double x = x1 - x2;
	double y = y1 - y2;
	return sqrt(x * x + y * y);
}

int StudentWorld::init()
{
	m_destroyedEnemies = 0;
	m_numberOfCurrent = 0;

	// NachenBlaster initialization

	m_player = new NachenBlaster(this);
	addActor(m_player);

	// Star background initialization

	for (int i = 0; i < 30; i++)
	{
		addActor(new Star(0, VIEW_WIDTH - 1, 0, VIEW_HEIGHT - 1));
	}
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{

	// Stat line initialization

	setGameStatText("Lives: " + std::to_string(getLives()) + "  Health: " + std::to_string(m_player->getHealth()*2) + "%  Score: " + std::to_string(getScore()) + "  Level: " + std::to_string(getLevel()) + "  Cabbages: " + std::to_string(m_player->getCabbageEnergy()*10/3) + "%  Torpedoes: " + std::to_string(m_player->getTorpedoCount()));

	// Add alien ships

	int enemiesPerLevel = 6 + (4 * getLevel());

	if (enemiesPerLevel - m_destroyedEnemies > 0 && m_numberOfCurrent <= 4 + (0.5*getLevel()) - m_destroyedEnemies)
	{
		int S1 = 60;
		int S2 = 20 + getLevel() * 5;
		int S3 = 5 + getLevel() * 10;

		int S = S1 + S2 + S3;

		int probability = randInt(1, S);

		if (probability > 0 && probability <= S1)
		{
			addActor(new Smallgon(getLevel()));
			m_numberOfCurrent++;
		}
		else if (probability > S1 && probability <= S1 + S2)
		{
			m_numberOfCurrent = m_numberOfCurrent;
		}
		else if(probability > S1 + S2 && probability <= S)
		{
			m_numberOfCurrent = m_numberOfCurrent;
		}
	}

	// Check for cabbage collision before movement

	//vector<Actor*>::iterator cabIt = m_vector.begin();

	//while (cabIt != m_vector.end())
	//{
	//	if ((*cabIt)->getIID() == IID_CABBAGE)
	//	{
	//		double cabX = (*cabIt)->getX();
	//		double cabY = (*cabIt)->getY();
	//		double cabR = (*cabIt)->getRadius();
	//		vector<Actor*>::iterator it = m_vector.begin();

	//		while (it != m_vector.end())
	//		{
	//			if ((*it)->getIID() == IID_SMALLGON)
	//			{
	//				double alienX = (*it)->getX();
	//				double alienY = (*it)->getY();
	//				double alienR = (*it)->getRadius();

	//				if (distance(cabX, cabY, alienX, alienY) < .75 * (cabR + alienR))
	//				{
	//					(*cabIt)->setDead();
	//					if ((*it)->takeDamage(IID_CABBAGE))
	//					{
	//						increaseScore(250);
	//						(*it)->setDead();
	//						playSound(SOUND_DEATH);
	//						//addActor(new Explosion(alienX, alienY));
	//						m_destroyedEnemies++;
	//					}
	//					else
	//						playSound(SOUND_BLAST);
	//				}
	//			}
	//			it++;
	//		}
	//	}
	//	cabIt++;
	//}


	// Animate alive actors

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
			if ((*it_2)->getIID() == IID_SMALLGON)
				m_numberOfCurrent--;
			delete *it_2;
			it_2 = m_vector.erase(it_2);
		}
		else
		{
			it_2++;
		}
	}

	// Check for cabbage collision after movement

	//vector<Actor*>::iterator cabIt_1 = m_vector.begin();
	//while (cabIt_1 != m_vector.end())
	//{
	//	if ((*cabIt_1)->getIID() == IID_CABBAGE)
	//	{
	//		double cabX = (*cabIt_1)->getX();
	//		double cabY = (*cabIt_1)->getY();
	//		double cabR = (*cabIt_1)->getRadius();
	//		vector<Actor*>::iterator it_3 = m_vector.begin();

	//		while (it_3 != m_vector.end())
	//		{
	//			if ((*it_3)->getIID() == IID_SMALLGON)
	//			{
	//				double alienX = (*it_3)->getX();
	//				double alienY = (*it_3)->getY();
	//				double alienR = (*it_3)->getRadius();

	//				if (distance(cabX, cabY, alienX, alienY) < .75 * (cabR + alienR))
	//				{
	//					//(*cabIt)->setDead();
	//					if ((*it_3)->takeDamage(IID_CABBAGE))
	//					{
	//						increaseScore(250);
	//						(*it_3)->setDead();
	//						/*playSound(SOUND_DEATH);*/
	//						//addActor(new Explosion(alienX, alienY));
	//						m_destroyedEnemies++;
	//					}
	//					/*else
	//						playSound(SOUND_BLAST);*/
	//				}
	//			}
	//			it_3++;
	//		}
	//	}
	//	cabIt_1++;
	//}

	// Add new Star

	if (randInt(1, 15) == 15)
		addActor(new Star(VIEW_WIDTH - 1, VIEW_WIDTH - 1, 0, VIEW_HEIGHT - 1));

	if (enemiesPerLevel - m_destroyedEnemies <= 0)
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
}
