#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class Breakout :public Layer {
public:
	static int Score;

	void setPhysicsWorld(PhysicsWorld * world);
	// there's no 'id' in cpp, so we recommend returning the class instance pointer//
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init(PhysicsWorld* world);

    // implement the "static create()" method manually
	static Breakout* create(PhysicsWorld* world);

private:
    Sprite* player;
	PhysicsWorld* m_world;
	Size visibleSize;
	Point origin;
	Sprite* ball;
	Sprite* ball2;
	int blocknum;
	int flag = 0;
	cocos2d::Label* ScoreLabel;
//��ؼ��صĺ���
    void preloadMusic();
    void playBgm();

    void addBackground();
	void addball();
	void addpea();
//������ĺ���
	void addContactListener();
	void addKeyboardListener();
//������
	void update(float f);
//���º���
	bool onConcactBegan(PhysicsContact& contact);
    void onKeyPressed(EventKeyboard::KeyCode code, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode code, Event* event);

};