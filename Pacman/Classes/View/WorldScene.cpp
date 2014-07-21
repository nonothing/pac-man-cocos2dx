#include "View\WorldScene.h"
#include "Model\ReadLevel.h"
#include "SimpleAudioEngine.h"
#include "MainMenuScene.h"

using namespace cocos2d;
USING_NS_CC;

Scene* WorldScene::createScene()
{
    auto scene = Scene::create();
    auto layer = WorldScene::create();
    scene->addChild(layer);
    return scene;
}

void WorldScene::update(float dt){
	ostringstream convert;   
    convert << world->getScore();    

	labelScore->setString("You: " + convert.str() );
	world->tryToPlayerGo(direction);	

	for(int i=0; i < 4; i++){	
			world->spirits->get(i)->go(world);
		}
}

bool WorldScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	isSound = CCUserDefault::sharedUserDefault()->getBoolForKey("SOUND", false);
	if(isSound){
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/sirensound.wav");
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/sirensound.wav", true);
	}
	

	direction = LEFT;

	readLevel = new ReadLevel();
	readLevel->readFile("level_1.txt", map);
	int size = readLevel->level->bricks->size();

	world = new World(readLevel->level);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(WorldScene::TouchBegan,this);
	touchListener->onTouchMoved = CC_CALLBACK_2(WorldScene::TouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(WorldScene::TouchEnded,this);
	getEventDispatcher()->addEventListenerWithFixedPriority(touchListener, 100);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
	setTouchMode(kCCTouchesOneByOne);
 

    auto labelRecord = LabelTTF::create("Record: ", FONT_EMULOGIC, 14);
    labelRecord->setPosition(Point(100,436));
	labelRecord->setColor(Color3B::YELLOW);

	labelScore = LabelTTF::create("You: ", FONT_EMULOGIC , 14);
    labelScore->setPosition(Point(610,436));
	labelScore->setColor(Color3B::YELLOW);
	

	for(int i=0; i < size; i++){
		this->addChild(readLevel->level->bricks->get(i)->getTexture(), 0);
	}
    this->addChild(labelRecord, 1);
	this->addChild(labelScore, 1);
	this->addChild(world->getPlayer()->getTexture(),2);
	for(int i=0; i < world->spirits->size(); i++){
		this->addChild(world->spirits->get(i)->getTexture(),2);
	}

    this->setKeyboardEnabled(true);
    this->schedule(schedule_selector(WorldScene::update),0.05f);
    return true;
}

bool WorldScene::TouchBegan(Touch *touch, Event *event)
{
	touchX = touch->getLocation().x;
	touchY = touch->getLocation().y;
    return true;
}

 void WorldScene::TouchMoved(Touch* touch, CCEvent* event){
	 int x = touch->getLocation().x;
	 int y = touch->getLocation().y;
	 if (touchX > x && abs(x - touchX) > 20 && abs(y - touchY) < 60)
			direction = LEFT;
		if (touchX < x && abs(x - touchX) > 20 && abs(y - touchY) < 60)
			direction = RIGHT;
		if (touchY > y && abs(y - touchY) > 20 && abs(x - touchX) < 60)
			direction = DOWN;
		if (touchY < y && abs(y - touchY) > 20 && abs(x - touchX) < 60)
			direction = UP;
}
 void WorldScene::TouchEnded(Touch* touch, Event* event){
	 int x = touch->getLocation().x;
	 int y = touch->getLocation().y;
	 if (touchX > x && abs(y - touchY) < 60)
			direction = LEFT;
		if (touchX < x && abs(y - touchY) < 60)
			direction = RIGHT;
		if (touchY > y && abs(x - touchX) < 60)
			direction = DOWN;
		if (touchY < y && abs(x - touchX) < 60)
			direction = UP;
}

void WorldScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event){
	if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID){
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
		Director::getInstance()->pushScene(MainMenuScene::createScene());
	}
}