#include "LevelMenuScene.h"
#include "View\MainMenuScene.h"
#include "View\WorldScene.h"
#define SCALE 1.5f

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

	levels_->append(createLevel(2, 11));
	levels_->append(createLevel(8, 11));
	levels_->append(createLevel(14, 11));
	levels_->append(createLevel(20, 11));

	levels_->append(createLevel(2, 5));
	levels_->append(createLevel(8, 5));
	levels_->append(createLevel(14, 5));
	levels_->append(createLevel(20, 5));

	levels_->append(createLevel(28, 11));
	levels_->append(createLevel(34, 11));
	levels_->append(createLevel(40, 11));
	levels_->append(createLevel(46, 11));

	levels_->append(createLevel(28, 5));
	levels_->append(createLevel(34, 5));
	levels_->append(createLevel(40, 5));
	levels_->append(createLevel(46, 5));

	levels_->append(createLevel(54, 11));
	levels_->append(createLevel(60, 11));
	levels_->append(createLevel(66, 11));
	levels_->append(createLevel(72, 11));

	levels_->append(createLevel(54, 5));
	levels_->append(createLevel(60, 5));
	levels_->append(createLevel(66, 5));
	levels_->append(createLevel(72, 5));


	touchListener_ = EventListenerTouchOneByOne::create();
	touchListener_->onTouchBegan = CC_CALLBACK_2(LevelMenuScene::TouchBegan,this);
	getEventDispatcher()->addEventListenerWithFixedPriority(touchListener_, 100);

	for (int i = 0; i < levels_->size(); i++){
		this->addChild(levels_->get(i)->getTexture(), 1);
		levels_->get(i)->getTexture()->setScale(SCALE);
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
	return new LevelMenu(new PPoint(x, y), "lock_gold_star", levels_->size(), 0, 80 * SCALE, 80 * SCALE);
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
		if (!levels_->get(i)->getLock() && levels_->get(i)->getRect()->intersects(rectangle_)){
			getEventDispatcher()->removeEventListener(touchListener_);
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			Director::getInstance()->pushScene(WorldScene::create(parseLevel(i + 1), i + 1, soundController_)->getScene());
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

	if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 && keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)) {
		getEventDispatcher()->removeEventListener(touchListener_);
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
		Director::getInstance()->pushScene(MainMenuScene::create(soundController_)->getScene());
	}

}