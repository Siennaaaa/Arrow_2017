#ifndef __USER_LEVEL_SELECTION_H__
#define __USER_LEVEL_SELECTION_H__

#include "cocos2d.h"
#include "Level.h"
class ChooseLevel :public Level
{
public:
	static cocos2d::Scene* createScene();
	CREATE_FUNC(ChooseLevel);
	virtual void createLevelSelection(float y_start);
	virtual void openlevel(cocos2d::Ref* pSender);
	void addLevel(cocos2d::Ref* pSender);
	void cutLevel(cocos2d::Ref* pSender);
protected:
	cocos2d::Label* _show_info;

};
#endif


