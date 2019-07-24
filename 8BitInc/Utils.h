#ifndef H__UTILS_050520131719__H
#define H__UTILS_050520131719__H

#include <sstream>

namespace utils
{
	template<class T>
	T stringToNum(const std::string& str)
	{
		std::istringstream iss(str);
		T number;
		iss >> number; 
		return number;
	}

	inline int random(int min, int max)
	{
		return (rand() % (max - min + 1) + min);
	}
};

#endif