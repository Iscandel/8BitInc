#ifndef H__PLAYER_050520131345__H
#define H__PLAYER_050520131345__H

#include <string>

class Player
{
public:
	Player(const std::string& name, const std::string& gameName, int gold = 3);
	~Player(void);

	void changeGold(int value);
	int getGold() {return myGold;}

protected:
	int myScore;
	int myGold;
	std::string myName;
	std::string myGameName;

	int myGraphicScore;
	int mySoundScore;
	int myProgramScore;
};

#endif