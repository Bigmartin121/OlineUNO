#include <iostream>
#include "process.h"
#include <algorithm>
#include <windows.h>
using namespace std;

//是否是数字牌
bool is_NumCard(Card& card) {
	if (card.number >= 0 && card.number <= 9) return 1;
	return 0;
}

//合法性判断
bool cardJudge(Card &receiveCard, Card &currentCard) {
	if (currentCard.number == 13 || currentCard.number == 14) {
		return true;
	}
	if (currentCard.color == receiveCard.color || currentCard.number == receiveCard.number)
		return true;
	return false;
}

//将枚举类型转换为字符串
string enumToString(int color) {
	switch (color)
	{
	case red:
		return "red";
		break;
	case green:
		return "green";
	case blue:
		return "blue";
	case yellow:
		return "yellow";
	case black:
		return "black";
	default:
		break;
	}
}


Process::Process(){

}

//初始化牌库
void Process::initDeck() {

}


//开始游戏部分，牌库初始化，玩家初始化，底牌确定，初始化部分参数
void Process::startUNO() {
	unoMsg.GameStart();
	deck.Init();		//牌库初始化
	deck.Shuffle();		//牌库洗牌

	for (int i = 0; i < 4; i++) { //初始化玩家
		Player p;
		players.push_back(p);
	}

	Context ct;
	//Context ct = Context(Draw("interface_Begin"));
	ct.show();

	for (vector<Player>::iterator it = players.begin(); it != players.end(); it++) {
		for (int i = 0; i < 7; i++) {
			it->handCardAdd(deck.getCard());
		}
	}
	while (true)
	{
		receiveCard = deck.getCard();		//底牌
		if (receiveCard.number == 14 || receiveCard.number == 13) {			//可以简化为.color属性
			deck.addCard(receiveCard);		//如果底牌是黑色牌，将底牌放回
		}
		else {
			break;							//底牌不是黑色牌，完成操作
		}
	}

	preCard = receiveCard;
	//deck.addCard(receiveCard);			//此处确保牌库不变，设置初始上一玩家牌信息
	currentPos = 0;//(int)rand() % 4;	//随机选定一个玩家作为初始玩家出牌，以pos==0表示当前为玩家的回合，否则为机器的回合
	flagfirst = true;	//是否是第一轮游戏
	direction = 1;
}

//初始化缺失颜色容器
void Process::initLackColor() {
	vector<string> ii;
	ii.push_back("something");
	for (int i = 0; i < 4; i++) {
		lackColor.push_back(ii);
	}
}

bool Process::start() {
	Manager m;
	return m.managerMain();		//是否登录成功
}

// 游戏过程所有玩家可能缺失的颜色记录 容器类型 char 与enum的确定
void Process::recordPlayerColor() {
	string color = enumToString(receiveCard.color);
	vector<vector<string>>::iterator i = lackColor.begin();
	i += currentPos;
	if (flagPlusCard and !count(i->begin(), i->end(), color)) {	//当前玩家摸牌 且该玩家的缺失花色中没有改颜色	
		i->push_back(color);
	}
	else if (!flagPlusCard and count(i->begin(), i->end(), color)) {
		for (vector<string>::iterator j = i->begin(); j != i->end(); j++) {
			if (*j == color) {
				j = i->erase(j);
				break;
			}
		}
	}
}


/*
//一局游戏结束 各玩家分数计算 排名 展示 我给明哥提示过一个类似的可以进行参考
void Process::computeScore() {
	vector<int> ScorePlayer;
	vector<Player>::iterator it = players.begin();
	for (it; it != players.end(); it++) {
		int sum = 0;
		while (it->head) {
			switch (it->head->data.number)
			{
			case 1:
				sum += 10;		//only a case 
				break;
			default:
				break;
			}
			it->head++;
		}
		ScorePlayer.push_back(sum);
	}
	//针对score进行排序 打印胜利者信息，有点累了，不写了
}
*/


//更新 每轮游戏的上上玩家出牌 上玩家出牌 以及接收牌更新
void Process::updateCard() {
	pPreCard = preCard;
	preCard = currentCard;
	receiveCard = preCard;
}

