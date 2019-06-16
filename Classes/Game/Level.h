#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "cocos2d.h"


class Level :public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	CREATE_FUNC(Level);
	//建立关卡选择场景
	virtual bool init();

	virtual void createLevelSelection(float y_start);
	//关卡选择函数
	void closeScene(cocos2d::Ref* pSender);
	//关闭场景函数
	void addmode(cocos2d::Ref* pSender);
	//增加模式函数
	void minusmode(cocos2d::Ref* pSender);
	//设置模式函数
	void addlife(cocos2d::Ref* pSender);
	//增加生命函数
	void minuslife(cocos2d::Ref* pSender);
	//控制最小生命

	void setlevel(int level);
	//设置关卡函数
	virtual void openlevel(cocos2d::Ref* pSender);
	//打开关卡函数
	enum GameMode {
		Classic,
		AI,
		Two
	};
	const int MaxLevel = 18;
	const int MaxMode = 3;
	const int MaxLife = 10;
	const int MaxTime = 180;
protected:
	GameMode _currentmode;
	int _currentlife;
	int _currenttime;
	int _currentlevel;
	int _currentdifficulty;
	cocos2d::Label* _showmode;
	cocos2d::Label* _showlife;
	cocos2d::Label* _showtime;
	cocos2d::Label* _showlevel;
	cocos2d::Label* _showdifficulty;
	cocos2d::Label* _title_difficulty;
	cocos2d::MenuItemImage* _change_difficulty;
public:
	void setAIVisible(bool b)
	{
		_showdifficulty->setVisible(b);
		_title_difficulty->setVisible(b);
		_change_difficulty->setVisible(b);
	}
};
#endif

