#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include <Windows.h>
#include"card.h"
using namespace std;

class Msg {
public:
	static void GameStart();            //游戏开始提示
	static void CardsPlayMsg();         //出牌、摸牌、过牌提示
	static void CardsOutMsg();          //出牌提示
	static void LegalMsg();             //摸牌后有合法牌选择：打出、保留提示
	static void CardsColorChoice();     //改色牌颜色选择提示
	static void FourCardSuspectMsg();   //+4牌是否选择质疑提示
	static void RoundAgainMsg();        //再来一局提示
	static void UNOJudgeMsg();          //是否UNO提示
	static void ErrMsg();               //输入错误提示
	static void RoundOverMsg();         //玩家该轮结束提示
	static void ClearMsg();             //清屏函数
	static void HandsCards();           //手牌
	static void RoboCompute();			//机器人回合正在出牌
	static void Reverse();				//转向提示信息
	static void Allcolor();				//转色提示信息
	static void PrintCard(Card &card);	//打印纸牌信息
};

class GameMenu {
public:
	void Show_menu();

	bool Menumain();

};



//void Show_rank() {
//	ifstream show_rank;
//	show_rank.open("rank.txt", ios::in);
//	if (!show_rank.is_open())
//	{
//		cout << "Fail to open this rank menu.Please make sure that you have finished 1 game at least!" << endl;
//	}
//	char grade_message[1024] = {0};
//	while (show_rank.getline(grade_message, sizeof(grade_message)))
//	{
//		cout << grade_message << endl;
//	}
//}


