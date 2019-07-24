#include "Season.h"
#include "Game.h"
#include "Dice.h"
#include "Worker.h"

#include <iostream>
#include <sstream>


Season::Season(const std::string& name, Game& game)
:myName(name)
,myGame(&game)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Season::~Season(void)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void Season::update()
{
	phase1();

	phase2();

	phase3(3);

	phase4();

	//Phase 5
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void Season::phase1()
{
	//Phase 1
	std::cout <<  myName << "..." << std::endl;
	std::cout << "Phase 1 : Choose a product name." << std::endl;

	std::vector<Worker*> vec = myGame->getAllWorkers();
	Room& room = myGame->getRoom("Recreation");
	for(unsigned int i = 0; i < vec.size(); i++)
	{
		room.affect(vec[i]);
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void Season::phase2()
{
	//Phase 2
	std::cout << "Phase 2 : " << std::endl;
	std::cout << "Assign workers..." << std::endl;

	Room& room = myGame->getRoom("Recreation");
	std::vector<Worker*> vec = room.getWorkers();

	std::cout << "Available workers : " << std::endl;
	for(unsigned int i = 0; i < vec.size(); i++)
	{
		std::cout << i << " : " << vec[i] << std::endl;
	}

	int num = 0;

	std::cout << "Affect ? (-1 to finish)" << std::endl;
	std::cin >> num;

	while(num != -1)
	{
		std::cout << "Which room (Recreation, Graphic, Sound, Program, Hire, Contract) ?" << std::endl;
		std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
		std::string sRoom = "";
		std::getline(std::cin, sRoom);

		Room& room = myGame->getRoom(sRoom);

		if(!room.affect(vec[num]))
		{
			std::cout << "Worker " << vec[num]->getName() << " couldn't be affected." << std::endl;
		}

		std::cout << "Affect ? (-1 to finish)" << std::endl;
		std::cin >> num;
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void Season::phase3(int nbDice)
{
	//Phase 3
	std::cout << "Phase 3 : Roll dice" << std::endl;
	std::vector<Dice> dice;
	dice.resize(3);

	std::cout << "You got : " << std::endl;
	for(unsigned int i = 0; i < dice.size(); i++)
	{
		dice[i].roll();
		std::cout << dice[i] << "  "; 
	}
	std::cout << std::endl;

	std::string sDice;
	std::cout << "Choose the dice to spend (type the dice numbers separated by an empty space and then, return). Type -1 to stop." << std::endl;
	std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
	std::getline(std::cin, sDice);

	while(sDice != "-1")
	{
		std::vector<Dice> vecDice;
		std::istringstream sD(sDice);
		while(!sD.eof())
		{
			int val;
			sD >> val;
			Dice d(dice[val]);
			vecDice.push_back(d);
		}

		std::cout << "Action on which room (Recreation, Graphic, Sound, Program, Hire, Contract) ?" << std::endl;
		std::string sRoom = "";
		std::getline(std::cin, sRoom);

		Room& room = myGame->getRoom(sRoom);

		room.action(vecDice);

		std::cout << "Choose the dice to spend (type the dice numbers separated by an empty space and then, return). Type -1 to stop." << std::endl;
		std::getline(std::cin, sDice);
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void Season::phase4()
{
	//Phase 4
	std::cout << "Phase 4 : Boosting..." << std::endl;
	std::cout << "Player has " << myGame->getPlayer().getGold() << std::endl;
	std::cout << "Spend gold ? 1 for yes, otherwise 0";
	int num;
	std::cin >> num;
	if(num == 1)
	{
		if(myGame->getPlayer().getGold() >= 3)
		{
			myGame->getPlayer().changeGold(-3);
			phase3(2);
		}
		else
		{
			std::cout << "No gold enough" << std::endl;
		}
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void Season::phase5()
{
	//Phase 5
	std::vector<Room*> vec = myGame->getAllRooms();
	for(unsigned int i = 0; i < vec.size(); i++)
	{
		vec[i]->update(*myGame);
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void Season::setSeason(Season* s)
{
	myGame->setSeason(s);
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
Automn::Automn(Game& game)
:Season("Automn", game)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void Automn::update()
{
	Season::update();

	setSeason(new Winter(*myGame));
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
Winter::Winter(Game& game)
:Season("Winter", game)
{

}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void Winter::update()
{
	Season::update();

	setSeason(new Spring(*myGame));
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
Spring::Spring(Game& game)
:Season("Spring", game)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void Spring::update()
{
	Season::update();

	setSeason(new Summer(*myGame));
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
Summer::Summer(Game& game)
:Season("Summer", game)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void Summer::update()
{
	Season::update();

	//Pay wages
	std::vector<Worker*> vec = myGame->getAllWorkers();
	if(myGame->getPlayer().getGold() > vec.size())
	{
		myGame->getPlayer().changeGold(-(int)vec.size());
	}
	else
	{
	}

	setSeason(new Automn(*myGame));
}