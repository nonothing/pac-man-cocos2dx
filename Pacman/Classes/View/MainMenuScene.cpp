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
	menuController = new MenuController();
	menuController->init();
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
	this->addChild(menuController->getButtonPlay(), 1);
	this->addChild(menuController->getButtonLevel(), 1);
	this->addChild(menuController->getButtonSound(), 1);
	this->addChild(menuController->getButtonExit(), 1);
  
	this->setKeyboardEnabled(true);
    return true;
}

void MainMenuScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event){
	if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID){
		Director::getInstance()->end();
	}
}

bool MainMenuScene::TouchBegan(Touch *touch, Event *event)
{
	setMenu(menuController->selectMenuItem(touch->getLocation().y, true));
    return true;
}

void MainMenuScene::TouchMoved(Touch* touch, CCEvent* event){
	setMenu(menuController->selectMenuItem(touch->getLocation().y, true));
}
 void MainMenuScene::TouchEnded(Touch* touch, Event* event){
	 setMenu(menuController->selectMenuItem(touch->getLocation().y, false));
}

 void MainMenuScene::setMenu(int item){
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
				menuController->getButtonSound()->setString("Sound off");
				menuController->getButtonSound()->setPosition(Point(363, 200));
				CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
				CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
				CCUserDefault::sharedUserDefault()->setBoolForKey("SOUND",false);
				CCUserDefault::sharedUserDefault()->flush();
			} else {
				isSound = true;
				menuController->getButtonSound()->setString("Sound on");
				menuController->getButtonSound()->setPosition(Point(350, 200));
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