#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "cocos2d.h"


class Level :public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	CREATE_FUNC(Level);
	//�����ؿ�ѡ�񳡾�
	virtual bool init();

	virtual void createLevelSelection(float y_start);
	//�ؿ�ѡ����
	void closeScene(cocos2d::Ref* pSender);
	//�رճ�������
	void addmode(cocos2d::Ref* pSender);
	//����ģʽ����
	void minusmode(cocos2d::Ref* pSender);
	//����ģʽ����
	void addlife(cocos2d::Ref* pSender);
	//������������
	void minuslife(cocos2d::Ref* pSender);
	//������С����

	void setlevel(int level);
	//���ùؿ�����
	virtual void openlevel(cocos2d::Ref* pSender);
	//�򿪹ؿ�����
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

