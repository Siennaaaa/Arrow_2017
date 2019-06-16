#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"

class MenuLayer :public cocos2d::Layer
{
public:

	CREATE_FUNC(MenuLayer);
	static cocos2d::Scene* createScene();
	virtual bool init() override;
	virtual void onEnter() override;
	void closeScene(cocos2d::Ref* pSender);
	void MenuLayer::switchToFreeSelete(cocos2d::Ref* pSender);
	void popToAbout(cocos2d::Ref* pSender);
	void PoptoUser(cocos2d::Ref* pSender);
	void preloadResources();
	void unloadResources();
};
#endif