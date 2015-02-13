#include "MainMenuScene.h"
#include "View/WorldScene.h"
#include "View/LevelMenuScene.h"

MainMenuScene* MainMenuScene::create(SoundController* soundController) {
	MainMenuScene* scene = new MainMenuScene();
	if(scene && scene->init(soundController)){
		return (MainMenuScene*)scene->autorelease();
	}
	CC_SAFE_DELETE(scene);
	return scene;
}

bool MainMenuScene::init(SoundController* soundController) {

    if (!Layer::init()) {
        return false;
    }

	soundController_ = soundController;
	
	menuController_ = new MenuController();
	menuController_->init();
	isSound_ =  UserDefault::getInstance()->getBoolForKey("SOUND", false);
	if(isSound_){
		soundController_->preloadingAndPlayMusic(ESounds::ES_PACMAN_SOUNG, true);
	}

	touchListener_ = EventListenerTouchOneByOne::create();
	touchListener_->onTouchBegan = CC_CALLBACK_2(MainMenuScene::TouchBegan,this);
	touchListener_->onTouchMoved = CC_CALLBACK_2(MainMenuScene::TouchMoved, this);
	touchListener_->onTouchEnded = CC_CALLBACK_2(MainMenuScene::TouchEnded,this);
	getEventDispatcher()->addEventListenerWithFixedPriority(touchListener_, 100);

	keyboardListener_ = EventListenerKeyboard::create();
	keyboardListener_->onKeyReleased = CC_CALLBACK_2(MainMenuScene::onKeyReleased, this);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener_, this);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    auto labelName = LabelTTF::create("PAC-MAN", "fonts/emulogic.ttf", 56);
	labelName->setColor(Color3B::YELLOW);
	labelName->setPosition(Point(origin.x + visibleSize.width/2, origin.y + visibleSize.height - labelName->getContentSize().height));
    this->addChild(labelName, 1);
	this->addChild(menuController_->getButtonPlay(), 1);
	this->addChild(menuController_->getButtonLevel(), 1);
	this->addChild(menuController_->getButtonSound(), 1);
	this->addChild(menuController_->getButtonExit(), 1);
  
	scene_ = Scene::create();
	scene_->addChild(this);

    return true;
}

void MainMenuScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event){
	if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 && keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)) {
		Director::getInstance()->end();
	}
}

bool MainMenuScene::TouchBegan(Touch *touch, Event *event) {
	setMenu(menuController_->selectMenuItem(touch->getLocation().y, true));
    return true;
}

void MainMenuScene::TouchMoved(Touch* touch, Event* event) {
	setMenu(menuController_->selectMenuItem(touch->getLocation().y, true));
}

void MainMenuScene::TouchEnded(Touch* touch, Event* event) {
	setMenu(menuController_->selectMenuItem(touch->getLocation().y, false));	
}

 void MainMenuScene::setMenu(int item){
 switch (item) {
		case 1:
			getEventDispatcher()->removeEventListener(touchListener_);
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			Director::getInstance()->pushScene(WorldScene::create("lvl_01.txt", 1, soundController_)->getScene());
			break;
		case 2:
			getEventDispatcher()->removeEventListener(touchListener_);
			Director::getInstance()->pushScene(LevelMenuScene::create()->getScene());
			break;
        case 3: 
			if(isSound_){
				isSound_ = false;
				menuController_->getButtonSound()->setString("Sound off");
				menuController_->getButtonSound()->setPosition(Point(363, 200));
				CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
				CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
				UserDefault::getInstance()->setBoolForKey("SOUND", false);
				UserDefault::getInstance()->flush();
			} else {
				isSound_ = true;
				menuController_->getButtonSound()->setString("Sound on");
				menuController_->getButtonSound()->setPosition(Point(350, 200));
				soundController_->preloadingAndPlayMusic(ESounds::ES_PACMAN_SOUNG, true);
				UserDefault::getInstance()->setBoolForKey("SOUND",true);
				UserDefault::getInstance()->flush();
			}
			break;
		case 4:
			Director::getInstance()->end();
			break;
		default:
			break;
		}
 }