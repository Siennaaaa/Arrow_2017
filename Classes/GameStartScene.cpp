#pragma execution_character_set("utf-8")
#include"GameStartScene.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#define database UserDefault::getInstance()

USING_NS_CC;
using namespace CocosDenshion;

void GameStartScene::setPhysicsWorld(PhysicsWorld* world) { m_world = world; }

//MyFirstScene场景创建实现
Scene* GameStartScene::createScene() {
	srand((unsigned)time(NULL));
	auto scene = Scene::createWithPhysics();

	scene->getPhysicsWorld()->setAutoStep(true);

	// Debug 模式
	// scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0, -300.0f));
	auto layer = GameStartScene::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());
	layer->setJoint();
	scene->addChild(layer);
	return scene;
}

/*
Scene* GameStart::createScene()
{
	auto scene = Scene::create();	//创建一个场景
	auto layer = GameStart::create();//创建一个GameStart层
	scene->addChild(layer);		//把GameStart层加入刚刚创建的场景中，
	return scene;			//返回这个场景
}*/

bool GameStartScene::init()
{
		if (!Layer::init()) {
			return false;
		}
		visibleSize = Director::getInstance()->getVisibleSize();

		auto edgeSp = Sprite::create();  //创建一个精灵
		auto boundBody = PhysicsBody::createEdgeBox(visibleSize, PhysicsMaterial(0.0f, 1.0f, 0.0f), 3);  //edgebox是不受刚体碰撞影响的一种刚体，我们用它来设置物理世界的边界
		edgeSp->setPosition(visibleSize.width / 2, visibleSize.height / 2);  //位置设置在屏幕中央
		edgeSp->setPhysicsBody(boundBody);
		addChild(edgeSp);


		preloadMusic(); // 预加载音效

		addSprite();    // 添加背景和各种精灵
		addListener();  // 添加监听器 
		addPlayer();    // 添加球与板
		BrickGenerated();  // 生成砖块


		schedule(schedule_selector(GameStartScene::update), 0.01f, kRepeatForever, 0.1f);

		onBall = true;

		spHolded = -1;
		spFactor = 0;
		return true;
}
//菜单回调函数的实现
// 关节连接，固定球与板子
// Todo
void GameStartScene::setJoint() {
	Vec2 fixPoint = Vec2(ball->getAnchorPoint().x, ball->getAnchorPoint().y - 30);
	joint1 = PhysicsJointPin::construct(ball->getPhysicsBody(), player->getPhysicsBody(), fixPoint, player->getAnchorPoint());
	m_world->addJoint(joint1);
}



// 预加载音效
void GameStartScene::preloadMusic() {
	auto sae = SimpleAudioEngine::getInstance();
	sae->preloadEffect("gameover.mp3");
	sae->preloadBackgroundMusic("bgm.mp3");
	sae->playBackgroundMusic("bgm.mp3", true);
}

// 添加背景和各种精灵
void GameStartScene::addSprite() {

	// add ship
	ship = Sprite::create("ship.png");
	ship->setScale(visibleSize.width / ship->getContentSize().width * 0.97, 1.2f);
	ship->setPosition(visibleSize.width / 2, 0);
	auto shipbody = PhysicsBody::createBox(ship->getContentSize(), PhysicsMaterial(100.0f, 0.0f, 1.0f));
	shipbody->setCategoryBitmask(0xFFFFFFFF);
	shipbody->setCollisionBitmask(0xFFFFFFFF);
	shipbody->setContactTestBitmask(0xFFFFFFFF);
	shipbody->setTag(Tag::SHIP);
	shipbody->setDynamic(false);
	ship->setPhysicsBody(shipbody);
	this->addChild(ship, 1);

	// add sun and cloud
	auto sunSprite = Sprite::create("sun.png");
	sunSprite->setPosition(rand() % (int)(visibleSize.width - 200) + 100, 550);
	this->addChild(sunSprite);
	auto cloudSprite1 = Sprite::create("cloud.png");
	cloudSprite1->setPosition(rand() % (int)(visibleSize.width - 200) + 100, rand() % 100 + 450);
	this->addChild(cloudSprite1);
	auto cloudSprite2 = Sprite::create("cloud.png");
	cloudSprite2->setPosition(rand() % (int)(visibleSize.width - 200) + 100, rand() % 100 + 450);
	this->addChild(cloudSprite2);
}

