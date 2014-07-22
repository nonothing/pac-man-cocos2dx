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
extern string levelName;
bool WorldScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	worldController = new WorldController();

	isSound = CCUserDefault::sharedUserDefault()->getBoolForKey("SOUND", false);
	worldController->setRecord(CCUserDefault::sharedUserDefault()->getIntegerForKey("RECORD",0));

	if(isSound){
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/sirensound.wav");
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/sirensound.wav", true);
	}
	
	worldController->setDirection(LEFT);
	isPause = false;

	readLevel = new ReadLevel();
	readLevel->readFile(levelName);
	int size = readLevel->level->bricks->size();

	world = new World(readLevel->level);
	worldController->init(world);
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(WorldScene::TouchBegan,this);
	touchListener->onTouchMoved = CC_CALLBACK_2(WorldScene::TouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(WorldScene::TouchEnded,this);
	getEventDispatcher()->addEventListenerWithFixedPriority(touchListener, 100);


	setTouchMode(kCCTouchesOneByOne);
 
	for(int i=0; i < size; i++){
		this->addChild(readLevel->level->bricks->get(i)->getTexture(), 0);
	}
	this->addChild(worldController->getLabelRecord(), 1);
	this->addChild(worldController->getLabelScore(), 1);
	this->addChild(world->getPlayer()->getTexture(),2);
	for(int i=0; i < world->spirits->size(); i++){
		this->addChild(world->spirits->get(i)->getTexture(),2);
	}

    this->setKeyboardEnabled(true);
    this->schedule(schedule_selector(WorldScene::updatePlayer),0.05f);
	this->schedule(schedule_selector(WorldScene::updateWorld),0.07f);
	this->schedule(schedule_selector(WorldScene::timerTask),1.0f);
	this->schedule(schedule_selector(WorldScene::speedTask),0.03f);
    return true;
}

void WorldScene::timerTask(float dt){
	worldController->timerTask(dt);
}

void WorldScene::speedTask(float dt){
	worldController->speedTask(dt);
}

void WorldScene::updatePlayer(float dt){
	worldController->updatePlayer(dt);
}	

void WorldScene::updateWorld(float dt){
	worldController->updateWorld(dt);
}

bool WorldScene::TouchBegan(Touch *touch, Event *event){
	worldController->setTouch(touch->getLocation().x, touch->getLocation().y);
    return true;
}

 void WorldScene::TouchMoved(Touch* touch, CCEvent* event){
	 worldController->TouchMoved(touch->getLocation().x,touch->getLocation().y);
}
 void WorldScene::TouchEnded(Touch* touch, Event* event){
	 worldController->TouchEnded(touch->getLocation().x,touch->getLocation().y);
}

void WorldScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event){
	if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID){
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
		Director::getInstance()->pushScene(MainMenuScene::createScene());
	}
}