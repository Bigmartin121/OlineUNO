#include "deck.h"
#include<time.h>

#define CARD_COUNT 108

using namespace std;

class HandCards {

};

Deck::Deck() {
	ptr_deck = new Card[CARD_COUNT];//开辟108张牌的空间
	size = 0;//初始化牌的尺寸
}

Deck::Deck(const Deck& other) {
	copy(other);
}

const Deck& Deck::operator=(const Deck& other) {
	if (this != &other) {
		clear();
		copy(other);
	}
	return *this;
}

//生成牌库
void Deck::Init() {
	int num = 0;


	// 对0号牌进行定义
	for (int col = 0; col < 4; col++)
	{
		ptr_deck[size].number = num;
		ptr_deck[size].color = static_cast<CardColor>(col);
		size++;
	}

	// 对1-9号牌，跳过牌skip，+2牌draw-two，逆转牌reverse每个颜色两张 
	for (num = 1; num <= 12; num++)
	{
		for (int x = 0; x < 2; x++)
		{
			for (int col = 0; col < 4; col++)
			{
				ptr_deck[size].number = num;
				ptr_deck[size].color = static_cast<CardColor>(col);
				size++;
			}
		}

	}

	// 手牌变色牌wild、王牌wild draw four
	for (num = 13; num <= 14; num++)
	{
		for (int x = 0; x < 4; x++)
		{
			ptr_deck[size].number = num;
			ptr_deck[size].color = black;
			size++;
		}
	}
}

//洗牌
void Deck::Shuffle() {
	Card* temp_deck = new Card[size];	//生成一个temp_deck，开辟与牌库相同的空间
	for (int i = 0; i < size; i++) {
		temp_deck[i] = ptr_deck[i];		//将牌放入缓存区
	}

	int temp_size = size;
	int temp_pos;
	int pos;
	for (int i = 0; i < size; i++) {
		//在temp_deck中随机一个位置
		srand((unsigned)time(NULL));;				//在每次时间随机的位置都不一样
		pos = rand() % temp_size;
		ptr_deck[i] = temp_deck[pos];	//将随机后的牌放入牌库

		//移除temp_deck的对应元素
		temp_size--;
		for (temp_pos = pos; temp_pos < temp_size; temp_pos++) {
			temp_deck[temp_pos] = temp_deck[temp_pos + 1];
		}
	}
	delete[] temp_deck;//删除缓存区内容
}


//进行一次发牌（摸牌）
Card Deck::getCard() {
	if (size <= 0) {
		return Card();
	}

	Card temp_card;
	temp_card = ptr_deck[size-1];
	size--;
	return temp_card;
}

//加牌操作
int Deck::addCard(Card temp_card) {
	if (size < CARD_COUNT) {
		ptr_deck[size] = temp_card;
		size++;
		return 0;
	}
	else {
		return 1;
	}
}

//打印牌库
void Deck::printDeck() {
	for (int i = 0; i < size; i++) {
		cout << i << ": " << ptr_deck[i] << endl;
	}
}

//复制牌库内容
void Deck::copy(const Deck& other)
{
	size = other.size;
	ptr_deck = new Card[size];
	for (int i = 0; i < size; i++)
	{
		ptr_deck[i] = other.ptr_deck[i];
	}
}

//清空
void Deck::clear()
{
	delete[] ptr_deck;
	ptr_deck = NULL;
	size = 0;
}

//获取尺寸
int Deck::getSize()
{
	return size;
}

//析构函数
Deck::~Deck() {
	clear();
}
