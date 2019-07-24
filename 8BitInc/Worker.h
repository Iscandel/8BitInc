#ifndef H__WORKER0505131245__H
#define H__WORKER0505131245__H

#include <string>
#include <vector>

#define MYLIST_STATE(x)    \
x(FRESH,    "Fresh") \
x(TIRED,	"Tired") \
x(WO,		"Working overtime") 

#define MYLIST_SKILLS(x)    \
x(GRAPHIC,	"Graphic") \
x(SOUND,	"Sound") \
x(PROGRAM,	"Program") 

#define USE_FIRST_ELEMENT(x, y)  x,
#define USE_SECOND_ELEMENT(x, y) y,

class Room;

class Worker
{
public:
	enum State {MYLIST_STATE(USE_FIRST_ELEMENT)};
	enum Skill {MYLIST_SKILLS(USE_FIRST_ELEMENT)};
public:
	Worker(void);
	Worker(const std::string& name, int values[2], const std::vector<Skill>& skills);
	Worker(const Worker& w);
	~Worker(void);

	const State& getState() {return myCurrentState;}
	int getValue(State s) {return myValues[s];}

	void affect(Room*);

	void getTired(); 
	void rest();

	const std::string& getName() {return myName;}
	const std::vector<Skill>& getSkills() {return mySkills;}

	friend std::ostream& operator << (std::ostream& s, Worker* w); 

protected:
	int myValues[2];
	State myCurrentState;
	std::string myName;
	std::vector<Skill> mySkills;

	Room* myRoom;
};

namespace nWorker
{
	static const char *states[] =
	{
		MYLIST_STATE(USE_SECOND_ELEMENT)
	};

	static const char *skills[] =
	{
		MYLIST_SKILLS(USE_SECOND_ELEMENT)
	};

	std::string getStrState(Worker::State s);
	std::string getStrSkill(Worker::Skill s);
};

#undef MYLIST
#undef USE_FIRST_ELEMENT
#undef USE_SECOND_ELEMENT

#endif