#include "View/WorldScene.h"
#include "Model/ReadLevel.h"
#include "SimpleAudioEngine.h"
#include "MainMenuScene.h"

WorldScene* WorldScene::create(std::string levelName, int currentLevel, SoundController* soundController) {
	WorldScene* scene = new WorldScene();
	if(scene && scene->init(levelName, currentLevel, soundController)){
		return (WorldScene*)scene->autorelease();
	}
	CC_SAFE_DELETE(scene);
	return scene;
}

bool WorldScene::init(std::string levelName, int currentLevel, SoundController* soundController) {
    if ( !Layer::init() ) {
        return false;
    }
	soundController_ = soundController;
	worldController_ = new WorldController();
	size_ = Director::getInstance()->getWinSize();
	worldLayer_ = Layer::create();
	this->addChild(worldLayer_);
	positionX_ = 0;
	positionY_ = 0;


	isSound_ = UserDefault::getInstance()->getBoolForKey("SOUND", false);
	worldController_->setRecord(UserDefault::getInstance()->getIntegerForKey(levelName.c_str(), 0));
	
	if(isSound_){
		soundController_->preloadingAndPlayMusic(ESounds::ES_SIREN_SOUND, true);
	}
	
	worldController_->setDirection(LEFT);
	isPause_ = false;

	readLevel_ = new ReadLevel();
	readLevel_->readFile(levelName);
	int size = readLevel_->getLevel()->getBricks().size();

	world_ = new World(readLevel_->getLevel(), soundController_);
	world_->setCurrentLevel(currentLevel);
	worldController_->init(world_, soundController_);

	touchListener_ = EventListenerTouchOneByOne::create();
	touchListener_->onTouchBegan = CC_CALLBACK_2(WorldScene::TouchBegan,this);
	touchListener_->onTouchMoved = CC_CALLBACK_2(WorldScene::TouchMoved, this);
	touchListener_->onTouchEnded = CC_CALLBACK_2(WorldScene::TouchEnded,this);
	getEventDispatcher()->addEventListenerWithFixedPriority(touchListener_, 100);

	keyboardListener_ = EventListenerKeyboard::create();
	keyboardListener_->onKeyReleased = CC_CALLBACK_2(WorldScene::onKeyReleased, this);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener_, this);
 
	for(auto brick: readLevel_->getLevel()->getBricks()){
		worldLayer_->addChild(brick->getTexture(), 0);
	}

	this->addChild(worldController_->getLabelRecord(), 1);
	this->addChild(worldController_->getLabelScore(), 1);
	worldLayer_->addChild(world_->getPlayer()->getTexture(), 2);

	for(auto spirit: world_->getSpirits()){
		worldLayer_->addChild(spirit->getTexture(), 2);
	}

    this->schedule(schedule_selector(WorldScene::updatePlayer),0.06f);
	this->schedule(schedule_selector(WorldScene::updateWorld),0.07f);
	this->schedule(schedule_selector(WorldScene::timerTask),1.0f);
	this->schedule(schedule_selector(WorldScene::speedTask),0.03f);
	this->schedule(schedule_selector(WorldScene::generateFruit), 15.0f);

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
	updatePosition();
}	

void WorldScene::updateWorld(float dt){
	worldController_->updateWorld(dt);
}

void WorldScene::generateFruit(float dt) {
	worldController_->generateFruit(dt);
}

bool WorldScene::TouchBegan(Touch *touch, Event *event){
	worldController_->setTouch(touch->getLocation().x, touch->getLocation().y);
    return true;
}

 void WorldScene::TouchMoved(Touch* touch, Event* event){
	 worldController_->TouchMoved(touch->getLocation().x,touch->getLocation().y);
}
 void WorldScene::TouchEnded(Touch* touch, Event* event){
	 worldController_->TouchEnded(touch->getLocation().x,touch->getLocation().y);
}

void WorldScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event) {
	if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 && keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)) {
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
		Director::getInstance()->pushScene(MainMenuScene::create(soundController_)->getScene());
	}
}

void WorldScene::updatePosition() {

	float bufferWidth = size_.width * 0.3;
	float bufferHeight = size_.height * 0.3;
	float playerX = world_->getPlayer()->getTexture()->getPositionX();
	float playerY = world_->getPlayer()->getTexture()->getPositionY();
	float levelWidth = readLevel_->getLevel()->getWidth() * 30;
	float levelHeight = readLevel_->getLevel()->getHeight() * 30;

	if(playerX > (size_.width - bufferWidth) +  positionX_)	{
		positionX_ += 5;
	} else if(playerX < bufferWidth +  positionX_)	{
		positionX_ -= 5;
	}

	if(playerY > (size_.height - bufferHeight) +  positionY_) {
		positionY_ += 5;
	} else if(playerY < bufferHeight +  positionY_)	{
		positionY_ -= 5;
	}

	if(positionX_ < 0) positionX_ = 0;
	if(positionX_ > levelWidth-size_.width) positionX_ = levelWidth-size_.width;

	if(positionY_ < 0) positionY_ = 0;
	if(positionY_ > levelHeight-size_.height) positionY_ = levelHeight-size_.height;

	worldLayer_->setPosition(-positionX_, -positionY_);
}