//更新当前玩家位置 或者下一个玩家位置 flag=1 更新下一个玩家 0 更新当前玩家 
void Process::updatePos(int &pos,int  flag) {
	if (direction == 1){
		pos++;	
	}
	else if (direction == -1) {
		pos--;
	}

	if (pos == -1) {
		pos = 3;
	}
	if (pos == 4) {
		pos = 0;
	}

	if (flag == 0) {
		cout << "当前出牌玩家编号" << pos << endl;
	}
	else {
		cout << "下一个玩家编号" << pos << endl;
	}
	
}

//更新接收牌的颜色，主要是玩家出黑色牌后的颜色调整 ，字符转换
void Process::updateReceiveColor() {
	if (colorSelect == "red") {
		receiveCard.color = red;
	}
	else if (colorSelect == "yellow") {
		receiveCard.color = yellow;
	}
	else if (colorSelect == "green") {
		receiveCard.color = green;
	}
	else if (colorSelect == "blue") {
		receiveCard.color = blue;
	}
	cout << "上个玩家选的颜色：" << colorSelect << endl;
}

//机器人和玩家的一轮游戏的交互或者说出牌过程 所出牌 转色颜色 是否摸牌的确定
void Process::roboAndPlayer(vector<Player>::iterator &it) {
	if (currentPos) {							//若当前位置非0，则为机器人	
		unoMsg.RoboCompute();			//提示信息
		//输入 下一个玩家 
		int pos_next = currentPos;
		updatePos(pos_next,1);
		vector<Player>::iterator it_next = players.begin();
		it_next = it_next + pos_next;	//迭代器位置加1，？？是否会出现超出迭代器位置
		int handSize = it_next->getHandCardSize(); 
		

		robo.RoboInit(preCard, handSize, pos_next, lackColor);	//初始化
		//获得robo的出牌 输出这张牌信息 更新currentCard = 这张牌 或者摸牌的布尔值
		//即给currentCard flagIsGetCard  color 赋值

		vector<Card> playerCards;				//初始化相关参数
		playerCards = it->getPlayerCards();
		bool isQusePrePlayer = false;
		

		flagPlusCard = robo.roboOutMain(playerCards, isQusePrePlayer, flagPlusCard,currentCard); //获得相关参数
		//cout << flagPlusCard << endl;
		if (flagPlusCard) {
			cout << "机器人摸牌" << endl;
			it->handCardAdd(deck.getCard());		//玩家加牌操作 牌库减牌
		}
		else {
			it->handCardRemove(robo.cardPosition(playerCards, currentCard));			//注意顺序是否相反
			cout << "机器人出位置为：" << robo.cardPosition(playerCards, currentCard) << " 的牌"<< endl;
		}

		if (currentCard.number == 13 || currentCard.number == 14) { //黑色牌调色确定
			map<int, string> colorRobo;
			colorRobo = robo.getColorRobo(playerCards);
			colorSelect = robo.cardOutColor(currentCard,colorRobo);
			updateReceiveColor();
		}
		cout << "机器人出牌：" << currentCard << endl;
		cout << "机器人出牌完成" << endl;
	}
	else {
		cout << "当前您的手牌信息如下：" << endl;
		it->printPlayer();			//打印玩家手牌信息

		int select;
		bool isLegal = false;			//出牌是否合法
		while (!isLegal) {
			cout << "牌库剩余：" << deck.getSize() << endl;
			unoMsg.CardsPlayMsg();		//出牌提示
			cin >> select;
			if (select == 1) {
				unoMsg.CardsOutMsg();
				cout << "参考牌为：" << currentCard << endl;
				int choice;			//手牌堆编号
				//cout << "请输入手牌编号：0-最大值" << endl;
				//输入一个整型choice ，输出玩家对应的手牌
				cin >> choice;
				currentCard = it->handCardRemove(choice);	//需不需要-1？//注意顺序是否相反
				isLegal = cardJudge(receiveCard, currentCard);
				if (!isLegal) {
					cout << "出牌不合法" << endl;
					it->handCardAdd(currentCard);   //因为在循环中会首先删除该卡牌，所以若不合法，应该将该卡牌放回。马宇杰，6.15
					it->printPlayer();
					//currentCard = receiveCard;
					//（此处应该封装重新选择出牌的内容）
				}
				else {
					cout << "打出的牌为：" << currentCard << endl;;
				}

				if (currentCard.number == 13 || currentCard.number == 14) { //黑色牌
					unoMsg.CardsColorChoice();
					string choice;		//颜色选择  R Y B G
					cin >> choice;
					colorSelect = choice;
					updateReceiveColor(); 
				}
				flagPlusCard = false;					//是否摸牌 false
			}
			else if (select == 2) {
				flagPlusCard = true;
				it->handCardAdd(deck.getCard());		//玩家加牌操作 牌库减牌
				it->printPlayer();
				isLegal = true;
			}
			else if (select == 3 ) {
				cout << "您选择过牌操作" << endl;
				isLegal = true;
			}
			else {
				cout << "输入出错,请重新输入" << endl;
				Sleep(1000);
				isLegal = false;
			}
		}
	}
}


