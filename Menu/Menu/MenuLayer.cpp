#include "MenuLayer.h"
#include "MenuAbout.h"
#include "MenuScoreBoard.h"
USING_NS_CC;
#include"SimpleAudioEngine.h"
#include "Game/Level.h"
using namespace CocosDenshion;

Scene* MenuLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = MenuLayer::create();
	scene->addChild(layer);
	return scene;
}
//关闭页面
void MenuLayer::closeScene(Ref* pSender)
{
	unloadResources();
	this->_eventDispatcher->removeAllEventListeners();
	Director::getInstance()->end();
}
//跳转到游戏选择页面
void MenuLayer::switchToFreeSelete(cocos2d::Ref* pSender)
{
	auto scene = Level::createScene();
	Director::getInstance()->pushScene(scene);
}
//跳转到游戏说明页面
void MenuLayer::popToAbout(cocos2d::Ref* pSender)
{
	//SimpleAudioEngine::getInstance()->playEffect("sound/effect/click.wav");
	auto layer = MenuAbout::create();
	auto scene = Scene::create();
	scene->addChild(layer);
	Director::getInstance()->pushScene(scene);
}
//跳转到排行榜
void MenuLayer::PoptoUser(cocos2d::Ref* pSender)
{
	//SimpleAudioEngine::getInstance()->playEffect("sound/effect/click.wav");
	auto layer = MenuScoreBoard::create();
	auto scene = Scene::create();
	scene->addChild(layer);
	Director::getInstance()->pushScene(scene);
}

bool MenuLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("background/background_menu_02.png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bg);

	auto title = Sprite::create("menu\\title.png");
	title->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - title->getContentSize().height / 2));
	this->addChild(title);

	MenuItemFont::setFontName("fonts/arial.ttf");
	MenuItemFont::setFontSize(45);

	//游戏开始
	MenuItemFont *playItem = MenuItemFont::create("Start", CC_CALLBACK_1(MenuLayer::switchToFreeSelete, this));
	playItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - title->getContentSize().height ));


	//游戏设置
	MenuItemFont *aboutItem = MenuItemFont::create("About", CC_CALLBACK_1(MenuLayer::popToAbout, this));
	aboutItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - title->getContentSize().height - 100));

	//排行榜
	MenuItemFont *userItem = MenuItemFont::create("ScoreBoard", CC_CALLBACK_1(MenuLayer::PoptoUser, this));
	userItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - title->getContentSize().height - 200));

	

	auto menu = Menu::create(playItem, aboutItem, userItem, NULL);
	menu->setPosition(Vec2::ZERO);

	this->addChild(menu);

	return true;

}
void MenuLayer::preloadResources()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("designer/design_bricks.plist", "designer/design_bricks.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("game/game_sprite_default.plist", "game/game_sprite_default.png");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/effect/ball_deadzone.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/effect/ball_plate.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/effect/ball_wall.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/effect/brick_damage.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/effect/brick_destroy.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/effect/shoot_ball.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/effect/newItem.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/effect/getItem.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/effect/win.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/effect/lose.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/effect/click.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/effect/pop.wav");
}
void MenuLayer::unloadResources()
{
	SpriteFrameCache::getInstance()->removeSpriteFrames();
	SpriteFrameCache::getInstance()->destroyInstance();
	SimpleAudioEngine::getInstance()->end();
}
void MenuLayer::onEnter()
{
	Layer::onEnter();
	preloadResources();
}