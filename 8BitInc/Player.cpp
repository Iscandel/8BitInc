#include "Player.h"

Player::Player(const std::string& name, const std::string& gameName, int gold)
:myGold(gold)
,myName(name)
,myGameName(gameName)
{
}


Player::~Player(void)
{
}

void Player::changeGold(int value) 
{
	myGold += value; 
	myGold = myGold < 0 ? 0 : myGold;
}