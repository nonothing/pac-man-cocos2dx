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
	_size = Director::getInstance()->getWinSize();
	_worldLayer = Layer::create(); this->addChild(_worldLayer);
	_positionX = 0;
	_positionY = 0;


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
		_worldLayer->addChild(readLevel_->getLevel()->bricks->get(i)->getTexture(), 0);
	}
	this->addChild(worldController_->getLabelRecord(), 1);
	this->addChild(worldController_->getLabelScore(), 1);
	_worldLayer->addChild(world_->getPlayer()->getTexture(),2);
	for(int i=0; i < world_->spirits->size(); i++){
		_worldLayer->addChild(world_->spirits->get(i)->getTexture(),2);
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
	updatePosition();
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

void WorldScene::updatePosition()
{
	float bufferWidth = _size.width*0.3;
	float bufferHeight = _size.height*0.3;
	float playerX = world_->getPlayer()->getTexture()->getPositionX();
	float playerY = world_->getPlayer()->getTexture()->getPositionY();
	float levelWidth = readLevel_->getLevel()->_width*30;
	float levelHeight = readLevel_->getLevel()->_height*30;

	if(playerX > (_size.width - bufferWidth) +  _positionX)
	{
		_positionX+=3;
	} else
	if(playerX < bufferWidth +  _positionX)
	{
		_positionX-=3;
	}

	if(playerY > (_size.height - bufferHeight) +  _positionY)
	{
		_positionY+=3;
	} else
	if(playerY < bufferHeight +  _positionY)
	{
		_positionY-=3;
	}

	//границы
	if(_positionX < 0) _positionX = 0;
	if(_positionX > levelWidth-_size.width) _positionX = levelWidth-_size.width;

	if(_positionY < 0) _positionY = 0;
	if(_positionY > levelHeight-_size.height) _positionY = levelHeight-_size.height;

	_worldLayer->setPosition(-_positionX, -_positionY);
}