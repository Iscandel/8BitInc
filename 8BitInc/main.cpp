#include <iostream>

#include "Game.h"

int main()
{
	try
	{
		Game game;
	
		game.run();
	}
	catch(std::exception& e)
	{
		std::cout << "error... : " << e.what() << std::endl;
		getchar();
	}
	catch(...)
	{
		std::cout << "Unexpected error..." << std::endl;
		getchar();
	}

	return 0;
}