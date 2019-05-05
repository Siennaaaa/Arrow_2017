#ifndef __HIT_BRICK_H__
#define __HIT_BRICK_H__

#include "cocos2d.h"
using namespace std;
USING_NS_CC;
class HitBrick : public Layer {
public:

  virtual bool init();
  static cocos2d::Scene* createScene();
  void EnterGameScene(cocos2d::Ref * pSender);//菜单回调至游戏开始界面
  CREATE_FUNC(HitBrick);
};

#endif // __HIT_BRICK_H__
