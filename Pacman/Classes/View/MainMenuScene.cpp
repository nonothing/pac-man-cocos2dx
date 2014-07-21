#include "MainMenuScene.h"
#include "View\WorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace std;
USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    auto scene = Scene::create();
	auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    auto layer = MainMenuScene::create();
    scene->addChild(layer);

    return scene;
}

bool MainMenuScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	isSound =  CCUserDefault::sharedUserDefault()->getBoolForKey("SOUND", false);
	if(isSound){
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/pacman_song2.wav");
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/pacman_song2.wav", true);
	}
	touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(MainMenuScene::TouchBegan,this);
	touchListener->onTouchMoved = CC_CALLBACK_2(MainMenuScene::TouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(MainMenuScene::TouchEnded,this);
	getEventDispatcher()->addEventListenerWithFixedPriority(touchListener, 100);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
	setTouchMode(kCCTouchesOneByOne);
    
    auto labelName = LabelTTF::create("PAC-MAN", "fonts/emulogic.ttf", 56);
	labelName->setColor(Color3B::YELLOW);
	labelName->setPosition(Point(origin.x + visibleSize.width/2, origin.y + visibleSize.height - labelName->getContentSize().height));
    this->addChild(labelName, 1);

	buttonPlay = LabelTTF::create("Play", "fonts/emulogic.ttf", 26);
	buttonPlay->setColor(Color3B::YELLOW);
	buttonPlay->setPosition(Point(300, 300));
    this->addChild(buttonPlay, 1);

	buttonLevel = LabelTTF::create("Select level", "fonts/emulogic.ttf", 26);
	buttonLevel->setColor(Color3B::YELLOW);
	buttonLevel->setPosition(Point(402, 250));
    this->addChild(buttonLevel, 1);

	buttonSound = LabelTTF::create("sound on", "fonts/emulogic.ttf", 26);
	buttonSound->setColor(Color3B::YELLOW);
	buttonSound->setPosition(Point(350, 200));
	if(!isSound){
		buttonSound->setString("Sound off");
		buttonSound->setPosition(Point(363, 200));
	} 
    this->addChild(buttonSound, 1);

	buttonExit = LabelTTF::create("exit", "fonts/emulogic.ttf", 26);
	buttonExit->setColor(Color3B::YELLOW);
	buttonExit->setPosition(Point(300, 150));
    this->addChild(buttonExit, 1);
  
	this->setKeyboardEnabled(true);
    return true;
}

void MainMenuScene::setBooleanForKey(const char* key, bool obj){

}

void MainMenuScene::selectMenuItem(int y, bool isTouch){
	int item = 0;
	if(y >= 150 && y < 200){
		buttonExit->setColor(Color3B::RED);
		item = 4;
	} else {
		buttonExit->setColor(Color3B::YELLOW);
	}
	if(y >= 200 && y < 250){
		item = 3;
		buttonSound->setColor(Color3B::RED);
	} else {
		buttonSound->setColor(Color3B::YELLOW);
	}
	if(y >= 250 && y < 300){
		item = 2;
		buttonLevel->setColor(Color3B::RED);
	} else {
		buttonLevel->setColor(Color3B::YELLOW);
	}
	if(y >= 300 && y < 350){
		item = 1;
		buttonPlay->setColor(Color3B::RED);
	} else {
		buttonPlay->setColor(Color3B::YELLOW);
	}

	if(!isTouch){
		switch (item)
		{
		case 1:
			getEventDispatcher()->removeEventListener(touchListener);
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			Director::getInstance()->pushScene(WorldScene::createScene());
			break;
		case 2: break;
        case 3: 
			if(isSound){
				isSound = false;
				buttonSound->setString("Sound off");
				buttonSound->setPosition(Point(363, 200));
				CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
				CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
				CCUserDefault::sharedUserDefault()->setBoolForKey("SOUND",false);
				CCUserDefault::sharedUserDefault()->flush();
			} else {
				isSound = true;
				buttonSound->setString("Sound on");
				buttonSound->setPosition(Point(350, 200));
				CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/pacman_song2.wav");
				CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/pacman_song2.wav", true);
				CCUserDefault::sharedUserDefault()->setBoolForKey("SOUND",true);
				CCUserDefault::sharedUserDefault()->flush();
			}
			break;
		case 4:
			Director::getInstance()->end();
			break;
		default:
			break;
		}
	}
}

void MainMenuScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event){
	if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID){
		Director::getInstance()->end();
	}
}

bool MainMenuScene::TouchBegan(Touch *touch, Event *event)
{
	selectMenuItem(touch->getLocation().y, true);
    return true;
}

void MainMenuScene::TouchMoved(Touch* touch, CCEvent* event){
	selectMenuItem(touch->getLocation().y, true);
}
 void MainMenuScene::TouchEnded(Touch* touch, Event* event){
	selectMenuItem(touch->getLocation().y, false);
}