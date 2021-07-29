#pragma once
#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<string.h>
#include<ctime>
#include"card.h"
using namespace std;


class Robo  {
public:
	Robo();
	void RoboInit(Card preCard, int numnext, int nextplayer, vector<vector<string>> colorLack); //初始化


	vector<int> cardNumHigher3(vector<Card> &vaildCards);	//高于三张手牌时优先级调整，此时合法牌应该有牌，输入合法牌，输出手牌分数
	vector<int> cardNumNotHigher3(vector<Card> &vaildCards);			//少于或等于三张手牌时优先级调整，此时合法牌应该有牌，输入合法牌，输出手牌分数
	vector<Card> getPlayerVaildCard(vector<Card> &playerCards); //得到有效手牌堆（6/11新加）
	map<int, string> getColorRobo(vector<Card> &playerCards);		//得到当前机器人手牌颜色统计
	
	Card cardOut(vector<int> &cardPoint,vector<Card> &vaildCards);           //输出所出牌，需要输入调整后的优先级vector容器
	string cardOutColor(Card &card, map<int, string> &colorRobo);					//输出颜色，如果机器人打出黑色牌，需要确定颜色
	//bool isQusetion(Card &preCard);							//是否质疑上一个玩家,输入上上一个玩家手牌
	Card computerReact(vector<Card> &playerCards);			//输入手牌堆，返回一张牌（6/11新加）测试用
	int cardPosition(vector<Card> &playerCards, Card &outCard);	//根据输入的牌输出在player中的位置

	bool roboOutMain(vector<Card> &playerCards,bool &isQusePrePlayer, bool &isPickCard, Card &nowCard);		//机器人主模块，主要判断是否需要摸牌,返回是否摸牌的布尔值

	vector<Card> playerCards;
	Card preCard;									//需要确定是否放在这里，如果放在别的类，可以通过形参实现
	int numNext;									//下一个玩家所剩手牌数量
	int nextPlayer;									//下一个玩家，next_player是一个数字，可以认为是距离开局人的距离 岑哥的是一个指向下一个玩家的迭代器 以上三个变量均需确定是否放在这里，既可以当形参，也可以放在这里，新建一个构造函数
	vector<vector<string>> colorLack;

	Card nowCard;									//当前出牌
	vector<Card> vaildCards;						//当前玩家合法手牌堆
	map<int, string> colorRobo;						//当前机器人手牌的颜色统计 依次 R G B Y
};
