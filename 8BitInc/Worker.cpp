#include "Worker.h"
#include "Room.h"

Worker::Worker(void)
:myCurrentState(FRESH)
{
	myValues[0] = myValues[1] = 0;
}

Worker::Worker(const std::string& name, int values[2], const std::vector<Skill>& skills)
:myName(name)
,mySkills(skills)
,myCurrentState(FRESH)
,myRoom(NULL)
{
	myValues[0] = values[0];
	myValues[1] = values[1];
	//mySkills = skills;
}

Worker::Worker(const Worker& w)
{
	myValues[0] = w.myValues[0];
	myValues[1] = w.myValues[1];
	mySkills = w.mySkills;
	myRoom = w.myRoom;
}


Worker::~Worker(void)
{
}

void Worker::affect(Room* room)
{
	if(myRoom)
		myRoom->removeWorker(this);

	myRoom = room;
}

std::ostream& operator << (std::ostream& out, Worker* w)
{
	const std::vector<Worker::Skill>& skills = w->getSkills();
	std::string stringSkills = "";
	for(unsigned int j = 0; j < skills.size(); j++)
		stringSkills += nWorker::getStrSkill(skills[j]) + ", ";

	out << w->getName() << "(" << w->getValue(Worker::FRESH) << ", " << 
		w->getValue(Worker::TIRED) << ")" << " is " << 
		nWorker::getStrState(w->getState()) << " and has skills in: " << stringSkills;

		return out;
}

void Worker::getTired()
{
	if(myCurrentState == FRESH)
		myCurrentState = TIRED;
	else if(myCurrentState == TIRED)
		myCurrentState = WO;
}

void Worker::rest()
{
	if(myCurrentState == WO)
		myCurrentState = TIRED;
	else if(myCurrentState == TIRED)
		myCurrentState = FRESH;
}


namespace nWorker
{
	std::string getStrState(Worker::State s) {return states[s];}
	std::string getStrSkill(Worker::Skill s) {return skills[s];}
};