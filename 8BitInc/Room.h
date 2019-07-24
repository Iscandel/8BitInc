#ifndef H__ROOM_050520131307__H
#define H__ROOM_050520131307__H

#include <vector>

#include "Worker.h"
#include "Dice.h"

class Game;

class Room
{
public:
	Room(void);
	Room(const std::string& name, int value = 0);
	virtual ~Room(void);

	virtual bool affect(Worker* w) = 0;
	virtual void action(const std::vector<Dice>& dice) = 0;
	virtual void update(Game& g) = 0;

	const std::vector<Worker*>& getWorkers() {return myWorkers;}

	bool removeWorker(Worker* w);
	void removeWorkers() {myWorkers.clear();}

	int getValue() {return myValue;}

	std::string& getName() {return myName;}

protected:
	int myValue;
	std::string myName;
	std::vector<Worker*> myWorkers;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class UpgradeRoom : public Room
{
public:
	UpgradeRoom(const std::string& name, int value, Worker::Skill skillNeeded);
	virtual ~UpgradeRoom(void);

	virtual bool affect(Worker* w);
	virtual void action(const std::vector<Dice>& dice);
	virtual void update(Game& g);

protected:
	int myGainedPoints;
	Worker::Skill mySkillNeeded;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class RecreationRoom : public Room
{
public:
	RecreationRoom();//const std::string& name);
	virtual ~RecreationRoom(void);

	virtual bool affect(Worker* w);
	virtual void action(const std::vector<Dice>& dice);
	virtual void update(Game& g);
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class HireRoom : public Room
{
public:
	HireRoom();//const std::string& name);
	virtual ~HireRoom(void);

	virtual bool affect(Worker* w);
	virtual void action(const std::vector<Dice>& dice);
	virtual void update(Game& g);
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class ContractRoom : public Room
{
public:
	ContractRoom();//const std::string& name);
	virtual ~ContractRoom(void);

	virtual bool affect(Worker* w);
	virtual void action(const std::vector<Dice>& dice);
	virtual void update(Game& g);

};

#endif