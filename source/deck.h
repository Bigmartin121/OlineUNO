#pragma once
#include "card.h"

class Deck {
public:
	friend class Player;
	friend class Robo;

	Deck();
	Deck(const Deck& other);
	const Deck& operator= (const Deck& other);
	~Deck();
	//对牌库进行初始化
	void Init();

	//洗牌
	void Shuffle();

	//进行一次发牌（摸牌）
	Card getCard();
	
	//加牌操作
	int addCard(Card temp_card);

	//打印牌库
	void printDeck();

	//获取尺寸
	int getSize();


private:

	Card *ptr_deck;  //创建牌库
	int size;		//牌的尺寸
	void clear();	//清空
	void copy(const Deck& other);	//复制

};

