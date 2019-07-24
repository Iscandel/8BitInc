#include "Game.h"
#include "Season.h"
#include "Utils.h"

#include <ctime>
#include <exception>
#include <queue>

#include <iostream>

Game::Game(void)
:mySeason(NULL)
{
	srand((unsigned int)time(NULL));

	initWorkerStack();

	//for(unsigned int i = 0; i < myWorkerStack.size(); i++)
	//{
	//	std::cout << i << " : " << myWorkerStack[i] << std::endl;
	//}
}
	
//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void Game::initWorkerStack()
{
	//std::queue<Worker*> file;file.push
	std::ifstream file("./data/Workers.txt");
	if(!file)
		throw std::exception("Worker File not found...");

	std::vector<Worker*> tmpVec;
	while(!file.eof())
	{
		std::string name = readLine(file);

		int values[2];
		//std::string sValues = readLine(file);
		values[0] = utils::stringToNum<int>(readLine(file));
		values[1] = utils::stringToNum<int>(readLine(file));
		
		int nSkills = utils::stringToNum<int>(readLine(file));
		std::vector<Worker::Skill> skills;
		for(int i = 0; i < nSkills; i++)
		{
			skills.push_back((Worker::Skill) utils::stringToNum<int>(readLine(file)));
		}

		tmpVec.push_back(new Worker(name, values, skills));	
	}
	//myWorkerStack.push_back(new Worker(tab, {Worker::Skills::GRAPHIC}));
	//Mix all
	myWorkerStack = mix(tmpVec);
}



//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Game::~Game(void)
{
	std::map<std::string, Room*>::iterator it = myRooms.begin();
	for(; it != myRooms.end(); ++it)
	{
		delete it->second;
	}

	//std::<Worker*>::iterator it2 = myWorkerStack.begin();
	//for(; it2 != myWorkerStack.end(); ++it2)
	//{
	//	delete (*it2);
	//}
	while(!myWorkerStack.empty())
	{
		delete myWorkerStack.front();
		myWorkerStack.pop();
	}

	std::vector<GameToken*>::iterator it3 = myTokenStack.begin();
	for(; it3 != myTokenStack.end(); ++it3)
	{
		delete (*it3);
	}

	delete mySeason;

}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
std::string Game::readLine(std::ifstream& file)
{
	std::string line;
	do
	{
		std::getline(file, line);
	}while (line[0] == '#');

	return line;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void Game::startup()
{
	Room* r = new UpgradeRoom("Graphic", 5, Worker::GRAPHIC);
	myRooms[r->getName()] = r;
	r = new UpgradeRoom("Sound", 5, Worker::SOUND);
	myRooms[r->getName()] = r;
	r = new UpgradeRoom("Program", 5, Worker::PROGRAM);
	myRooms[r->getName()] = r;
	r = new UpgradeRoom("Graphic", 5, Worker::GRAPHIC);
	myRooms[r->getName()] = r;

	r = new RecreationRoom;
	myRooms[r->getName()] = r;

	r = new HireRoom;
	myRooms[r->getName()] = r;

	r = new ContractRoom;
	myRooms[r->getName()] = r;

	std::vector<Worker*> tmpWorkers = drawWorkerTokens(3, 2);
	//Worker* tmpWorker[3];
	//for(unsigned int i = 0; i < 3; i++)
	//{
	//	int min = 0;
	//	int max = myWorkerStack.size();
	//	int val = rand() % (max - min) + min;

	//	tmpWorker[i] = myWorkerStack[val];
	//	myWorkerStack.erase(myWorkerStack.begin() + val);
	//}

	//std::cout << "Choose 2 workers between : " << std::endl;
	//for(unsigned int i = 0; i < 3; i++)
	//{
	//	std::cout << i << " : " << tmpWorker[i] << std::endl;
	//}

	//int w1, w2;
	//std::cin >> w1 >> w2;
	
	Room& room = getRoom("Recreation");

	room.affect(tmpWorkers[0]);
	room.affect(tmpWorkers[1]);

	////Remettre dans la pile la carte restante
	//for(unsigned int i = 0; i < 3; i++)
	//{
	//	if(i != w1 && i != w2)
	//	{
	//		myWorkerStack.push(tmpWorkers[i]);
	//		break;
	//	}
	//}


	setSeason(new Automn(*this));
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void Game::run()
{
	myPlayer = new Player("Moi", "monJeu");

	startup();

	for(unsigned int i = 0; i < 3; i++)
	{
		mySeason->update();
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Room& Game::getRoom(const std::string& name)
{
	std::map<std::string, Room*>::iterator it = myRooms.find(name);
	if(it != myRooms.end())
		return *(it->second);

	throw std::exception("Room not found...");
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
std::vector<Worker*> Game::getAllWorkers()
{
	std::vector<Worker*> vec;
	std::map<std::string, Room*>::iterator it = myRooms.begin();
	for(; it != myRooms.end(); ++it)
	{
		std::vector<Worker*> tmp = it->second->getWorkers();
		vec.insert(vec.end(), tmp.begin(), tmp.end());
	}

	return vec;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
std::vector<Room*> Game::getAllRooms()
{
	std::vector<Room*> vec;
	std::map<std::string, Room*>::iterator it = myRooms.begin();
	for(; it != myRooms.end(); ++it)
	{
		vec.push_back(it->second);
	}
	

	return vec;
}

std::vector<Worker*> Game::drawWorkerTokens(int nbTokens, int nbToKeep)
{
	std::vector<Worker*> tmpTokens = drawTokens(myWorkerStack, nbTokens);//, nbToKeep);

	//std::cout << "Choose " << nbToKeep << " workers between : " << std::endl;
	//for(unsigned int i = 0; i < nbTokens; i++)
	//{
	//	std::cout << i << " : " << tmpTokens[i] << std::endl;
	//}

	std::vector<Worker*> res;
	for(unsigned int i = 0; i < nbToKeep; i++)
	{
		std::cout << "Choose " << nbToKeep - i << " workers between : " << std::endl;
		for(unsigned int j = 0; j < nbTokens - i; j++)
		{
			std::cout << j << " : " << tmpTokens[j] << std::endl;
		}
		int val = 0;
		do
		{
			getAnswer(val, "Correct value please...");	
		} while(val < 0 || val > tmpTokens.size());
		
		res.push_back(tmpTokens[i]);
		tmpTokens.erase(tmpTokens.begin() + i);

		
	}

	//Remettre dans la pile la carte restante
	for(unsigned int i = 0; i < tmpTokens.size(); i++)
	{
		myWorkerStack.push(tmpTokens[i]);			
	}

	return res;
}