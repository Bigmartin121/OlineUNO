#include <iostream>
#include "card.h"

using namespace std;

Card::Card() : number(0), color(black)
{

}

Card::Card(int num, CardColor col) : number(num), color(col)
{

}

bool Card::operator==(Card const& other) const
{
	return number == other.number || color == other.color || color == black || other.color == black;

}


bool Card::operator!=(Card const& other) const
{
	return !(*this == other);
}


ostream& operator<<(ostream& out, Card const& temp_card)
{
	out << "Num:";

	switch (temp_card.number)
	{
	case 10: out << "DRAW-2     "; break;
	case 11: out << "SKIP       "; break;
	case 12: out << "REVERSE    "; break;
	case 13: out << "WILD       "; break;
	case 14: out << "WILD DRAW-4"; break;  
	default: out << (int)temp_card.number<<"          "; break;
	}

	out << "Col:";
	switch (temp_card.color)
	{
	case black: out << "black ";  break;
	case red: out <<   "red   ";  break;
	case green: out << "green ";  break;
	case blue: out <<   "blue  ";  break;
	case yellow: out << "yellow";  break;
	default: out << "N/A   "; break;
	}
	return out;
}

