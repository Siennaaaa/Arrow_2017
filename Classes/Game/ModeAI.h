#ifndef __GAME_AI_H__
#define __GAME_AI_H__
#include "cocos2d.h"
#include "Game.h"

class ModeAI :public Game
{
public:
	virtual void initMode() override;
	//建立模式
	virtual void updateMode() override;
	//更新模式
	virtual void createHUDMode() override;
	virtual void recordBrick(Brick* brick) override;
	//记录砖块的位置
	virtual void writeScoreToUserData() override;
	//把数据写入排行榜中
	static cocos2d::Scene* createSceneAI(int life, int level, int difficulty);
	void updateTime(float delta);
	//更新时间函数
	void generateBricks();
	//记录之前的砖块位置
	void oppositeAI(float delta);
	//对战的AI函数
	CREATE_FUNC(ModeAI);
protected:
	
	Plate* _player_opposite;
	Deadzone* _deadzone_opposite;
	cocos2d::Label* _showlife_opposite;
	int _generatetime = 10;
	int _shoot_waittime = 24;
	std::vector<cocos2d::Vec2> V_destroyedbricks;
};

#endif


