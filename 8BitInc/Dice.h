#ifndef H__DICE_050520131834__H
#define H__DICE_050520131834__H

#include <iostream>

class Dice
{
public:
	Dice(int val = 1) :myValue(val) {}

	void roll() {myValue = rand() % (6 - 1) + 1;}

	unsigned int getValue() const {return myValue;}

	friend std::ostream& operator << (std::ostream& out,  Dice& d)
	{
		switch(d.myValue)
		{
		case 1:
			out << " _______" << std::endl;
			out << "|       |" << std::endl;
			out << "|   o   |" << std::endl;
			out << "|_______|" ;
			break;
		case 2:
			out << " _______" << std::endl;
			out << "|       |" << std::endl;
			out << "|  o o  |" << std::endl;
			out << "|_______|" ;
			break;
		case 3:
			out << " _______" << std::endl;
			out << "|o      |" << std::endl;
			out << "|   o   |" << std::endl;
			out << "|______o|" ;
			break;
		case 4:
			out << " _______" << std::endl;
			out << "|o     o|" << std::endl;
			out << "|       |" << std::endl;
			out << "|o_____o|" ;
			break;
		case 5:
			out << " _______" << std::endl;
			out << "|o     o|" << std::endl;
			out << "|   o   |" << std::endl;
			out << "|o_____o|" ;
			break;
		case 6:
			out << " _______" << std::endl;
			out << "|o     o|" << std::endl;
			out << "|o     o|" << std::endl;
			out << "|o_____o|" ;
			break;
		default:
				break;
		}

		return out;
	}

protected:
	unsigned int myValue;
};

#endif