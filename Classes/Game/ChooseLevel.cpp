#include "ChooseLevel.h"
#include<fstream>
USING_NS_CC;
using namespace std;
#include "Game.h"
#include "ModeAI.h"
#include "ModeTwo.h"

Scene* ChooseLevel::createScene()
{
	auto scene = Scene::create();
	auto layer = ChooseLevel::create();
	scene->addChild(layer);
	return scene;
}
void ChooseLevel::createLevelSelection(float y_start)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_currentlevel = 10001;
	_showlevel->setString(StringUtils::format("Level\nUser\n%d", _currentlevel - 10000));
	_show_info=Label::createWithTTF("Existed File", "fonts\\arial.ttf", 48, Size::ZERO, cocos2d::TextHAlignment::CENTER);
	std::string filename = StringUtils::format("levels/user_levels/level_%d.json", _currentlevel - 10000);
	ifstream infile(filename);
	if (!infile)
		_show_info->setString("No File");
	infile.close();
	auto book = Sprite::create("menu/menu_book.png");
	auto preLevel = MenuItemImage::create("button_next_r.png", "button_next_selected_r.png", CC_CALLBACK_1(ChooseLevel::cutLevel, this));
	auto nextLevel = MenuItemImage::create("button_next.png", "button_next_selected.png", CC_CALLBACK_1(ChooseLevel::addLevel, this));
	float y1 = book->getContentSize().height / 2;
	float y2 = 100;
	float x3 = visibleSize.width / 2;
	float x2 = x3 - book->getContentSize().width / 4;
	float x4 = x3 + book->getContentSize().width / 4;
	float x1 = x3 - book->getContentSize().width / 2-nextLevel->getContentSize().width/2;
	float x5 = x3 + book->getContentSize().width / 2 + nextLevel->getContentSize().width / 2;
	book->setPosition(x3, y1); book->setLocalZOrder(-1);
	_showlevel->setPosition(x2, y1); _showlevel->setColor(Color3B::BLACK);
	_show_info->setPosition(x4, y1); _show_info->setColor(Color3B::BLACK);
	preLevel->setPosition(x1, y1);
	nextLevel->setPosition(x5, y1);
	auto menu = Menu::create(nextLevel,preLevel, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	this->addChild(book);
	this->addChild(_show_info);
}
void ChooseLevel::addLevel(Ref* pSender)
{
	_currentlevel++;
	_showlevel->setString(StringUtils::format("Level\nUser\n%d", _currentlevel - 10000));
	std::string filename = StringUtils::format("levels/user_levels/level_%d.json", _currentlevel - 10000);
	ifstream infile(filename);
	if (infile)
	{
		_show_info->setString("Existed File");
	}
	else
	{
		_show_info->setString("No File");
	}
	infile.close();
}
void ChooseLevel::cutLevel(Ref* pSender)
{
	if (_currentlevel != 10001)
	{
		_currentlevel--;
		_showlevel->setString(StringUtils::format("Level\nUser\n%d", _currentlevel - 10000));
		std::string filename = StringUtils::format("levels/user_levels/level_%d.json", _currentlevel - 10000);
		ifstream infile(filename);
		if (infile)
		{
			_show_info->setString("Existed File");
		}
		else
		{
			_show_info->setString("No File");
		}
		infile.close();
	}


}
void ChooseLevel::openlevel(cocos2d::Ref* pSender)
{
	if (_show_info->getString() == "Existed File")
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
}