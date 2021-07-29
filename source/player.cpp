
#include<string.h>
#include<string>
#include "card.h"
#include "player.h"
#include<iostream>


using namespace std;

Player::Player() {
	head = NULL;
	hand_size = 0;
}

Player::Player(const Player& other) {
	copy(other);
}

//等于重载
const Player& Player::operator=(const Player& other) {
	if (this != &other) {
		clear();
		copy(other);
	}
	return *this;
}


Player::~Player() {
	clear();
}

//在手牌的最前面加牌
void Player::handCardAdd(Card temp) {
	
	card_elem* temp_ptr;		//创建一个缓存数据
	temp_ptr = new card_elem;	//
	temp_ptr->data = temp;
	temp_ptr->next = head;
	head = temp_ptr;

	hand_size++;
}

//手牌移除
Card Player::handCardRemove(int pos) {
	//位置出错检查
	if (pos<0 || pos >=hand_size || !head) { //
		return Card();
	}
	//查找删除操作
	card_elem* prev_ptr = head;
	card_elem* target = prev_ptr->next;
	Card temp_card;
	int temp_pos = pos;

	//若在位置为第一个
	if (pos == 0) {
		temp_card = head->data; //保存返回的数据
		head = head->next;		//将指针指向下一个
		delete prev_ptr;		//删除目标元素
		hand_size--;			
		return temp_card;
	}

	//找到前一元素
	while (temp_pos > 1) {
		prev_ptr = prev_ptr->next;
		target = prev_ptr->next;
		temp_pos--;
	} 
	prev_ptr->next = target->next; //连接上下两个元素
	temp_card = target->data;		//将数据保存到tem
	delete target;					//删除目标元素
	hand_size--;
	return temp_card;				//返回目标元素
}

//打印玩家
void Player::printPlayer() {
	int temp_size = hand_size;
	int i = 0;
	// card_elem* temp_ptr = head;
	while(temp_size > 0) {
		/*cout << "*"<<i << " " << temp_ptr->data << "  ";
		temp_ptr = temp_ptr->next;
		i++;
		if (i % 4 == 0) cout << endl;*/

		cout << "|   " << i << "   |  ";
		i++;
		temp_size--;
	}
	cout << endl;
	temp_size = hand_size;
	card_elem* temp_ptr = head;
	string color;
	while (temp_size > 0) {
		switch (temp_ptr->data.color)
		{
		case black: color = "black ";  break;
		case red: color =  "red   ";  break;
		case green: color = "green ";  break;
		case blue: color = "blue  ";  break;
		case yellow:color = "yellow";  break;
		default: color = "N/A   "; break;
		}
		
		cout << "| " << color << "|  ";
		temp_ptr = temp_ptr->next;
		temp_size--;
	}
	cout << endl;
	temp_size = hand_size;
	temp_ptr = head;
	string number;
	while (temp_size > 0) {
		switch (temp_ptr->data.number)
		{
		case 10: number = "+2     "; break;
		case 11: number = "SKIP   "; break;
		case 12: number = "REVERSE"; break;
		case 13: number = "WILD   "; break;
		case 14: number = "+4     "; break;
		default: number = to_string(temp_ptr->data.number) + "      "; break;
		}
		cout << "|" << number << "|  ";
		temp_ptr = temp_ptr->next;
		temp_size--;
	}
	cout << endl;
}
//获取玩家手牌数量
int Player::getHandCardSize() {
	return hand_size;
}



//玩家初始化
void Player::initPlayer(Deck deck) {
	for (int i = 0; i < 7; i++) {
		this->handCardAdd(deck.getCard());
}
}

//进行复制操作
void Player::copy(const Player& other) {
	hand_size = other.hand_size;

	//创建目标玩家的对象
	if (hand_size > 0) {
		head = new card_elem();
		head->data = other.head->data;
	}
	else {
		head = NULL;
		return;
	}
	//用other_ptr 保存其他表
	card_elem* other_ptr = other.head->next;
	//创建一个缓存区 temp_ptr 创建其他链表
	card_elem* temp_ptr;
	//创建之前的指针指向当前
	card_elem* prev_ptr = head;
	for (int i = 1; i < hand_size; i++) {
		
		temp_ptr = new card_elem;			//创建新元素
		prev_ptr->next = temp_ptr;			//下一目标为缓存区内容
		temp_ptr->data = other_ptr->data;	//当前数据进入缓存区
		prev_ptr = temp_ptr;				//当前内容放入上一区域
		temp_ptr = NULL;					//当前内容为空
		other_ptr = other_ptr->next;		//指定下一内容
	}
}
//清空操作
void Player::clear() {
	card_elem* temp_ptr = head;
	card_elem* next_ptr;
	while (hand_size > 0) {
		next_ptr = temp_ptr->next;
		delete temp_ptr;
		temp_ptr = next_ptr;
		hand_size--;
	}
	head = NULL;
}

//获取当前玩家的手牌容器，主要为机器人服务
vector<Card> Player::getPlayerCards()
{
	vector<Card> playerCards;
	card_elem* temp_head = head;
	while (head)
	{
		Card c;
		c.color = head->data.color;
		c.number = head->data.number;
		playerCards.push_back(c);
		head = head->next;
	}
	head = temp_head;
	//reverse(playerCards.begin(), playerCards.end());  //由于player的链式存储采用的是尾插法，故需要逆转
	return playerCards;
}







