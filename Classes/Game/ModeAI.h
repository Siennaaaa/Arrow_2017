#ifndef __GAME_AI_H__
#define __GAME_AI_H__
#include "cocos2d.h"
#include "Game.h"

class ModeAI :public Game
{
public:
	virtual void initMode() override;
	//����ģʽ
	virtual void updateMode() override;
	//����ģʽ
	virtual void createHUDMode() override;
	virtual void recordBrick(Brick* brick) override;
	//��¼ש���λ��
	virtual void writeScoreToUserData() override;
	//������д�����а���
	static cocos2d::Scene* createSceneAI(int life, int level, int difficulty);
	void updateTime(float delta);
	//����ʱ�亯��
	void generateBricks();
	//��¼֮ǰ��ש��λ��
	void oppositeAI(float delta);
	//��ս��AI����
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


