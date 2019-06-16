#ifndef __GAME_TWO_H__
#define __GAME_TWO_H__
#include "cocos2d.h"
#include "Game.h"

class ModeTwo :public Game
{
public:
	virtual void initMode() override;
	//建立双人模式场景
	virtual void updateMode() override;
	//更新双人模式
	virtual void createHUDMode() override;
	//创建左边信息栏
	virtual void recordBrick(Brick* brick) override;
	//记录砖块的位置
	virtual void writeScoreToUserData() override;
	//游戏结束后把数据写入排行榜
	static cocos2d::Scene* createSceneTwo(int life, int level, int difficulty);
	//创建场景
	void updateTime(float delta);
	//更新时间函数
	void generateBricks();
	//记录砖块位置函数
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode code, Event * event);
	//按键按下函数
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode code, Event * event);
	//按键松开函数
	CREATE_FUNC(ModeTwo);
protected:

	Plate* _player_opposite;
	Deadzone* _deadzone_opposite;
	cocos2d::Label* _showlife_opposite;
	int _generatetime = 10;
	int _shoot_waittime = 24;
	std::vector<cocos2d::Vec2> V_destroyedbricks;
};

#endif


