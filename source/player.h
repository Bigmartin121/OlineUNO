
#include<string.h>
#include "card.h"
#include"deck.h"


class Player {	
public:
	friend class Process;

	string name;		//玩家名字
	//设置玩家
	Player();
	Player(const Player& other);
	//逻辑等于
	const Player & operator=(const Player& other);
	//重载输出
	friend ostream& operator <<(ostream& os, const Player& player);

	~Player();

	//玩家手中加牌
	void handCardAdd(Card temp);
	//玩家手中减牌
	Card handCardRemove(int pos);
	//打印玩家
	void printPlayer();
	//获取玩家手牌数量
	int getHandCardSize();
	//玩家初始化
	void initPlayer(Deck deck);

	vector<Card> getPlayerCards(); //获取当前玩家的手牌容器，主要为机器人服务
	

private:
	const std::string mUsername;
	//设置类：卡牌元素
	class card_elem {
	public:
		card_elem() {
			next = NULL;
		}
		card_elem* next;
		Card data;
	};
	int hand_size;
	card_elem* head;
	void copy(const Player& other);
	void clear();
	
};

