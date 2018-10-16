#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h"
#include "GameConstants.h"
#include <string>
#include <vector>

class Actor;
class NachenBlaster;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
	~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();
	void addActor(Actor* element);
	double distance(double x1, double y1, double x2, double y2);
private:
	std::vector<Actor*> m_vector;
	NachenBlaster* m_player;
	int m_destroyedEnemies;
	int m_numberOfCurrent;
};

#endif // STUDENTWORLD_H_
