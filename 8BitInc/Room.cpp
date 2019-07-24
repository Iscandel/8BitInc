#include "Room.h"
#include "Game.h"

Room::Room(void)
{
}

Room::Room(const std::string& name, int value)
:myName(name)
,myValue(value)
{
}

Room::~Room(void)
{
}

bool Room::removeWorker(Worker* w)
{
	for(unsigned int i = 0; i < myWorkers.size(); i++)
	{
		if(myWorkers[i] == w)
		{
			myWorkers.erase(myWorkers.begin() + i);
			return true;
		}
	}

	return false;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
UpgradeRoom::UpgradeRoom(const std::string& name, int value, Worker::Skill skillNeeded)
:Room(name, value)
,mySkillNeeded(skillNeeded)
{
}

UpgradeRoom:: ~UpgradeRoom(void)
{
}

bool UpgradeRoom::affect(Worker* w)
{
	if(myWorkers.size() > 0)
		return false;

	const std::vector<Worker::Skill>& skills = w->getSkills();
	for(unsigned int i = 0; i < skills.size(); i++)
	{
		if(mySkillNeeded == skills[i])
		{
			w->affect(this);
			myWorkers.push_back(w);
			//+changer la valeur
			return true;
		}
	}

	return false;
}

void UpgradeRoom::action(const std::vector<Dice>& dice)
{
	int sum = 0;
	for(int i = 0; i < dice.size(); i++)
	{
		sum += dice[i].getValue();
	}

	int myGainedPoints = 0;
	if(myWorkers.size() ==0)
	{
		myGainedPoints = sum / this->myValue;
	}
	else
	{
		switch(myWorkers[0]->getState())
		{
		case Worker::FRESH:
		case Worker::TIRED:
			myGainedPoints = sum / myWorkers[0]->getValue(myWorkers[0]->getState());
		break;
	
		default:
			myGainedPoints = sum / this->myValue;
			break;
		}
	}

}

void UpgradeRoom::update(Game& g)
{
	//Changer les points
	for(unsigned int i = 0; i < myWorkers.size(); i++)
		myWorkers[i]->getTired();
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
RecreationRoom::RecreationRoom()//const std::string& name)
:Room("Recreation")//name)
{
}

RecreationRoom::~RecreationRoom(void)
{
}

bool RecreationRoom::affect(Worker* w)
{
	//Check if he wasn't here yet
	for(unsigned int i = 0; i < myWorkers.size(); i++)
	{
		if(myWorkers[i] == w)
		{
			return false;
		}
	}

	w->affect(this);
	myWorkers.push_back(w);
	return true;
}
	
void RecreationRoom::action(const std::vector<Dice>&)
{
	//Nothing to do here...
}

void RecreationRoom::update(Game&)
{
	for(unsigned int i = 0; i < myWorkers.size(); i++)
		myWorkers[i]->rest();
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
HireRoom::HireRoom()//const std::string& name)
:Room("Hire", 4)//name, 4)
{
}

HireRoom::~HireRoom(void)
{
}

bool HireRoom::affect(Worker*)
{
	//No worker here
	return false;
}
	
void HireRoom::action(const std::vector<Dice>& dice)
{
}

void HireRoom::update(Game& g)
{
	for(unsigned int i = 0; i < myWorkers.size(); i++)
		myWorkers[i]->getTired();
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
ContractRoom::ContractRoom()//const std::string& name)
:Room("Contract", 0)//name, 4)
{
}

ContractRoom::~ContractRoom(void)
{
}

bool ContractRoom::affect(Worker* w)
{
	//Check if he wasn't here yet
	for(unsigned int i = 0; i < myWorkers.size(); i++)
	{
		if(myWorkers[i] == w)
		{
			return false;
		}
	}

	if(w->getState() == Worker::FRESH)
	{
		w->affect(this);
		myWorkers.push_back(w);
		return true;
	}

	return false;
}

void ContractRoom::action(const std::vector<Dice>&)
{
	//Nothing to do here
}
	
void ContractRoom::update(Game& g)
{
	for(unsigned int i = 0; i < myWorkers.size(); i++)
		myWorkers[i]->getTired();

	g.getPlayer().changeGold(myWorkers.size());
}