// 添加监听器
void GameStartScene::addListener() {
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(GameStartScene::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(GameStartScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameStartScene::onConcactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

// 创建角色
void GameStartScene::addPlayer() {



	player = Sprite::create("bar.png");
	int xpos = visibleSize.width / 2;

	player->setScale(0.1f, 0.1f);
	player->setPosition(Vec2(xpos, ship->getContentSize().height - player->getContentSize().height*0.1f));
	// 设置板的刚体属性
	// Todo

	auto playerBody = PhysicsBody::createBox(player->getContentSize(), PhysicsMaterial(1000.0f, 1.0f, 10.0f));
	playerBody->setCategoryBitmask(0xFFFFFFFF);
	playerBody->setCollisionBitmask(0xFFFFFFFF);
	playerBody->setContactTestBitmask(0xFFFFFFFF);
	playerBody->setGravityEnable(false);
	playerBody->setTag(Tag::BOARD);
	player->setPhysicsBody(playerBody);
	player->getPhysicsBody()->setRotationEnable(false);

	this->addChild(player, 2);

	ball = Sprite::create("ball.png");
	ball->setPosition(Vec2(xpos, player->getPosition().y + ball->getContentSize().height*0.1f));
	ball->setScale(0.1f, 0.1f);
	// 设置球的刚体属性
	// Todo
	auto ballBody = PhysicsBody::createCircle(ball->getContentSize().height / 2, PhysicsMaterial(0.1f, 1.0f, 0.0f));

	ballBody->setCategoryBitmask(0xFFFFFFFF);
	ballBody->setCollisionBitmask(0xFFFFFFFF);
	ballBody->setContactTestBitmask(0xFFFFFFFF);
	ballBody->setGravityEnable(false);
	ballBody->setTag(Tag::BALL);
	ballBody->setRotationEnable(false);
	ball->setPhysicsBody(ballBody);

	addChild(ball, 3);

}

// 实现简单的蓄力效果
// Todo

void GameStartScene::update(float dt) {
	if (player->getPosition().x < 100) {
		player->setPosition(100, player->getPosition().y);
		player->getPhysicsBody()->setVelocity(Vec2(0, 0));
	}
	else if (player->getPosition().x > visibleSize.width - 100)
	{
		player->setPosition(visibleSize.width - 100, player->getPosition().y);
		player->getPhysicsBody()->setVelocity(Vec2(0, 0));
	}
	if (spHolded == 1)
		spFactor++;
}




// Todo
void GameStartScene::BrickGenerated() {

	for (int i = 0; i < 3; i++) {
		int cw = 30;
		while (cw <= visibleSize.width) {
			auto box = Sprite::create("box.png");
			// 为砖块设置刚体属性
			// Todo
			box->setPosition(cw, visibleSize.height - box->getContentSize().height * (i + 1));
			cw += box->getContentSize().width;

			auto boxBody = PhysicsBody::createCircle(box->getContentSize().height / 2, PhysicsMaterial(100.0f, 1.0f, 0.0f));
			boxBody->setCategoryBitmask(0xFFFFFFFF);
			boxBody->setCollisionBitmask(0xFFFFFFFF);
			boxBody->setContactTestBitmask(0xFFFFFFFF);
			boxBody->setGravityEnable(false);
			boxBody->setTag(Tag::BOX);
			boxBody->setDynamic(false);
			box->setPhysicsBody(boxBody);
			box->getPhysicsBody()->setRotationEnable(false);

			addChild(box, 4);
		}
	}

}


// 左右
void GameStartScene::onKeyPressed(EventKeyboard::KeyCode code, Event* event) {

	switch (code) {
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		if (player->getPosition().x > 100) {
			player->getPhysicsBody()->setVelocity(Vec2(-500, 0));
		}
		else {
			//player->setPosition(100, player->getPosition().y);
			player->getPhysicsBody()->setVelocity(Vec2(0, 0));
		}
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		// 左右移动
		// Todo
		if (player->getPosition().x < visibleSize.width - 100) {
			player->getPhysicsBody()->setVelocity(Vec2(500, 0));
		}
		else {
			//player->setPosition(visibleSize.width-100,player->getPosition().y);
			player->getPhysicsBody()->setVelocity(Vec2(0, 0));
		}
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_SPACE: // 开始蓄力
		if (spHolded == -1)
			spHolded = 1;
		break;
	default:
		break;
	}
}

// 释放按键
void GameStartScene::onKeyReleased(EventKeyboard::KeyCode code, Event* event) {
	switch (code) {
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		// 停止运动
		// Todo
		player->getPhysicsBody()->setVelocity(Vec2(0, 0));
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:   // 蓄力结束，小球发射
		if (spHolded == 1) {
			spHolded = 0;
			m_world->removeJoint(joint1);
			ball->getPhysicsBody()->setVelocity(Vec2(0, spFactor * 30));
		}
		break;

	default:
		break;
	}
}

// 碰撞检测
// Todo
bool GameStartScene::onConcactBegin(PhysicsContact & contact) {
	auto c1 = contact.getShapeA()->getBody(), c2 = contact.getShapeB()->getBody();
	auto s1 = (Sprite*)c1->getNode(), s2 = (Sprite*)c2->getNode();
	auto rain = ParticleRain::create();
	if (c1->getTag() == Tag::BOX && c2->getTag() == Tag::BALL) {
		//下雨
		rain->setPosition(s1->getPosition());
		addChild(rain);
		s1->removeFromParentAndCleanup(true);
	}
	else if (c2->getTag() == Tag::BOX && c1->getTag() == Tag::BALL) {
		rain->setPosition(s2->getPosition());
		addChild(rain);
		s2->removeFromParentAndCleanup(true);
	}
	else if (c1->getTag() == Tag::SHIP && c2->getTag() == Tag::BALL ||
		c2->getTag() == Tag::SHIP && c1->getTag() == Tag::BALL) {
		GameOver();
	}
	return true;
}


void GameStartScene::GameOver() {

	_eventDispatcher->removeAllEventListeners();
	ball->getPhysicsBody()->setVelocity(Vec2(0, 0));
	player->getPhysicsBody()->setVelocity(Vec2(0, 0));
	SimpleAudioEngine::getInstance()->stopBackgroundMusic("bgm.mp3");
	SimpleAudioEngine::getInstance()->playEffect("gameover.mp3", false);

	auto label1 = Label::createWithTTF("Game Over~", "fonts/STXINWEI.TTF", 60);
	label1->setColor(Color3B(0, 0, 0));
	label1->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(label1);

	auto label2 = Label::createWithTTF("重玩", "fonts/STXINWEI.TTF", 40);
	label2->setColor(Color3B(0, 0, 0));
	auto replayBtn = MenuItemLabel::create(label2, CC_CALLBACK_1(GameStartScene::replayCallback, this));
	Menu* replay = Menu::create(replayBtn, NULL);
	replay->setPosition(visibleSize.width / 2 - 80, visibleSize.height / 2 - 100);
	this->addChild(replay);

	auto label3 = Label::createWithTTF("退出", "fonts/STXINWEI.TTF", 40);
	label3->setColor(Color3B(0, 0, 0));
	auto exitBtn = MenuItemLabel::create(label3, CC_CALLBACK_1(GameStartScene::exitCallback, this));
	Menu* exit = Menu::create(exitBtn, NULL);
	exit->setPosition(visibleSize.width / 2 + 90, visibleSize.height / 2 - 100);
	this->addChild(exit);
}

// 继续或重玩按钮响应函数
void GameStartScene::replayCallback(Ref * pSender) {
	Director::getInstance()->replaceScene(GameStartScene::createScene());
}

// 退出
void GameStartScene::exitCallback(Ref * pSender) {
	Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}







/*
bool HitB
auto label1 = Label::createWithSystemFont("Breakout!", "Arial", 70);
label1->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 200));
this->addChild(label1, 1);

Sprite *background = Sprite::create("menu/backGround.png");
background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
this->addChild(background);

MenuItemFont::setFontName("Times New Roman");
MenuItemFont::setFontSize(60);
MenuItemFont *item1 = MenuItemFont::create("Start", CC_CALLBACK_1(HitBrick::menuItem1Callback, this));
MenuItemFont *item2 = MenuItemFont::create("Help", CC_CALLBACK_1(HitBrick::menuItem2Callback, this));

Menu *mn = Menu::create(item1, item2, NULL);
mn->alignItemsVertically();
this->addChild(mn);

MenuItemFont rtMenuItem = MenuItemSprite::create(item1, CC_CALLBACK1_1(HitBrick::menuItemStartCallback, this));
startMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(700, 170)));
*/