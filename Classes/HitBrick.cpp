#pragma execution_character_set("utf-8")
#include "HitBrick.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#define database UserDefault::getInstance()

USING_NS_CC;
using namespace CocosDenshion;

Scene* HitBrick::createScene()
{
	auto scene = Scene::create();	//����һ������
	auto layer = HitBrick::create();//����һ���˵���
	scene->addChild(layer);		//�Ѳ˵������ոմ����ĳ����У�
	return scene;			//�����������
}

// on "init" you need to initialize your instance
bool HitBrick::init() {
	//////////////////////////////
	// 1. super init first
	if (!Layer::init()) {
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite *background = Sprite::create("menu/backGround.png");
	background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(background);//���ÿ�ʼҳ��
	auto label1 = Label::createWithSystemFont("Breakout", "Arial", 70);
	label1->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 200));
	this->addChild(label1, 1);

	MenuItemFont::setFontName("Times New Roman");
	MenuItemFont::setFontSize(60);
	MenuItemFont *item1 = MenuItemFont::create("Start", CC_CALLBACK_1(HitBrick::EnterGameScene, this));
	MenuItemFont *item2 = MenuItemFont::create("Help", CC_CALLBACK_1(HitBrick::EnterGameScene, this));

	auto menu = Menu::create(item1, item2, NULL);
	//�Ѳ˵���ӵ�GameStart����
	this->addChild(menu);
   /*
	auto edgeSp = Sprite::create();  //����һ������	auto boundBody = PhysicsBody::createEdgeBox(visibleSize, PhysicsMaterial(0.0f, 1.0f, 0.0f), 3);  //edgebox�ǲ��ܸ�����ײӰ���һ�ָ��壬����������������������ı߽�	edgeSp->setPosition(visibleSize.width / 2, visibleSize.height / 2);  //λ����������Ļ����	edgeSp->setPhysicsBody(boundBody);	addChild(edgeSp);

	preloadMusic(); // Ԥ������Ч
	addSprite();    // ��ӱ����͸��־���
	addListener();  // ��Ӽ����� 
	addPlayer();    // ��������
	BrickGeneraetd();  // ����ש��


	schedule(schedule_selector(HitBrick::update), 0.01f, kRepeatForever, 0.1f);

	onBall = true;

	spHolded = -1;
	spFactor = 0;*/
	return true;
}
void HitBrick::EnterGameScene(Ref * pSender)
{
	MenuItem* item = (MenuItem*)pSender;
	log("Touch GameStart %p", item);
	auto sc = GameStartScene::createScene();
	Director::getInstance()->replaceScene(sc);
}










/*
// �ؽ����ӣ��̶��������
// Todo
void HitBrick::setJoint() {
	Vec2 fixPoint = Vec2(ball->getAnchorPoint().x, ball->getAnchorPoint().y - 30);
	joint1 = PhysicsJointPin::construct(ball->getPhysicsBody(), player->getPhysicsBody(), fixPoint, player->getAnchorPoint());
	m_world->addJoint(joint1);
}



// Ԥ������Ч
void HitBrick::preloadMusic() {
	auto sae = SimpleAudioEngine::getInstance();
	sae->preloadEffect("gameover.mp3");
	sae->preloadBackgroundMusic("bgm.mp3");
	sae->playBackgroundMusic("bgm.mp3", true);
}

// ��ӱ����͸��־���
void HitBrick::addSprite() {

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

// ��Ӽ�����
void HitBrick::addListener() {
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(HitBrick::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(HitBrick::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(HitBrick::onConcactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

// ������ɫ
void HitBrick::addPlayer() {



	player = Sprite::create("bar.png");
	int xpos = visibleSize.width / 2;

	player->setScale(0.1f, 0.1f);
	player->setPosition(Vec2(xpos, ship->getContentSize().height - player->getContentSize().height*0.1f));
	// ���ð�ĸ�������
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
	// ������ĸ�������
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

// ʵ�ּ򵥵�����Ч��
// Todo

void HitBrick::update(float dt) {
	if (player->getPosition().x < 100) {
		player->setPosition(100,player->getPosition().y);
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
void HitBrick::BrickGeneraetd() {

	for (int i = 0; i < 3; i++) {
		int cw = 30;
		while (cw <= visibleSize.width) {
			auto box = Sprite::create("box.png");
			// Ϊש�����ø�������
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


// ����
void HitBrick::onKeyPressed(EventKeyboard::KeyCode code, Event* event) {

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
		// �����ƶ�
		// Todo
		if (player->getPosition().x < visibleSize.width - 100) {
			player->getPhysicsBody()->setVelocity(Vec2(500, 0));
		}
		else {
			//player->setPosition(visibleSize.width-100,player->getPosition().y);
			player->getPhysicsBody()->setVelocity(Vec2(0, 0));
		}
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_SPACE: // ��ʼ����
		if (spHolded == -1)
			spHolded = 1;
		break;
	default:
		break;
	}
}

// �ͷŰ���
void HitBrick::onKeyReleased(EventKeyboard::KeyCode code, Event* event) {
	switch (code) {
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		// ֹͣ�˶�
		// Todo
		player->getPhysicsBody()->setVelocity(Vec2(0, 0));
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:   // ����������С����
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

// ��ײ���
// Todo
bool HitBrick::onConcactBegin(PhysicsContact & contact) {
	auto c1 = contact.getShapeA()->getBody(), c2 = contact.getShapeB()->getBody();
	auto s1 = (Sprite*)c1->getNode(), s2 = (Sprite*)c2->getNode();
	auto rain = ParticleRain::create();
	if (c1->getTag() == Tag::BOX && c2->getTag() == Tag::BALL) {
		//����
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


void HitBrick::GameOver() {

	_eventDispatcher->removeAllEventListeners();
	ball->getPhysicsBody()->setVelocity(Vec2(0, 0));
	player->getPhysicsBody()->setVelocity(Vec2(0, 0));
	SimpleAudioEngine::getInstance()->stopBackgroundMusic("bgm.mp3");
	SimpleAudioEngine::getInstance()->playEffect("gameover.mp3", false);

	auto label1 = Label::createWithTTF("Game Over~", "fonts/STXINWEI.TTF", 60);
	label1->setColor(Color3B(0, 0, 0));
	label1->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(label1);

	auto label2 = Label::createWithTTF("����", "fonts/STXINWEI.TTF", 40);
	label2->setColor(Color3B(0, 0, 0));
	auto replayBtn = MenuItemLabel::create(label2, CC_CALLBACK_1(HitBrick::replayCallback, this));
	Menu* replay = Menu::create(replayBtn, NULL);
	replay->setPosition(visibleSize.width / 2 - 80, visibleSize.height / 2 - 100);
	this->addChild(replay);

	auto label3 = Label::createWithTTF("�˳�", "fonts/STXINWEI.TTF", 40);
	label3->setColor(Color3B(0, 0, 0));
	auto exitBtn = MenuItemLabel::create(label3, CC_CALLBACK_1(HitBrick::exitCallback, this));
	Menu* exit = Menu::create(exitBtn, NULL);
	exit->setPosition(visibleSize.width / 2 + 90, visibleSize.height / 2 - 100);
	this->addChild(exit);
}

// ���������水ť��Ӧ����
void HitBrick::replayCallback(Ref * pSender) {
	Director::getInstance()->replaceScene(HitBrick::createScene());
}

// �˳�
void HitBrick::exitCallback(Ref * pSender) {
	Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
*/
