#include "LevelMenuScene.h"
#include "View\MainMenuScene.h"
#include "View\WorldScene.h"

using namespace cocos2d;
extern string levelName;
USING_NS_CC;

Scene* LevelMenuScene::createScene()
{
    auto scene = Scene::create();
    auto layer = LevelMenuScene::create();
    scene->addChild(layer);
    return scene;
}

bool LevelMenuScene::init()
{

    if ( !Layer::init() )
    {
        return false;
    }
	page = 0;

	buttonArrowLeft = new PButton(new PPoint(1, 1), "arrow_left", 65, 50);
	buttonArrowRight = new PButton(new PPoint(23, 1), "arrow_right", 65, 50);

	rectangle = new PRectangle(0, 0, 2, 2);
	levels = new List<LevelMenu*>();
	
	levels->append(createLevel(1, 5));
	levels->append(createLevel(7, 5));
	levels->append(createLevel(13, 5));
	levels->append(createLevel(19, 5));
	
	levels->append(createLevel(1, 11));
	levels->append(createLevel(7, 11));
	levels->append(createLevel(13, 11));
	levels->append(createLevel(19, 11));

	levels->append(createLevel(27, 5));
	levels->append(createLevel(33, 5));
	levels->append(createLevel(39, 5));
	levels->append(createLevel(45, 5));

	levels->append(createLevel(27, 11));
	levels->append(createLevel(33, 11));
	levels->append(createLevel(39, 11));
	levels->append(createLevel(45, 11));

	levels->append(createLevel(53, 5));
	levels->append(createLevel(59, 5));
	levels->append(createLevel(65, 5));
	levels->append(createLevel(71, 5));

	levels->append(createLevel(53, 11));
	levels->append(createLevel(59, 11));
	levels->append(createLevel(65, 11));
	levels->append(createLevel(71, 11));
	

	touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(LevelMenuScene::TouchBegan,this);
	getEventDispatcher()->addEventListenerWithFixedPriority(touchListener, 100);
	
	for (int i = 0; i < levels->size(); i++){
		this->addChild(levels->get(i)->getTexture(), 1);
		
		if(!levels->get(i)->getLock()){
			this->addChild(levels->get(i)->getLabel(), 2);
		}
		
	}

	this->addChild(buttonArrowLeft->getTexture(), 1);
	this->addChild(buttonArrowRight->getTexture(), 1);
	setTouchMode(kCCTouchesOneByOne);
	this->setKeyboardEnabled(true);
    return true;
}

LevelMenu* LevelMenuScene::createLevel(int x, int y){
	return new LevelMenu(new PPoint(x, y), "lock_gold_star", levels->size(), 0, 80, 80);
}

bool LevelMenuScene::TouchBegan(Touch *touch, Event *event)
{

	int x = touch->getLocation().x;
	int y = touch->getLocation().y;
	
	rectangle = new PRectangle(x, y, 20, 20);

	if (buttonArrowLeft->getRect()->intersects(rectangle) && page > 0){
		page--;
		for (int i = 0; i < levels->size(); i++){
			if(!levels->get(i)->getLock()){
				this->removeChild(levels->get(i)->getLabel());
			}
			levels->get(i)->setOffsetX(780);
			if(!levels->get(i)->getLock()){
				this->addChild(levels->get(i)->getLabel(), 2);
			}	
		}
	}

	if (buttonArrowRight->getRect()->intersects(rectangle) && page < 2){
		page++;

		for (int i = 0; i < levels->size(); i++){
			if(!levels->get(i)->getLock()){
				this->removeChild(levels->get(i)->getLabel());
			}
			levels->get(i)->setOffsetX(-780);
			if(!levels->get(i)->getLock()){
				this->addChild(levels->get(i)->getLabel(), 2);
			}	
		}
		
	}

	for (int i = 0; i < levels->size(); i++){
		if (levels->get(i)->getRect()->intersects(rectangle)){
			levelName = parseLevel(i + 1);
			getEventDispatcher()->removeEventListener(touchListener);
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			Director::getInstance()->pushScene(WorldScene::createScene());
		}
	}

    return true;
}

string LevelMenuScene::parseLevel(int number){
	string result = "lvl_"; 
	ostringstream convert;
	convert << number;
	if (number < 10){
		result += "0" + convert.str();
	} else {
		result += convert.str();
	}
	return result + ".txt";
}

void LevelMenuScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event){
	if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID){
		getEventDispatcher()->removeEventListener(touchListener);
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
		Director::getInstance()->pushScene(MainMenuScene::createScene());
	}
}