#include"ModeTwo.h"
#include"ModeTwo.h"
using namespace cocos2d;

Scene*  ModeTwo::createSceneTwo(int life, int level, int difficulty)
//建立双人模式场景
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	auto layer = ModeTwo::create();
	layer->_life = life;
	layer->_level = level;
	layer->_player1->setLife(life);
	layer->_player_opposite->setLife(life);
	layer->initAfter();
	scene->addChild(layer);
	return scene;
}

void ModeTwo::initMode()
//双人模式
{
	createPlayerSide(2, _player_opposite, _deadzone_opposite);
	_ball_side = _player1;
	this->schedule(schedule_selector(ModeTwo::updateTime), 1.0f);
}
void ModeTwo::updateMode()
//更新双人模式
{
	collisionDetection(_player_opposite);

	if (!V_balls.empty())
		if (!isRoundStarted&&_ball_side == _player_opposite)
		{
			if (V_balls.back()->getPositionX() != _player_opposite->getPositionX())
			{
				V_balls.back()->setPositionX(_player_opposite->getPositionX());
			}
		}

	if (balltodestroy)
	{
		auto player = balltodestroy->getPlateBelongto();
		destroyball(balltodestroy);
		balltodestroy = nullptr;
		player->damaged();
		_showlife->setString(StringUtils::format("%d", _player1->getLife()));
		_showlife_opposite->setString(StringUtils::format("%d", _player_opposite->getLife()));

		if (_player1->getLife() == 0)
		{
			this->unschedule(schedule_selector(ModeTwo::updateTime));
			_player_opposite->stopMoving();
			gameOver(true, false);
		}
		else if (_player_opposite->getLife() == 0)
		{
			this->unschedule(schedule_selector(ModeTwo::updateTime));
			_player_opposite->stopMoving();
			gameOver(true, true);
		}
		else if (V_balls.empty())
		{
			_point_multiple = 10;
			_show_point_multi->setString("10");
			if (_ball_side == _player1)
				_ball_side = _player_opposite;
			else
				_ball_side = _player1;
			createballforPlate(_ball_side);
			isRoundStarted = false;
		}
	}
}
void ModeTwo::createHUDMode()
//建立双人模式左边信息栏
{
	float x = _gamescreen.getMinX() / 2;
	float y = _gamescreen.getMaxY();

	auto tlife = Label::createWithTTF("P2 Life:", "fonts\\arial.ttf", 48, Size::ZERO, cocos2d::TextHAlignment::LEFT);  //////
	tlife->setColor(Color3B::BLACK);
	auto str = StringUtils::format("%d", _life);
	_showlife_opposite = Label::createWithTTF(str, "fonts\\arial.ttf", 48, Size::ZERO, cocos2d::TextHAlignment::CENTER);
	tlife->setPosition(x, y - 450);
	_showlife_opposite->setPosition(x, y - 500);
	this->addChild(tlife);
	this->addChild(_showlife_opposite);
}
void ModeTwo::recordBrick(Brick* brick)
//记录砖块的位置
{
	Vec2 vec(brick->getPositionX(), brick->getPositionY());
	V_destroyedbricks.push_back(vec);
}
void ModeTwo::updateTime(float delta)
//更新时间
{
	if (_generatetime < 10)
		_generatetime++;
	if (_generatetime >= 10 || brickcount < allbrickcount / 2)
	{
		if (!V_destroyedbricks.empty())
		{
			generateBricks();
			_generatetime = 0;
		}

	}
}
void ModeTwo::generateBricks()
//记录之前的砖块位置
{
	if (V_destroyedbricks.empty())
		return;

	auto it = V_destroyedbricks.begin();
	float x = it->x;
	float y = it->y;
	int seed = random() % 10;
	Brick* brick;
	if (seed < 2)
	{
		brick = Brick::create("brick_addPoint.png", 1, 2);
	}
	else if (seed < 7)
	{
		brick = Brick::create("brick_1.png", 1, 1);
	}
	else
	{
		brick = Brick::create("brick_52.png", 1, 1, false, true);
	}
	LOG_INFO("Bonus Brick!");
	brickcount++;
	brick->initWithData(x, y);
	this->addChild(brick);
	V_destroyedbricks.erase(it);
}

