#ifndef __USER_LAYER_H__
#define __USER_LAYER_H__

#include "cocos2d.h"
using namespace cocos2d;
using namespace std;
struct classic_data
{
	int score;
	int brick;
	int level;
	classic_data(int s, int b, int l) :score(s), brick(b), level(l) {}
	classic_data(){}
	bool operator<(classic_data b) { return this->score > b.score; }
};
struct AI_data
{
	int score;
	int my_goal;
	int op_goal;
	int level;
	AI_data(int s, int m,int o, int l) :score(s), my_goal(m),op_goal(o), level(l) {}
	AI_data() {}
	bool operator<(AI_data b) { return this->score > b.score; }
}; 
struct Two_data
{
	int score;
	int time;
	int level;
	Two_data(int s, int t, int l) :score(s), time(t), level(l) {}
	Two_data() {}
	bool operator<(Two_data b) { return this->score > b.score; }
};
class MenuScoreBoard :public cocos2d::Layer
{
public:
	CREATE_FUNC(MenuScoreBoard);
	virtual bool init();
	void closeScene(cocos2d::Ref* pSender);
	void initData();

	void clearClassic(cocos2d::Ref* pSender);
	void clearAI(cocos2d::Ref* pSender);
	void clearTwo(cocos2d::Ref* pSender);
	void prevMode(cocos2d::Ref* pSender);
	void nextMode(cocos2d::Ref* pSender);
	void setclassic();
	void setAI();
	void setTwo();
private:
	int _current_gamemode=1;
	Label* _showmode;
	vector<classic_data> _v_classic;
	vector<AI_data> _v_AI;
	vector<Two_data> _v_Two;
	vector<Label*> _v_showscore;
	vector<Label*> _v_showspecial;
	vector<Label*> _v_showlevel;
};
#endif
