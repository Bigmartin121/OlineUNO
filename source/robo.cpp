#include"robo.h"

bool judge(Card& card, Card& preCard)    //（6/11新增）
{
	if (card.number == 13 || card.number == 14)
		return true;
	if (card.color == preCard.color || card.number == preCard.number)
		return true;
	return false;
}

string enumToString2(int color) {
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

Robo::Robo() {

}

void Robo::RoboInit(Card preCard, int numnext, int nextplayer, vector<vector<string>> colorLack) {
	this->preCard = preCard;
	this->numNext = numnext;
	this->nextPlayer = nextplayer;
	this->colorLack = colorLack;
}

int Robo::cardPosition(vector<Card> &playerCards, Card &outCard){
	for (vector<Card>::iterator it = playerCards.begin(); it != playerCards.end(); it++)
	{
		if ((*it).color == outCard.color && (*it).number == outCard.number)
		{
			return it - playerCards.begin();
		} 
	}
}

vector<Card> Robo::getPlayerVaildCard(vector<Card> &playerCards)  //（6/11新增）
{
	vector<Card> vaildCards;
	for (auto playerCard : playerCards)
	{
		//利用判断是否符合规则函数来检测玩家手牌堆中哪张手牌可以使用
		if (judge(playerCard, this->preCard))
		{
			vaildCards.push_back(playerCard);
		}
	}
	return vaildCards;
}

// 0612 得到当前玩家所有手牌的颜色统计 
map<int, string> Robo::getColorRobo(vector<Card> &playerCards) {
	map<int, string> colorRobo;
	//遍历手牌为各个颜色计数
	int numR = 0;
	int numY = 0;
	int numB = 0;
	int numG = 0;
	for (vector<Card>::iterator it = playerCards.begin(); it != playerCards.end(); it++) {
		if (it->color == red) {
			numR++;
		}
		else if (it->color ==yellow) {
			numY++;
		}
		else if (it->color == blue) {
			numB++;
		}
		else {
			numG++;
		}
	}
	colorRobo.insert(pair<int, string>(numR, "red"));
	colorRobo.insert(pair<int, string>(numY, "yellow"));
	colorRobo.insert(pair<int, string>(numB, "blue"));
	colorRobo.insert(pair<int, string>(numG, "green"));//将原有的‘R’转换为CardColor型，马宇杰6.15

	return colorRobo;
}

//下一个玩家手牌数量多于3张的实现 输入 合法手牌堆，输出 当前玩家手牌所有牌的分数 点数越高越容易出这张牌
vector<int> Robo::cardNumHigher3(vector<Card> &vaildCards) {
	vector<int> cardPoint;								//创建牌分值vector容器 下一家玩家多于三张牌时 普通数字>禁止>逆转>变色>+2>+4
	for (vector<Card>::iterator it = vaildCards.begin(); it != vaildCards.end(); it++) {
		if (it->number < 10 and it->number >0) {			//除去0的普通数字牌
			cardPoint.push_back(it->number + 10);
		}
		else if (it->number == 0) {				//0
			cardPoint.push_back(20);
		}
		else {									//非数字牌
			switch (it->number) {
			case 11:							//跳过
				cardPoint.push_back(5);
				break;
			case 10:							//+2
				cardPoint.push_back(2);
				break;
			case 12:							//转向
				cardPoint.push_back(4);
				break;
			case 13:							//转色
				cardPoint.push_back(3);
				break;
			case 14:							//+4
				cardPoint.push_back(1);
				break;
			}
		}
	}
	return cardPoint;
}

//下家手牌少于3或等于三张时，人机出牌优先级算法,输入符合出牌规则的手牌堆，输出该手牌对对应分值
vector<int> Robo::cardNumNotHigher3(vector<Card> &vaildCards)
{
	vector<int> cardPoint;										//创建vector容器存储玩家手牌符合出牌规则的牌的分值，分值越大越优先出该牌
	for (auto card : vaildCards)
	{
		if (card.number < 10)//判断如果是数字牌进行下列操作
		{
			int flag = 0;					//0612 设置是否加分标志位
			
			vector<vector<string>>::iterator it = this->colorLack.begin();			//指向第一个玩家没有颜色的map容器的迭代器
			
			it += this->nextPlayer;													//得到下一个玩家的迭代器
			for (vector<string>::iterator j = it->begin(); j != it->end(); j++) {		//遍历下一个玩家没有颜色的容器
				if (*j == enumToString2(card.color)) {												//当前手牌颜色是下一个玩家所没有的颜色
					flag = 1;				//该手牌已经赋值
					if (card.number == 0)
					{
						cardPoint.push_back(10 + 9 );
					}
					else
					{
						cardPoint.push_back(card.number + 9);
					}
				}
			}
			
			if (flag == 0) {				//该手牌未赋值
				//当前手牌颜色不是下一个玩家所没有的颜色
				if (card.number == 0)//0牌代表10分，单独表示
				{
					cardPoint.push_back(10);
				}
				else//剩余1-9数字牌计分
				{
					cardPoint.push_back(card.number);
				}
			}
		}
		else if (card.number == 11)
		{
			//跳过牌顺序优先级为4，分值22
			cardPoint.push_back(22);
		}
		else if (card.number == 10)
		{
			//加2牌顺序优先级为2，分值30
			cardPoint.push_back(30);
		}
		else if (card.number == 12)
		{
			//逆转牌顺序优先级为3，分值21
			cardPoint.push_back(21);
		}
		else if (card.number == 13)
		{
			//黑色变色牌顺序优先级为5，分值20
			cardPoint.push_back(20);
		}
		else if (card.number == 14)
		{
			//黑色加4牌顺序优先级为1，分值40
			cardPoint.push_back(40);
		}
	}
	return cardPoint;
}


//最终输出牌确定 输入当前玩家手牌分值和合法手牌堆 输出一张手牌 
Card Robo::cardOut(vector<int> &cardPoint,vector<Card> &vaildCards) {
	vector<int> ::iterator indexMax = cardPoint.begin();								//初始化手牌分值最大值
	for (vector<int>::iterator it = cardPoint.begin(); it != cardPoint.end(); it++) {	//寻找手牌分值最大值
		if (*it > *indexMax) {
			indexMax = it;
		}
	}
	int inDex = indexMax - cardPoint.begin();					//获得分值最大的索引值

	Card cardOut = vaildCards.at(inDex);					//确定输出牌
	return cardOut;
}


//机器人输出颜色 如果机器人出黑色牌，那么转色的确定 ，如果不出黑牌，那么颜色即为所出牌颜色 输入当前玩家所出牌 输出char颜色
string Robo::cardOutColor(Card &card,map<int,string> &colorRobo) {
	string color;
	if (card.number == 13 or card.number == 14) {					//机器人输出黑色牌  //疑问：为什么会有第15号牌？马宇杰.6.15
		//this->color_no
		if (this->numNext > 3) {								//下一个玩家所剩手牌大于3
			map<int, string>::iterator it= colorRobo.begin();//map按键值自动排序，最大的key值，即颜色最多的手牌在最后
			color = it->second;									//返回手牌中含有颜色最多的颜色  //这里的输出颜色不对，可以进行重新的修改，此处暂时设置为blue
		}
		else {
			
			vector<vector<string>>::iterator it = this->colorLack.begin();			//指向第一个玩家没有颜色的map容器的迭代器
			it += this->nextPlayer;													//得到下一个玩家的迭代器

			for (vector<string>::iterator j = it->begin(); j != it->end(); j++) {		//遍历下一个玩家没有颜色的容器
				map<int, string>::iterator i = colorRobo.end();					//指向当前机器人手牌颜色的最后一位，即拥有手牌最多的颜色容器
				i--;
				for (i; i == colorRobo.begin(); i--) {						//向前循环
					if (*j == i->second) {					//下一个玩家没有的手牌颜色和当前机器人所拥有的牌颜色重合
						color = *j;
						return color;
					}
				}
			}
			map<int, string>::iterator j = colorRobo.end();
			j--;
			color = j->second;			//下一个玩家没有的手牌颜色和当前机器人所拥有的牌颜色无重合，返回最大数量的颜色手牌
		}
	}
	else {
		color = enumToString2(card.color);   //枚举类型与字符串的转换
	}
	return color;
}
/*
//机器人是否质疑上一个玩家
bool Robo::isQusetion(Card &preCard) {
	vector<vector<char>>::iterator it = this->colorLack.begin();			//指向第一个玩家没有颜色的map容器的迭代器
	it += this->nextPlayer - 1;											//得到上一个玩家的迭代器，这时，next_player还没有更新，指向的还是当前玩家
	for (vector<char>::iterator j = it->begin(); j != it->end(); j++) {		//遍历上一个玩家没有颜色的容器
		if (*j == preCard.color) {											//如果上一个玩家确定没有这个颜色
			return false;
		}
	}
	int y;																	//如果上一个玩家不确定是否有这个颜色，随机猜 50%
	srand((unsigned)time(NULL));
	y = rand() % 10;
	if (y > 5) {
		return false;
	}
	else if (y < 5) {
		return true;
	}
}
*/



//机器人主模块 主要输出 是否质疑 是否摸牌 出牌 转色功能需要在确定下一个玩家后进行
bool Robo::roboOutMain(vector<Card> &playerCards,bool &isQusePrePlayer,bool &isPickCard,Card &nowCard) {
	/*
	if (this->isQusetion(this->preCard))						//质疑上一个玩家
	{
		cout << "您被玩家质疑了" << endl;
		isQusePrePlayer = true;
	}
	else {
		isQusePrePlayer = false;
	}
	*/
	vector<Card> vaildCards = this->getPlayerVaildCard(playerCards);
	if (vaildCards.empty()) {					//合法牌为空
		isPickCard = true;							//摸牌，返回摸牌为真值
		return isPickCard;
	}
	else {										//人机出牌过程实现
		isPickCard = false;
		vector<int> cardScore;
		if (this->numNext > 3) {
			cardScore = this->cardNumHigher3(vaildCards);	//下个玩家手牌数多于3张时调整优先级
		}
		else {
			cardScore = this->cardNumNotHigher3(vaildCards);		//调整优先级
		}

		nowCard = this->cardOut(cardScore,vaildCards);									//确定出牌，这里没有确定输出颜色，需要在这个函数执行后确定下一个玩家后进行
		return isPickCard;
	}
	
}

/*
//机器人主模块，主要实现 是否质疑 是否摸牌 是否出牌 转色功能的实现不在这里
bool Robo::roboOutMain(vector<Card> &vaildCards) {
	if (this->isQusetion(preCard))						//质疑上一个玩家
	{
		cout << "您被玩家质疑了" << endl;
	}

	if (vaild_cards.empty()) {					//合法牌为空
		return true;							//摸牌，返回摸牌为真值
	}
	else {										//人机出牌过程实现
		vector<int> cardScore;
		if (this->numNext > 3) {
			cardScore = this->cardNumHigher3(this->validCards);	//下个玩家手牌数多于3张时调整优先级
		}
		else {
			cardScore = this->cardNumNotHigher3(this->validCards);		//调整优先级
		}
		
		this->cardOut(cardScore);									//确定出牌，这里没有确定输出颜色，需要在这个函数执行后确定下一个玩家后进行
		
		return false;												//不摸牌，返回摸牌为false
	}
}*/



Card Robo::computerReact(vector<Card> &playerCards)//（6/11新加）
{
	vector<Card> v1 = this->getPlayerVaildCard(playerCards);
	vector<int> cardScore;
	if (this->numNext > 3) {
		cardScore = this->cardNumHigher3(v1);	//下个玩家手牌数多于3张时调整优先级
	}
	else {
		cardScore = this->cardNumNotHigher3(v1);		//调整优先级
	}
	return cardOut(cardScore,v1);
}
