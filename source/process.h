#pragma once
#include <cstdlib>
#include "time.h"
#include"manager.h"
#include "player.h"
#include "card.h"
#include "deck.h"
#include "robo.h"
#include"gamemenu.h"
#include "string.h"
#include "Context.h"				//绘制图形
#include <vector>

class Process {
public:
	Player currentPlayer;
	Player lastPlayer;				//Player类提供记录当前玩家拥有的牌的数据结构,提供add和del函数，对add一个空做处理，以Card对象作为参数，对这个数据结构做修改；此外还应该提供一个初始化函数，以便在每局开始时对Player内的牌数做初始化
	Deck deck;						//需要一个Draw函数，完成抽牌并且删除牌堆中的该牌，如果抽不出牌就返回一个0；需要一个remains的int变量表示剩余牌数,需要一个init函数来完成对牌堆的初始化：以便于每次重新开始游戏
	Card pPreCard;					//Card需要提供function，表示数字或者功能，提供color表示颜色；Card的==重载应判断两张牌完全相同
	Card preCard;
	Card currentCard;
	Card receiveCard;				//接收的到底是 上家  上上家的牌
	vector<Player> players;			//初始化一个玩家数组，记录了所有玩家，其中0号玩家是人类玩家，其他是机器玩家
	int currentPos;		//表示当前游戏到谁的回合
	int countNum;		//质疑的加牌数量
	int direction;
	bool flag;		//本局游戏继续进行
	
	bool flagEnd = false; //控制游戏是否结束
	bool flagfirst = true;//是否是第一轮比赛
	string colorSelect;			//转色时的颜色选择
	bool flagPlusCard = true;	//是否摸牌
	Robo robo;
	vector<vector<string>> lackColor;
	
	GameMenu unoMenu;			//主菜单显示
	Msg unoMsg;					//cmd提示信息
	
	Process();
	void initDeck();			//初始化牌库和玩家
	void initLackColor();
	void startUNO();

	bool start();										//开场动画->注册登录->开始游戏，启动成功返回1，启动失败返回0
	bool execute();
	

	void playStageFirst();									//第一轮游戏
	void playStageNotFirst();								//非第一轮游戏
	void updateCard();										//更新 上上个玩家出牌 上个玩家出牌 当前出牌 和接收出牌
	void updatePos(int & pos, int flag = 0);					//更新当前玩家位置
	void roboAndPlayer(vector<Player>::iterator &it);		//出牌阶段机器人和玩家的出牌实现  输入指向当前玩家的迭代器
	void updateReceiveColor();								//如果涉及到转色，要将received 的color置为相应颜色，即本轮游戏的颜色
	void recordPlayerColor();								//记录所有玩家可能缺少的牌花色；
};
