#pragma once
#include <iostream>
#include "COLOR.h"
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
};
