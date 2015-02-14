#include "LevelMenuScene.h"
#include "View/MainMenuScene.h"
#include "View/WorldScene.h"

#define SCALE 1.5f
#define LAST_PAGE	3
#define MAX_LEVEL   30

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

	buttonArrowLeft_ = new PButton(new PPoint(1, 1), EArrow_left, 65, 50);
	buttonArrowRight_ = new PButton(new PPoint(23, 1), EArrow_right, 65, 50);

	rectangle_ = new PRectangle(0, 0, 2, 2);

	int offset = 0;
	for (int i = 0; i <= LAST_PAGE; i++) {
		offset += 2;
		for (int j=0; j < 4; j++) {
			int levelUp = (i * 8) + j;
			int levelDown = (i * 8) + j + 4;
			
			if(levelUp < MAX_LEVEL){
				levels_.push_back(createLevel(offset, 11, levelUp));
			}
			
			if(levelDown < MAX_LEVEL) {
				levels_.push_back(createLevel(offset, 5, levelDown));
			}
			
			offset +=6;
		}
	}

	touchListener_ = EventListenerTouchOneByOne::create();
	touchListener_->onTouchBegan = CC_CALLBACK_2(LevelMenuScene::TouchBegan,this);
	getEventDispatcher()->addEventListenerWithFixedPriority(touchListener_, 100);

	keyboardListener_ = EventListenerKeyboard::create();
	keyboardListener_->onKeyReleased = CC_CALLBACK_2(LevelMenuScene::onKeyReleased, this);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener_, this);

	for (auto level: levels_) {
		this->addChild(level->getTexture(), 1);
		level->getTexture()->setScale(SCALE);
		if(!level->getLock()){
			this->addChild(level->getLabel(), 2);
		}

	}
	buttonArrowLeft_->getTexture()->setVisible(false);
	this->addChild(buttonArrowRight_->getTexture(), 1);
	this->addChild(buttonArrowLeft_->getTexture(), 1);

	scene_ = Scene::create();
	scene_->addChild(this);

	return true;
}

LevelMenu* LevelMenuScene::createLevel(int x, int y, int level){
	return new LevelMenu(new PPoint(x, y), ELockGoldStar, level, 0, 80 * SCALE, 80 * SCALE);
}

bool LevelMenuScene::TouchBegan(Touch *touch, Event *event) {

	int x = touch->getLocation().x;
	int y = touch->getLocation().y;

	rectangle_ = new PRectangle(x, y, 20, 20);

	nextPage(buttonArrowLeft_, 0);
	nextPage(buttonArrowRight_, LAST_PAGE);
	
	buttonArrowLeft_->show(page_, 0);
	buttonArrowRight_->show(page_, LAST_PAGE);

	for (int i = 0; i < levels_.size(); i++){
		if (!levels_.at(i)->getLock() && levels_.at(i)->getRect()->intersects(rectangle_)){
			getEventDispatcher()->removeEventListener(touchListener_);
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			Director::getInstance()->pushScene(WorldScene::create(levels_.at(i)->getName(), i, soundController_)->getScene());
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

void LevelMenuScene::nextPage(PButton* button, int limitation) {
	int side = -1;
	int offset = 780;
	if(limitation != 0) {
		offset = -offset;
		side = 1;
	} 
	if (button->getTexture()->isVisible() && button->getRect()->intersects(rectangle_)){
		page_ += side;
		for (auto level: levels_){
			if(!level->getLock()){
				this->removeChild(level->getLabel());
			}
			level->setOffsetX(offset);
			if(!level->getLock()){
				this->addChild(level->getLabel(), 2);
			}	
		}
	}
}