//第一轮游戏的过程  可以参考那个excel 分情况讨论 由于最后有点晕，可能会写错
void Process::playStageFirst() {
	cout << "底牌信息如下" << "\t" <<receiveCard<<endl<<endl;
	
	if (receiveCard.number <= 9) {			//普通数字牌
		//updatePos(currentPos);
		vector<Player>::iterator it = players.begin();
		it += currentPos;		//获得当前玩家迭代器
		roboAndPlayer(it);
		if (flagPlusCard) pPreCard = preCard;	//当前玩家摸牌
		else {
			updateCard();
		}
	}
	else if (receiveCard.number == 11) {	//跳过
		cout << "上家打出跳过牌，此轮当前玩家禁止出牌" << endl; 
		//updatePos(currentPos);
		pPreCard = preCard;
	}
	else if (receiveCard.number == 12) {	//转向
		cout << "上个玩家所出牌为转向牌，正在转向......." << endl;
		direction = -direction;
		updatePos(currentPos);
		vector<Player>::iterator it = players.begin();
		it += currentPos;		//获得当前玩家迭代器
		cout << "转向完成" << endl;

		roboAndPlayer(it);
		if (flagPlusCard) pPreCard = preCard;	//当前玩家摸牌
		else {
			updateCard();
		}
	}
	else if (receiveCard.number == 10) {	//+2
		cout << "上家打出+2牌，当前玩家被加牌2张" << endl;
		//updatePos(currentPos);
		vector<Player>::iterator it = players.begin();
		it += currentPos;		//获得当前玩家迭代器
		for (int i = 0; i < 2; i++) {
			it->handCardAdd(deck.getCard());
		}
		pPreCard = preCard;
	}
}

