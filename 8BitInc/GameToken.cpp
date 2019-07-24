#include "GameToken.h"


GameToken::GameToken(void)
{
	myScore = 0;
}


GameToken::GameToken(int score, const std::string& title, const std::string& company)
:myScore(score)
,myTitle(title)
,myCompany(company)
{
}

GameToken::~GameToken(void)
{
}
