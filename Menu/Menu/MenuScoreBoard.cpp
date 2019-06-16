#include "MenuScoreBoard.h"
USING_NS_CC;


void MenuScoreBoard::closeScene(Ref* pSender)
{
	Director::getInstance()->popScene();

}

bool MenuScoreBoard::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("background_menu_02.png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bg);

	initData();
	setclassic();
	_showmode = Label::createWithTTF("Normal", "fonts/arial.ttf", 48);
	_showmode->setPosition(800, 800);///
	addChild(_showmode);

	

	auto preMode = MenuItemImage::create("button_next_r.png", "button_next_selected_r.png", CC_CALLBACK_1(MenuScoreBoard::prevMode, this));
	preMode->setPosition(550, 800);////
	auto nextMode = MenuItemImage::create("button_next.png", "button_next_selected.png", CC_CALLBACK_1(MenuScoreBoard::nextMode, this));
	nextMode->setPosition(1050, 800);///

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(MenuScoreBoard::closeScene, this));
	float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
	float y = origin.y + closeItem->getContentSize().height / 2;
	closeItem->setPosition(Vec2(x, y));///

	auto menu = Menu::create(closeItem,preMode,nextMode, NULL);////
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	return true;
}

void MenuScoreBoard::initData()
{
	bool flag_classic = true;
	bool flag_AI = true;
	for (int i = 0; i < 10; i++)
	{
		if (flag_classic)
		{
			classic_data temp_c;
			temp_c.score = UserDefault::getInstance()->getIntegerForKey(StringUtils::format("Normal_score_%d", i).c_str(), -1);
			if (temp_c.score != -1)
			{
				temp_c.brick = UserDefault::getInstance()->getIntegerForKey(StringUtils::format("Normal_brick_%d", i).c_str(), -1);
				temp_c.level = UserDefault::getInstance()->getIntegerForKey(StringUtils::format("Normal_level_%d", i).c_str(), -1);
				_v_classic.push_back(temp_c);
			}
			else
			{
				flag_classic = false;
			}
			
		}
		if (flag_AI)
		{
			AI_data temp_p;
			temp_p.score = UserDefault::getInstance()->getIntegerForKey(StringUtils::format("AI_score_%d", i).c_str(), -1);
			if (temp_p.score != -1)
			{
				temp_p.my_goal = UserDefault::getInstance()->getIntegerForKey(StringUtils::format("AI_mygoal_%d", i).c_str(), -1);
				temp_p.op_goal = UserDefault::getInstance()->getIntegerForKey(StringUtils::format("AI_opgoal_%d", i).c_str(), -1);
				temp_p.level = UserDefault::getInstance()->getIntegerForKey(StringUtils::format("AI_level_%d", i).c_str(), -1);
				_v_AI.push_back(temp_p);
			}
			else
			{
				flag_AI = false;
			}

		}
	}
	float start_x=600;//
	float start_y=700;
	float gap_x=200;//
	float gap_y=50;
	for (int i = 0; i < 11; i++)
	{
		string score("--");
		string special("--");
		string level("--");
		if (i == 0)
		{
			score = "Score";
			special = "Special";
			level = "Level";
		}
		auto showscore = Label::createWithTTF(score, "fonts/arial.ttf", 48);
		showscore->setPosition(start_x + gap_x*0, start_y - gap_y * i);
		addChild(showscore);
		_v_showscore.push_back(showscore);

		auto showspecial = Label::createWithTTF(special, "fonts/arial.ttf", 48);
		showspecial->setPosition(start_x + gap_x*1, start_y - gap_y * i);
		addChild(showspecial);
		_v_showspecial.push_back(showspecial);

		auto showlevel = Label::createWithTTF(level, "fonts/arial.ttf", 48);
		showlevel->setPosition(start_x + gap_x*2, start_y - gap_y * i);
		addChild(showlevel);
		_v_showlevel.push_back(showlevel);

	}
}
void MenuScoreBoard::prevMode(cocos2d::Ref* pSender)
{
	if (_current_gamemode != 1)
	{
		_current_gamemode--;
		switch (_current_gamemode)
		{
		case 1:
		{
			_showmode->setString("Normal");
			setclassic();
			break;
		}
		case 2:
		{
			_showmode->setString("AI");
			setAI();
			break;
		}
	
		}
	}
}
void MenuScoreBoard::nextMode(cocos2d::Ref* pSender)
{
	if (_current_gamemode != 3)
	{
		_current_gamemode++;
		switch (_current_gamemode)
		{
		case 1:
		{
			_showmode->setString("Normal");
			setclassic();
			break;
		}
		case 2:
		{
			_showmode->setString("AI");
			setAI();
			break;
		}
		
		}
	}
}
void MenuScoreBoard::setclassic()
{
	_v_showspecial.at(0)->setString("Brick");
	for (int i = 1; i < 11; i++)
	{
		_v_showscore.at(i)->setString("--");
		_v_showspecial.at(i)->setString("--");
		_v_showlevel.at(i)->setString("--");
	}
	for (size_t i = 0; i < _v_classic.size(); i++)
	{
		size_t j = i + 1;
		_v_showscore.at(j)->setString(StringUtils::format("%d", _v_classic.at(i).score));
		_v_showspecial.at(j)->setString(StringUtils::format("%d", _v_classic.at(i).brick));
		if(_v_classic.at(i).level>10000)
			_v_showlevel.at(j)->setString(StringUtils::format("User-%d", _v_classic.at(i).level-10000));
		else
			_v_showlevel.at(j)->setString(StringUtils::format("%d", _v_classic.at(i).level));
		
	}
}
void MenuScoreBoard::setAI()
{
	_v_showspecial.at(0)->setString("VS");
	for (int i = 1; i < 11; i++)
	{
		_v_showscore.at(i)->setString("--");
		_v_showspecial.at(i)->setString("--");
		_v_showlevel.at(i)->setString("--");
	}
	for (size_t i = 0; i < _v_AI.size(); i++)
	{
		size_t j = i + 1;
		_v_showscore.at(j)->setString(StringUtils::format("%d", _v_AI.at(i).score));
		_v_showspecial.at(j)->setString(StringUtils::format("%d:%d", _v_AI.at(i).my_goal, _v_AI.at(i).op_goal));
		if (_v_AI.at(i).level > 10000)
			_v_showlevel.at(j)->setString(StringUtils::format("User-%d", _v_AI.at(i).level - 10000));
		else
			_v_showlevel.at(j)->setString(StringUtils::format("%d", _v_AI.at(i).level));
	}
}

void MenuScoreBoard::clearClassic(cocos2d::Ref* pSender)
{
	UserDefault::getInstance()->setIntegerForKey("Normal_played", 0);
	UserDefault::getInstance()->setIntegerForKey("Normal_average", 0);
	UserDefault::getInstance()->setIntegerForKey("Normal_maxscore", 0);
	for (int i = 0; i < 10; i++)
	{
		UserDefault::getInstance()->setIntegerForKey(StringUtils::format("Normal_score_%d",i).c_str(), -1);
	}
}
void MenuScoreBoard::clearAI(cocos2d::Ref* pSender)
{
	UserDefault::getInstance()->setIntegerForKey("AI_played", 0);
	UserDefault::getInstance()->setIntegerForKey("AI_average", 0);
	UserDefault::getInstance()->setIntegerForKey("AI_win", 0);
	UserDefault::getInstance()->setIntegerForKey("AI_maxscore", 0);
	for (int i = 0; i < 10; i++)
	{
		UserDefault::getInstance()->setIntegerForKey(StringUtils::format("AI_score_%d", i).c_str(), -1);
	}
}
