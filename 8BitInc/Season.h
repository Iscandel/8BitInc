#ifndef H__SEASON_050520131353__H
#define H__SEASON_050520131353__H

#include <string>

class Game;

class Season
{
public:
	Season(const std::string& name, Game& game);
	~Season(void);

	virtual void update();

	void setSeason(Season* s);

protected:
	void phase1();
	void phase2();
	void phase3(int nbDice);
	void phase4();
	void phase5();

protected:
	std::string myName;
	Game* myGame;
};

class Automn : public Season 
{
public:
	Automn(Game& game);

	virtual void update();
};

class Winter : public Season 
{
public:
	Winter(Game& game);

	virtual void update();
};

class Spring : public Season 
{
public:
	Spring(Game& game);

	virtual void update();
};

class Summer : public Season 
{
public:
	Summer(Game& game);

	virtual void update();
};

#endif