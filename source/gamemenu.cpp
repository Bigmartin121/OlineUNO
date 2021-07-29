#include"gamemenu.h"

void ColorChoice(int a) {
	switch (a)
	{
	case 1:	//White on Black：
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
			FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	case 2:	//Red on Black：
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
			FOREGROUND_RED);
		break;
	case 3:	//Green on Black：
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
			FOREGROUND_GREEN);
		break;
	case 4:	//Yellow on Black：
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
			FOREGROUND_RED | FOREGROUND_GREEN);
		break;
	case 5:	//Blue on Black：
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
			FOREGROUND_BLUE);
		break;
	case 6:	//Magenta on Black：
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
			FOREGROUND_RED | FOREGROUND_BLUE);
		break;
	case 7:	//Cyan on Black：
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
			FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	case 8:	//Black on Gray：
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY |
			BACKGROUND_INTENSITY);
		break;
	case 9:	//Black on White：
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY |
			FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
		break;
	case 10: //Red on White：
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY |
			FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE |
			FOREGROUND_RED);
		break;
	}
}
 
void Msg::GameStart() {
	cout << "-----------------游戏开始--------------\n";
}

//出牌、摸牌、过牌提示信息
void Msg::CardsPlayMsg() {
	cout << "选择动作 1-3 : " << endl;    //选择按钮动作
	cout << endl;

	//出牌选项
	cout << "   ";
	ColorChoice(10);    //红字白底颜色
	cout << "1、出牌";
	ColorChoice(1);
	cout << "   ";

	//摸牌选项
	ColorChoice(10);
	cout << "2、摸牌";
	ColorChoice(1);
	cout << "   ";

	//过牌选项
	ColorChoice(10);
	cout << "3、过牌";


	//输入要执行的动作
	ColorChoice(1);
	cout << endl;
	cout << endl;
	cout << "请输入: ";
}

//出牌提示
void Msg::CardsOutMsg() {
	cout << "请输入当前手牌堆的编号0-最大值：" << endl;
	//cout << "Choose a card: ";
}

//玩家摸牌后有合法牌选择：打出、保留
void Msg::LegalMsg() {
	cout << "选择动作: " << endl;    //选择按钮动作
	cout << endl;
	//出牌选项
	cout << "   ";
	ColorChoice(10);
	cout << "出牌 out";
	ColorChoice(1);
	cout << "   ";

	//摸牌选项
	ColorChoice(10);
	cout << "摸牌 get" << endl;

	//输入要执行的动作
	ColorChoice(1);
	cout << endl;
	cout << endl;
	cout << "输入要执行的动作: ";
}

void Msg::CardsColorChoice() {
	cout << "选择你要更改的颜色:" << endl;
	cout << endl;
	cout << "   ";
	ColorChoice(2);
	cout << "red";  //红色
	ColorChoice(1);
	cout << "   ";
	ColorChoice(4);
	cout << "yellow"; //黄色
	ColorChoice(1);
	cout << "   ";
	ColorChoice(5);
	cout << "blue"; // 蓝色
	ColorChoice(1);
	cout << "   ";
	ColorChoice(3);
	cout << "green";    //绿色
	ColorChoice(1);
	cout << endl;
	//cout << "R for red Y for yellow B for blue and G for green";//????
	cout << endl;
	cout << endl;
	cout << "输入你选择的颜色: ";
}

void Msg::FourCardSuspectMsg() {
	cout << "是否质疑? (Y/N): ";
}

void Msg::RoundAgainMsg() {
	cout << "Do you want another round? (Y/N): ";
}

void Msg::UNOJudgeMsg() {
	cout << "是否 UNO? (Y/N): ";
}

void Msg::ErrMsg() {
	cout << "Input Error!" << endl;
}

void Msg::RoundOverMsg() {
	cout << "你的回合已经结束..." << endl;
}

void Msg::HandsCards() {
	cout << "你的手牌: " << endl;
}

void Msg::ClearMsg() {
	system("CLS");
}

void Msg::RoboCompute() {
	cout << "当前处在机器人回合，请您稍等" << endl;
}

void Msg::Reverse() {
	cout << "正在转向" << endl;
}

void Msg::Allcolor() {
	cout << "正在转色" << endl;
}

void Msg::PrintCard(Card &card) {
	cout << "手牌信息：";
	if (card.color == 0) {
		cout << "红色牌" << "\t";
	}
	else if (card.color == 1) {
		cout << "绿色牌" << "\t";
	}
	else if(card.color == 2){
		cout << "蓝色牌" << "\t";
	}
	else if(card.color == 3){
		cout << "黄色牌" << "\t";
	}
	else{
		cout << "黑色牌" << "\t";
	}

	if (card.number < 10) {
		cout << card.number << endl;
	}
	else if (card.number == 10) {
		cout << "+2" << endl;
	}
	else if (card.number == 11) {
		cout << "跳过 skip" << endl;
	}
	else if (card.number == 12) {
		cout << "逆转 Reverse" << endl;
	}
	else if (card.number == 13) {
		cout << "选色牌 Wild" << endl;
	}
	else if (card.number == 14) {
		cout << "选色+4 +4Wild" << endl;
	}
}

void GameMenu::Show_menu() {
	cout << "*******UNO牌大作战*******" << endl;
	cout << "*******1、开始游戏*******" << endl;
	cout << "*******2、结束游戏*******" << endl;
	//	cout << "*******3、排行榜显示*******" << endl;
}

bool GameMenu::Menumain() {
	Show_menu();//调用菜单展示函数
	while (true) {
		int select;
		cin >> select;//输入选择的数字
		switch (select)
		{
		case 1://开始游戏按钮
			system("cls");
			return true;     //成功进入游戏，放回真值
			break;

		case 2://结束游戏按纽，这个按钮触发直接退出cmd控制台
			system("cls");
			cout << "游戏结束，下次再玩吧！" << endl;
			system("pause");
			exit(0);
			break;
			//case 3://排行榜显示按钮
			//	system("cls");
			//	Show_rank();
			//	break;
		default:
			cout << "无效输入，请重新输入" << endl;
			system("pause");
			//goto flag;
			break;
		
		}
	}
}