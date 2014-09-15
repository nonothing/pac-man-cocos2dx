#include "View\WorldScene.h"
#include "Model\ReadLevel.h"
#include "SimpleAudioEngine.h"
#include "MainMenuScene.h"

WorldScene* WorldScene::create(std::string levelName) {
	WorldScene* scene = new WorldScene();
	if(scene && scene->init(levelName)){
		return (WorldScene*)scene->autorelease();
	}
	CC_SAFE_DELETE(scene);
	return scene;
}

bool WorldScene::init(std::string levelName) {
    if ( !Layer::init() ) {
        return false;
    }

	worldController_ = new WorldController();

	isSound_ = CCUserDefault::sharedUserDefault()->getBoolForKey("SOUND", false);
	worldController_->setRecord(CCUserDefault::sharedUserDefault()->getIntegerForKey("RECORD",0));

	if(isSound_){
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/sirensound.wav");
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/sirensound.wav", true);
	}
	
	worldController_->setDirection(LEFT);
	isPause_ = false;

	readLevel_ = new ReadLevel();
	readLevel_->readFile(levelName);
	int size = readLevel_->getLevel()->bricks->size();

	world_ = new World(readLevel_->getLevel());
	worldController_->init(world_);
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(WorldScene::TouchBegan,this);
	touchListener->onTouchMoved = CC_CALLBACK_2(WorldScene::TouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(WorldScene::TouchEnded,this);
	getEventDispatcher()->addEventListenerWithFixedPriority(touchListener, 100);


	setTouchMode(kCCTouchesOneByOne);
 
	for(int i=0; i < size; i++){
		this->addChild(readLevel_->getLevel()->bricks->get(i)->getTexture(), 0);
	}
	this->addChild(worldController_->getLabelRecord(), 1);
	this->addChild(worldController_->getLabelScore(), 1);
	this->addChild(world_->getPlayer()->getTexture(),2);
	for(int i=0; i < world_->spirits->size(); i++){
		this->addChild(world_->spirits->get(i)->getTexture(),2);
	}

    this->setKeyboardEnabled(true);
    this->schedule(schedule_selector(WorldScene::updatePlayer),0.05f);
	this->schedule(schedule_selector(WorldScene::updateWorld),0.07f);
	this->schedule(schedule_selector(WorldScene::timerTask),1.0f);
	this->schedule(schedule_selector(WorldScene::speedTask),0.03f);

	 scene_ = Scene::create();
	 scene_->addChild(this);

    return true;
}

void WorldScene::timerTask(float dt){
	worldController_->timerTask(dt);
}

void WorldScene::speedTask(float dt){
	worldController_->speedTask(dt);
}

void WorldScene::updatePlayer(float dt){
	worldController_->updatePlayer(dt);
}	

void WorldScene::updateWorld(float dt){
	worldController_->updateWorld(dt);
}

bool WorldScene::TouchBegan(Touch *touch, Event *event){
	worldController_->setTouch(touch->getLocation().x, touch->getLocation().y);
    return true;
}

 void WorldScene::TouchMoved(Touch* touch, CCEvent* event){
	 worldController_->TouchMoved(touch->getLocation().x,touch->getLocation().y);
}
 void WorldScene::TouchEnded(Touch* touch, Event* event){
	 worldController_->TouchEnded(touch->getLocation().x,touch->getLocation().y);
}

void WorldScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event){
	if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID){
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
		Director::getInstance()->pushScene(MainMenuScene::create()->getScene());
	}
}