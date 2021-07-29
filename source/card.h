#pragma once
#define CARD
#include <iostream>
#include<vector>

using namespace std;

enum  CardColor{ red, green, blue, yellow, black };
/*
const char* CardColorname[] = { "red", "green", "blue", "yellow", "black" };
string getCardColor(CardColor type)
{
	int idx = static_cast<int>(type);
	return CardColorname[idx];
}
*/

class Card
{
public:
	int number; // 0-9 numbers, 10->+2, 11->skip, 12->reverse, 13->all color, 14->+4 (all color) 
	CardColor color; // 五种颜色：红、黄、蓝、绿、黑

	//牌型检查：相同
	bool operator==(Card const& other) const;


	//牌型检查：不相同
	bool operator!=(Card const& other) const;

	Card();


	Card(int num, CardColor color);

	//~Card();
};

ostream& operator<<(ostream& out, Card const& temp_card);

