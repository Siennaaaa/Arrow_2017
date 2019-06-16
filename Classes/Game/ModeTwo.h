#ifndef __GAME_TWO_H__
#define __GAME_TWO_H__
#include "cocos2d.h"
#include "Game.h"

class ModeTwo :public Game
{
public:
	virtual void initMode() override;
	//����˫��ģʽ����
	virtual void updateMode() override;
	//����˫��ģʽ
	virtual void createHUDMode() override;
	//���������Ϣ��
	virtual void recordBrick(Brick* brick) override;
	//��¼ש���λ��
	virtual void writeScoreToUserData() override;
	//��Ϸ�����������д�����а�
	static cocos2d::Scene* createSceneTwo(int life, int level, int difficulty);
	//��������
	void updateTime(float delta);
	//����ʱ�亯��
	void generateBricks();
	//��¼ש��λ�ú���
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode code, Event * event);
	//�������º���
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode code, Event * event);
	//�����ɿ�����
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


