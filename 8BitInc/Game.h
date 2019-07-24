#ifndef H__GAME_050520131313_H
#define H__GAME_050520131313_H

#include <map>
#include <vector>
#include <queue>
#include <string>
#include <iostream>

#include "Room.h"
#include "Player.h"
#include "GameToken.h"
#include "Worker.h"
#include "Season.h"

#include <fstream>

class Game
{
public:
	Game(void);
	~Game(void);

	void startup();

	void run();

	void setSeason(Season* s) {delete mySeason; mySeason = s;}

	Room& getRoom(const std::string& name);
	Player& getPlayer() {return *myPlayer;}

	std::vector<Worker*> getAllWorkers();
	std::vector<Room*> getAllRooms();

	template<class T>
	std::vector<T> drawTokens(std::queue<T>& tokens, int nbTokens);//, int nbToKeep);

	std::vector<Worker*> drawWorkerTokens(int nbTokens, int nbToKeep);

protected:
	void initWorkerStack();
	std::string readLine(std::ifstream& file);

	template<class T>
	std::queue<T> mix(const std::vector<T>&);

	template<class T>
	void getAnswer(T& ans, const std::string& errorMessage = "");

protected:
	std::map<std::string, Room*> myRooms;

	std::queue<Worker*> myWorkerStack;
	std::vector<GameToken*> myTokenStack;

	Season* mySeason; //init

	Player* myPlayer;
};

template<class T>
std::vector<T> Game::drawTokens(std::queue<T>& tokens, int nbTokens)//, int nbToKeep)
{
	std::vector<T> tmpVect;
	tmpVect.resize(nbTokens);

	for(unsigned int i = 0; i < nbTokens; i++)
	{
		//int min = 0;
		//int max = myWorkerStack.size();
		//int val = rand() % (max - min) + min;

		tmpVect[i] = tokens.front();
		tokens.pop();
		//tokens.erase(myWorkerStack.begin() + val);
	}

	return tmpVect;
}

template<class T>
std::queue<T> Game::mix(const std::vector<T>& vec)
{
	std::queue<T> res;
	int nbElements = vec.size();
	std::vector<Worker*> tmp = vec;

	for(unsigned int i = 0; i < nbElements; i++)
	{
		int val = utils::random(0, tmp.size() - 1);
		res.push(tmp[val]);
		tmp.erase(tmp.begin() + val);
	}

	return res;
}

template<class T> 
void Game::getAnswer(T& ans, const std::string& errorMessage)
{
	std::cin.clear();
	//std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );

	while(! (std::cin >> ans) )
	{
		if ( std::cin.eof() )
        { 
            // ^D  (^Z sous windows); Fin du flux d'entree !
           // return false; 
        }
        else if (std::cin.fail() )
        { 
            if(errorMessage != "")
				std::cout << errorMessage << std::endl;
            std::cin.clear(); 
            std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
        }
		
	}
}

#endif

