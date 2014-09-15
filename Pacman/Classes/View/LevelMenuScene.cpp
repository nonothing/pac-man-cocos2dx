#include "LevelMenuScene.h"
#include "View\MainMenuScene.h"
#include "View\WorldScene.h"

LevelMenuScene* LevelMenuScene::create() {
	LevelMenuScene* scene = new LevelMenuScene();
	if(scene && scene->init()){
		return (LevelMenuScene*)scene->autorelease();
	}
	CC_SAFE_DELETE(scene);
	return scene;
}

bool LevelMenuScene::init() {

    if (!Layer::init()) {
        return false;
    }

	page_ = 0;

	buttonArrowLeft_ = new PButton(new PPoint(1, 1), "arrow_left", 65, 50);
	buttonArrowRight_ = new PButton(new PPoint(23, 1), "arrow_right", 65, 50);

	rectangle_ = new PRectangle(0, 0, 2, 2);
	levels_ = new List<LevelMenu*>();
	
	levels_->append(createLevel(1, 5));
	levels_->append(createLevel(7, 5));
	levels_->append(createLevel(13, 5));
	levels_->append(createLevel(19, 5));
	
	levels_->append(createLevel(1, 11));
	levels_->append(createLevel(7, 11));
	levels_->append(createLevel(13, 11));
	levels_->append(createLevel(19, 11));

	levels_->append(createLevel(27, 5));
	levels_->append(createLevel(33, 5));
	levels_->append(createLevel(39, 5));
	levels_->append(createLevel(45, 5));

	levels_->append(createLevel(27, 11));
	levels_->append(createLevel(33, 11));
	levels_->append(createLevel(39, 11));
	levels_->append(createLevel(45, 11));

	levels_->append(createLevel(53, 5));
	levels_->append(createLevel(59, 5));
	levels_->append(createLevel(65, 5));
	levels_->append(createLevel(71, 5));

	levels_->append(createLevel(53, 11));
	levels_->append(createLevel(59, 11));
	levels_->append(createLevel(65, 11));
	levels_->append(createLevel(71, 11));
	

	touchListener_ = EventListenerTouchOneByOne::create();
	touchListener_->onTouchBegan = CC_CALLBACK_2(LevelMenuScene::TouchBegan,this);
	getEventDispatcher()->addEventListenerWithFixedPriority(touchListener_, 100);
	
	for (int i = 0; i < levels_->size(); i++){
		this->addChild(levels_->get(i)->getTexture(), 1);
		
		if(!levels_->get(i)->getLock()){
			this->addChild(levels_->get(i)->getLabel(), 2);
		}
		
	}

	this->addChild(buttonArrowLeft_->getTexture(), 1);
	this->addChild(buttonArrowRight_->getTexture(), 1);
	setTouchMode(kCCTouchesOneByOne);
	this->setKeyboardEnabled(true);

	scene_ = Scene::create();
	scene_->addChild(this);

    return true;
}

LevelMenu* LevelMenuScene::createLevel(int x, int y){
	return new LevelMenu(new PPoint(x, y), "lock_gold_star", levels_->size(), 0, 80, 80);
}

bool LevelMenuScene::TouchBegan(Touch *touch, Event *event) {

	int x = touch->getLocation().x;
	int y = touch->getLocation().y;
	
	rectangle_ = new PRectangle(x, y, 20, 20);

	if (buttonArrowLeft_->getRect()->intersects(rectangle_) && page_ > 0){
		page_--;
		for (int i = 0; i < levels_->size(); i++){
			if(!levels_->get(i)->getLock()){
				this->removeChild(levels_->get(i)->getLabel());
			}
			levels_->get(i)->setOffsetX(780);
			if(!levels_->get(i)->getLock()){
				this->addChild(levels_->get(i)->getLabel(), 2);
			}	
		}
	}

	if (buttonArrowRight_->getRect()->intersects(rectangle_) && page_ < 2){
		page_++;

		for (int i = 0; i < levels_->size(); i++){
			if(!levels_->get(i)->getLock()){
				this->removeChild(levels_->get(i)->getLabel());
			}
			levels_->get(i)->setOffsetX(-780);
			if(!levels_->get(i)->getLock()){
				this->addChild(levels_->get(i)->getLabel(), 2);
			}	
		}
		
	}

	for (int i = 0; i < levels_->size(); i++){
		if (levels_->get(i)->getRect()->intersects(rectangle_)){
			getEventDispatcher()->removeEventListener(touchListener_);
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			Director::getInstance()->pushScene(WorldScene::create(parseLevel(i + 1))->getScene());
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
		getEventDispatcher()->removeEventListener(touchListener_);
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
		Director::getInstance()->pushScene(MainMenuScene::create()->getScene());
	}
}