void ModeTwo::onKeyPressed(cocos2d::EventKeyboard::KeyCode code, Event* event)
//按下按键后控制板的移动
{

	switch (code)
	{
	case EventKeyboard::KeyCode::KEY_A:
	{
		_player1->moveLeft();
		break;
	}
	case EventKeyboard::KeyCode::KEY_D:
	{
		_player1->moveRight();
		break;
	}
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:   //
	{
		_player_opposite->moveLeft();
		break;
	}
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	{
		_player_opposite->moveRight();
		break;
	}
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	{
		if (!isRoundStarted)
			if (_ball_side == _player_opposite)
			{
				V_balls.back()->shootBall(_player_opposite);
				isRoundStarted = true;
			}
		break;
	}
	case EventKeyboard::KeyCode::KEY_SPACE:
	{
		if (!isRoundStarted)
			if (_ball_side == _player1)
			{
				V_balls.back()->shootBall(_player1);
				isRoundStarted = true;
			}
		break;
	}
	default:
		break;
	}
}

void ModeTwo::onKeyReleased(cocos2d::EventKeyboard::KeyCode code, Event* event)
//松开按键后使得板停止移动
{
	switch (code)
	{
	case EventKeyboard::KeyCode::KEY_A:
	{
		_player1->stopLeft();
		break;
	}
	case EventKeyboard::KeyCode::KEY_D:
	{
		_player1->stopRight();
		break;
	}
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	{
		_player_opposite->stopLeft();
		break;
	}
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	{
		_player_opposite->stopRight();
		break;
	}
	default:
		break;
	}
}

void ModeTwo::writeScoreToUserData()
//游戏结束后把数据写入排行榜中
{
	vector<AI_data> v_AI;
	int finalscore = _score;
	for (int i = 0; i < 10; i++)
	{
		string score = StringUtils::format("AI_score_%d", i);
		string mygoal = StringUtils::format("AI_mygoal_%d", i);
		string opgoal = StringUtils::format("AI_opgoal_%d", i);
		string level = StringUtils::format("AI_level_%d", i);
		int s;
		if ((s = UserDefault::getInstance()->getIntegerForKey(score.c_str(), -1)) == -1)
			break;
		else
		{
			AI_data temp;
			temp.score = s;
			temp.my_goal = UserDefault::getInstance()->getIntegerForKey(mygoal.c_str(), -1);
			temp.op_goal = UserDefault::getInstance()->getIntegerForKey(opgoal.c_str(), -1);
			temp.level = UserDefault::getInstance()->getIntegerForKey(level.c_str(), -1);
			v_AI.push_back(temp);
		}
	}
	v_AI.push_back(AI_data(finalscore, _life - _player_opposite->getLife(), _life - _player1->getLife(), _level));
	sort(v_AI.begin(), v_AI.end());
	for (size_t i = 0; i < (v_AI.size() < 10 ? v_AI.size() : 10); i++)
	{
		string score = StringUtils::format("AI_score_%d", i);
		string mygoal = StringUtils::format("AI_mygoal_%d", i);
		string opgoal = StringUtils::format("AI_opgoal_%d", i);
		string level = StringUtils::format("AI_level_%d", i);
		UserDefault::getInstance()->setIntegerForKey(score.c_str(), v_AI.at(i).score);
		UserDefault::getInstance()->setIntegerForKey(mygoal.c_str(), v_AI.at(i).my_goal);
		UserDefault::getInstance()->setIntegerForKey(opgoal.c_str(), v_AI.at(i).op_goal);
		UserDefault::getInstance()->setIntegerForKey(level.c_str(), v_AI.at(i).level);
	}

	int time = UserDefault::getInstance()->getIntegerForKey("AI_played", 0);
	int average = UserDefault::getInstance()->getIntegerForKey("AI_average", 0);
	int win = UserDefault::getInstance()->getIntegerForKey("AI_win", 0);
	int maxscore = UserDefault::getInstance()->getIntegerForKey("AI_maxscore", 0);

	average = (average*time + finalscore) / (time + 1);
	time++;
	maxscore = maxscore > _score ? maxscore : _score;
	if (_player1->getLife() > _player_opposite->getLife())
		win++;
	UserDefault::getInstance()->setIntegerForKey("AI_played", time);
	UserDefault::getInstance()->setIntegerForKey("AI_win", win);
	UserDefault::getInstance()->setIntegerForKey("AI_average", average);
	UserDefault::getInstance()->setIntegerForKey("AI_maxscore", maxscore);
}