//非第一轮的游戏流程
void Process::playStageNotFirst() {

	cout << "上上一个手牌信息如下" << "\t"<< pPreCard<<endl;
	cout << "上一个手牌信息如下" << "\t" << preCard<<endl;
	cout << "接收的手牌信息如下" << "\t" << receiveCard << endl; //当出现黑色转色牌的时候会与上一个手牌信息不一致
	if (flagPlusCard) cout << "上一个玩家未出牌" << endl<<endl;
	
	cout << "手牌依次剩余:"<<endl ;
	int i = 0;
	for (vector<Player>::iterator itplay = players.begin(); itplay != players.end(); itplay++) {
		cout << "----------------------------------------------------------------------------------------" << endl;
		cout << "第"<< i <<"个玩家剩余牌： " << itplay->getHandCardSize() << endl;
		itplay->printPlayer();
		i++;
		cout << endl;
	}
	cout << endl;

	if (receiveCard.number <= 9) {			//普通数字牌  <改为<= 马宇杰。6.15
		updatePos(currentPos);
		vector<Player>::iterator it = players.begin();
		it += currentPos;		//获得当前玩家迭代器
		roboAndPlayer(it);
		updateCard();
	}
	else if (receiveCard.number == 11) {	//跳过
		updatePos(currentPos); 
		if (pPreCard.number == 11) {		//上上家跳过
			vector<Player>::iterator it = players.begin();
			it += currentPos;		//获得当前玩家迭代器
			roboAndPlayer(it);
		}
		else {
			cout << "上家打出跳过牌，此轮当前禁止出牌" << endl;
		}
		updateCard();
	}
	else if (receiveCard.number == 12) {	//转向
		
		vector<Player>::iterator it = players.begin();
		if (pPreCard.number != 12) {
			cout << "正在进行转向......" << endl;
			direction = -direction;				//上个玩家是转向 先进行转向操作
			cout << "转向完成" << endl;
		}
		updatePos(currentPos);
		it += currentPos;		//获得当前玩家迭代器
		roboAndPlayer(it);
		updateCard();
	}
	else if (receiveCard.number == 10) {	//+2
		updatePos(currentPos);
		vector<Player>::iterator it = players.begin();
		it += currentPos;		//获得当前玩家迭代器
		if (pPreCard.number != 10) {
			cout << "上家打出+2牌，当前玩家被加牌2张" << endl;
			for (int i = 0; i < 2; i++) {
				it->handCardAdd(deck.getCard());
			}
		}
		else {
			roboAndPlayer(it);
		}
		updateCard();
	}
	else if (receiveCard.number == 13) {	//转色
		updatePos(currentPos);
		vector<Player>::iterator it = players.begin();
		it += currentPos;		//获得当前玩家迭代器
		if (pPreCard.number != 13) {
			cout << "正在转色" << endl;
			updateReceiveColor();	
		}
		roboAndPlayer(it);
		updateCard();
	}
	else if (receiveCard.number == 14) {	//转色 +4
		updatePos(currentPos);
		vector<Player>::iterator it = players.begin();
		it += currentPos;		//获得当前玩家迭代器
		if (pPreCard.number != 14) {
			cout << "正在转色....." << endl;
			cout << "转色完成" << endl;
			cout << "被加牌4张,此轮禁止出牌" << endl;
			updateReceiveColor();
			for (int i = 0; i < 4; i++) {
				it->handCardAdd(deck.getCard());
			}
		}
		else {
			roboAndPlayer(it);
			}
		updateCard();
	}
}

//游戏主流程
bool Process::execute() {//return 0 则游戏结束
	
	while (true) {				//开始游戏，是否退出
		if (!start()) return false; //启动失败返回0，程序结束
			
		if (!unoMenu.Menumain()) return false;  
		//成功进入游戏
		
		// 一局开始
		while (!flagEnd) {		//开始一局游戏
			startUNO();			//开始游戏，进行一局游戏的初始化
			initLackColor();	//初始化缺失颜色容器
			//一轮开始
			while (!flagEnd) {
				//Context ct;//一个绘制图形的简单工厂，通过show绘制当前游戏界面
				//ct.show();
				
				if (flagfirst) {		//第一轮比赛
					
					playStageFirst();
				}
				else {					//非第一轮比赛
					playStageNotFirst();
				}

				
				flagfirst = false;
				recordPlayerColor();						//记录当前玩家的缺失花色

				vector<Player>::iterator it = players.begin();		//获得当前玩家迭代器
				it += currentPos;
				if (deck.getSize() == 0 || it->getHandCardSize() == 0)	//牌库无牌 当前玩家手牌为0
				{
					flagEnd = true;
				}
				system("pause");
				system("cls");
			}//一轮结束
			//计算分数 输出胜利者信息 flagEnd 已经为真 游戏结束
			//computeScore();
		}//一局结束
		//是否退出游戏 不退出继续进行游戏开始新一轮，退出游戏直接退出
		//unoMenu.Menumain();
		cout << "本局游戏结束" << endl;
		system("pause");
		exit(0);
		break;
	}//游戏结束
}

//
//
////
//bool Process::Ques(Player& p) {
//	int flag = 0;
//	Context ct = Context(Draw("interface_Player_ADD_Query"));
//	ct.show();
//	string str;
//	cin >> str;
//	if (str == "Yes") flag = 1;
//	if (!flag) {
//		count = 4;
//		return 0;
//	}
//	if (find_if(p.begin(), p.end(), is_Num())) {
//		for (int i = 0; i < 4; ++i)
//			p.add_card(deck.Draw());
//		return 1;
//	}
//	else {
//		count = 6;
//		return 0;
//	}
//
//}
//
//