#include "Level.h"
USING_NS_CC;
#include "ui/CocosGUI.h"
using namespace ui;
#include "Game.h"
#include "ModeAI.h"
#include "ModeTwo.h"

Scene* Level::createScene()
//建立不同的关卡
{
	auto scene = Scene::create();
	auto layer = Level::create();
	scene->addChild(layer);
	return scene;
}

void Level::closeScene(Ref* pSender)
//关闭关卡场景函数
{

	if (_currentlevel <= 10000)
		UserDefault::getInstance()->setIntegerForKey("default_level", _currentlevel);
	UserDefault::getInstance()->setIntegerForKey("default_life", _currentlife);
	UserDefault::getInstance()->setIntegerForKey("default_time", _currenttime);
	UserDefault::getInstance()->setIntegerForKey("default_difficulty", _currentdifficulty);
	UserDefault::getInstance()->setIntegerForKey("default_mode", static_cast<int>(_currentmode));
	Director::getInstance()->popScene();

}

void Level::addmode(cocos2d::Ref* pSender)
//可以选择不同的模式
{
	if ((int)_currentmode < MaxMode - 1)
	{
		_currentmode = (GameMode)((int)_currentmode + 1);
	}
	switch (_currentmode)
	{
	case Classic:
		//普通的单人打砖块模式
	{
		_showmode->setString("Normal");
		setAIVisible(false); break;
	}
	case AI:
		//玩家与电脑对战模式
	{
		_showmode->setString("AI");
		setAIVisible(true); break;
	}
	case Two:
		//双人对战模式
	{
		_showmode->setString("Two");
		setAIVisible(false); break;
	}
	}
}
void Level::minusmode(cocos2d::Ref* pSender)
//各个模式的延伸
{
	if ((int)_currentmode != 0)
	{
		_currentmode = (GameMode)((int)_currentmode - 1);
	}
	switch (_currentmode)
	{
	case Classic:
	{
		_showmode->setString("Normal");
		setAIVisible(false); break;
	}
	case AI:
	{
		_showmode->setString("AI");
		setAIVisible(true); break;
	}
	case Two:
	{
		_showmode->setString("Two");
		setAIVisible(false); break;
	}
	}
}
void Level::addlife(cocos2d::Ref* pSender)
//增加生命的函数
{
	if (_currentlife < MaxLife)
	{
		_currentlife++;

		_showlife->setString(StringUtils::format("%d", _currentlife));
	}
}
void Level::minuslife(cocos2d::Ref* pSender)
//控制最小生命的函数
{
	if (_currentlife != 1)
	{
		_currentlife--;

		_showlife->setString(StringUtils::format("%d", _currentlife));
	}
}

