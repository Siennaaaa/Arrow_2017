#include "AboutScene.h"
#include <string>
#include "SimpleAudioEngine.h"
#include "Box2D/Box2D.h"
#include "MenuSence.h"
#include "Box2D/Box2D.h"
#pragma execution_character_set("utf-8")
using namespace std;
USING_NS_CC;

Scene* About::createScene()
{
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = About::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
bool About::init()
{

	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bgmap = Sprite::create("2.jpg");
	bgmap->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	Size mywinsize = Director::getInstance()->getWinSize();
	float winw = mywinsize.width; //��ȡ��Ļ ���
	float winh = mywinsize.height;//��ȡ��Ļ�߶�
	float spx = bgmap->getTextureRect().getMaxX();
	float spy = bgmap->getTextureRect().getMaxY();
	bgmap->setScaleX(winw / spx); //���þ��������ű���
	bgmap->setScaleY(winh / spy);
	this->addChild(bgmap, -1);
//���صİ�ť�¼�
	auto startItem = MenuItemImage::create(
		"bga.png",
		"bgb.png",
		CC_CALLBACK_1(About::CancelMenuCallback, this));

	startItem->setPosition(Vec2(visibleSize.width  + origin.x - 60,  origin.y+30));
	startItem->setScale(1.5);
	auto menu = Menu::create(startItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);




}
//���������溯��
void About::CancelMenuCallback(cocos2d::Ref* pSender) {
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5, MenuSence::createScene()));
}