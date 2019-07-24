#ifndef H__GAMETOKEN_050520131304__H
#define H__GAMETOKEN_050520131304__H

#include <string>

class GameToken
{
public:
	GameToken(void);
	GameToken(int score, const std::string& title, const std::string& company);
	~GameToken(void);

protected:
	int myScore;
	std::string myTitle;
	std::string myCompany;
};

#endif