void Level::openlevel(cocos2d::Ref* pSender)
//打开关卡的函数
{
	Scene* scene;
	switch (_currentmode)
	{
	case GameMode::Classic:
		scene = Game::createScene(_currentlife, _currentlevel); break;
	case GameMode::AI:
		scene = ModeAI::createSceneAI(_currentlife, _currentlevel, _currentdifficulty); break;
	case GameMode::Two:
		scene = ModeTwo::createSceneTwo(_currentlife, _currentlevel, _currentdifficulty); break;
	}
	Director::getInstance()->pushScene(scene);

}
void Level::setlevel(int level)
//放置关卡按钮的函数
{
	this->_currentlevel = level;
	this->_showlevel->setString(StringUtils::format("Level:%d", level));
}
bool Level::init()
//放置关卡页面的各个按钮
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("background/background_menu_02.png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	bg->setLocalZOrder(-5);
	this->addChild(bg);

	_currentlevel = UserDefault::getInstance()->getIntegerForKey("default_level", 1);
	string level_str = StringUtils::format("Level:%d", _currentlevel);
	_currentlife = UserDefault::getInstance()->getIntegerForKey("default_life", 3);
	string life_str = StringUtils::format("%d", _currentlife);
	_currentmode = static_cast<GameMode>(UserDefault::getInstance()->getIntegerForKey("default_mode", 1));
	string mode_str;
	switch (_currentmode)
	{
	case Classic:	mode_str = "Normal"; break;
	case AI:	mode_str = "AI"; break;
	case Two:	mode_str = "Multi"; break;
	}
	_currenttime = UserDefault::getInstance()->getIntegerForKey("default_time", 90);
	string time_str = StringUtils::format("%d", _currenttime);
	_currentdifficulty = UserDefault::getInstance()->getIntegerForKey("default_difficulty", 2);
	string difficulty_str = StringUtils::format("%d", _currentdifficulty);

	auto tmode = Label::createWithTTF("Mode", "fonts\\arial.ttf", 48, Size::ZERO, cocos2d::TextHAlignment::CENTER);
	auto tlife = Label::createWithTTF("Life", "fonts\\arial.ttf", 48, Size::ZERO, cocos2d::TextHAlignment::CENTER);
	auto ttime = Label::createWithTTF("Time", "fonts\\arial.ttf", 0, Size::ZERO, cocos2d::TextHAlignment::CENTER);
	_showmode = Label::createWithTTF(mode_str, "fonts\\arial.ttf", 48, Size::ZERO, cocos2d::TextHAlignment::CENTER);
	_showlife = Label::createWithTTF(life_str, "fonts\\arial.ttf", 48, Size::ZERO, cocos2d::TextHAlignment::CENTER);
	_showtime = Label::createWithTTF(time_str, "fonts\\arial.ttf", 0, Size::ZERO, cocos2d::TextHAlignment::CENTER);
	_showlevel = Label::createWithTTF(level_str, "fonts\\arial.ttf", 48, Size::ZERO, cocos2d::TextHAlignment::CENTER);

	auto preMode = MenuItemImage::create("button_next_r.png", "button_next_selected_r.png", CC_CALLBACK_1(Level::minusmode, this));
	auto nextMode = MenuItemImage::create("button_next.png", "button_next_selected.png", CC_CALLBACK_1(Level::addmode, this));
	auto lifeprev = MenuItemImage::create("button_next_r.png", "button_next_selected_r.png", CC_CALLBACK_1(Level::minuslife, this));
	auto lifenext = MenuItemImage::create("button_next.png", "button_next_selected.png", CC_CALLBACK_1(Level::addlife, this));
	auto startgame = MenuItemImage::create("button_play.png", "button_play_s.png", CC_CALLBACK_1(Level::openlevel, this));
	//加入各个按钮

	float x1 = 100 + 200;
	float x2 = x1 + 100 + preMode->getContentSize().width / 2;
	float x3 = x2 + 175;
	float x4 = x3 + 100 + nextMode->getContentSize().width / 2;
	float x6 = x4 + 150;
	float x7 = x6 + 175;
	float x5 = visibleSize.width - startgame->getContentSize().width / 2 - 660;
	float y1 = visibleSize.height - 100;
	float y_ai = y1 - 10;
	float y2 = y1 - 100;
	float y5 = y1 - 600;
	float y4 = y2 - 300;
	float y3 = y1 - startgame->getContentSize().height - 300;
	//设置各个按钮的位置

	tmode->setPosition(x1, y1);
	preMode->setPosition(x2, y1);
	_showmode->setPosition(x3, y1);
	nextMode->setPosition(x4, y1);
	tlife->setPosition(x1, y2);
	lifeprev->setPosition(x2, y2);
	_showlife->setPosition(x3, y2);
	lifenext->setPosition(x4, y2);
	ttime->setPosition(x1, y4);
	//timeprev->setPosition(x2, y4);
	_showtime->setPosition(x3, y4);
	//timenext->setPosition(x4, y4);
	_showlevel->setPosition(x5, y5);
	startgame->setPosition(x5, y3);

	this->addChild(tmode);
	this->addChild(tlife);
	this->addChild(ttime);
	this->addChild(_showmode);
	this->addChild(_showlife);
	this->addChild(_showtime);
	this->addChild(_showlevel);

	_change_difficulty = MenuItemImage::create("ui/button_AI.png", "ui/button_AI_s.png",
		//选择AI对战的不同难度
		[=](Ref* psender)
	{
		if (_currentdifficulty != 5)
			_currentdifficulty++;
		else
			_currentdifficulty = 1;
		switch (_currentdifficulty)
		{
		case 1:
			_showdifficulty->setString("D"); break;
		case 2:
			_showdifficulty->setString("C"); break;
		case 3:
			_showdifficulty->setString("B"); break;
		case 4:
			_showdifficulty->setString("A"); break;
		case 5:
			_showdifficulty->setString("S"); break;
		}
		UserDefault::getInstance()->setIntegerForKey("default_difficulty", _currentdifficulty);
	});
	_change_difficulty->setPosition(x7, y_ai);
	_title_difficulty = Label::createWithTTF("AI", "fonts\\arial.ttf", 48, Size::ZERO, cocos2d::TextHAlignment::CENTER);
	_title_difficulty->setPosition(x6, y_ai);
	this->addChild(_title_difficulty);
	switch (_currentdifficulty)
	{
	case 1:_showdifficulty = Label::createWithTTF("D", "fonts\\arial.ttf", 48, Size::ZERO, cocos2d::TextHAlignment::CENTER); break;
	case 2:_showdifficulty = Label::createWithTTF("C", "fonts\\arial.ttf", 48, Size::ZERO, cocos2d::TextHAlignment::CENTER); break;
	case 3:_showdifficulty = Label::createWithTTF("B", "fonts\\arial.ttf", 48, Size::ZERO, cocos2d::TextHAlignment::CENTER); break;
	case 4:_showdifficulty = Label::createWithTTF("A", "fonts\\arial.ttf", 48, Size::ZERO, cocos2d::TextHAlignment::CENTER); break;
	case 5:_showdifficulty = Label::createWithTTF("S", "fonts\\arial.ttf", 48, Size::ZERO, cocos2d::TextHAlignment::CENTER); break;
	}

	_showdifficulty->setPosition(x7, y_ai);
	_showdifficulty->setLocalZOrder(5);
	_showdifficulty->setColor(Color3B::BLACK);
	this->addChild(_showdifficulty);

	auto closeItem = MenuItemImage::create(
		//建立菜单按钮
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(Level::closeScene, this));
	float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
	float y = origin.y + closeItem->getContentSize().height / 2;
	closeItem->setPosition(Vec2(x, y));

	auto menu = Menu::create(closeItem, preMode, nextMode, lifeprev, lifenext, startgame, _change_difficulty, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	if (_currentmode != AI)
		setAIVisible(false);
	createLevelSelection(y3);

	return true;

}
void Level::createLevelSelection(float y_start)
//建立关卡选择按钮
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	for (int i = 0; i < 5; i++)
	{
		auto str = StringUtils::format("%d", i + 1);
		auto num = Label::createWithTTF(str, "fonts\\arial.ttf", 48, Size::ZERO, cocos2d::TextHAlignment::CENTER);
		float lx = visibleSize.width / 6 + visibleSize.width / 6 * (i % 6);/////
		float ly = 350 + y_start - 150 - (y_start + 150) / 3 * (i / 6);////
		num->setPosition(lx, ly);
		this->addChild(num, 2);
		auto imagename = "level_blue.png";
		auto level = Sprite::create(imagename);
		level->setTag(i + 1);
		level->setPosition(lx, ly);
		this->addChild(level, 1);
	}

	auto gameListener = EventListenerTouchOneByOne::create();
	gameListener->onTouchBegan = [=](Touch* touch, Event* event) {
		Vec2 nodeLoca = this->convertToNodeSpace(touch->getLocation());

		for (int i = 0; i < 5; i++)///
		{
			if (this->getChildByTag(i + 1)->getBoundingBox().containsPoint(nodeLoca))
			{
				this->setlevel(i + 1);
			}
		}
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(gameListener, this);
}