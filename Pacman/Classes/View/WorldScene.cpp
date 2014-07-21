#include "View\WorldScene.h"
#include "Model\ReadLevel.h"
#include "SimpleAudioEngine.h"
#include "MainMenuScene.h"

using namespace cocos2d;
USING_NS_CC;

Scene* WorldScene::createScene()
{
    auto scene = Scene::create();
    auto layer = WorldScene::create();
    scene->addChild(layer);
    return scene;
}

void WorldScene::updatePlayer(float dt){
	ostringstream convertScore;   
    convertScore << world->getScore();    
	labelScore->setString("You: " + convertScore.str() );

	if(world->getScore() > record){
		record = world->getScore();
		CCUserDefault::sharedUserDefault()->setIntegerForKey("RECORD", world->getScore());
		CCUserDefault::sharedUserDefault()->flush();
	}
	ostringstream convertRecord;  
	convertRecord<<record;
	labelRecord->setString("Record: " + convertRecord.str());

	if(!isPause){
		world->tryToPlayerGo(direction);
	}
		
}
	

void WorldScene::updateWorld(float dt){
	if(!isPause){
		for(int i=0; i < world->spirits->size(); i++){	
			if(world->spirits->get(i)->getState() == DEFENCE)
				world->spirits->get(i)->setDefence(isDefenceSpirit);
			world->spirits->get(i)->go(world);
		}
		world->deadPlayer();
		world->deadSpirit();
		 if (world->isGameOver() || world->isVictory()) {
            onPause();
        }

		if (world->getPlayer()->getState() == DEAD || world->isVictory()) {
			world->createSpirit();
			world->startPointPlayer();
			world->getPlayer()->setLife(3);
			world->generationPoint();
			world->setScore(0);
			isPause = false;
			
        }
        
       
	}

}

void WorldScene::onPause(){
	if(isPause){
		isPause = false;
	} else {
		isPause = true;
	}
}
bool WorldScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	seconds =0;
	isSound = CCUserDefault::sharedUserDefault()->getBoolForKey("SOUND", false);
	record = CCUserDefault::sharedUserDefault()->getIntegerForKey("RECORD",0);

	if(isSound){
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/sirensound.wav");
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/sirensound.wav", true);
	}
	

	direction = LEFT;
	isPause = false;

	readLevel = new ReadLevel();
	readLevel->readFile("level_1.txt", map);
	int size = readLevel->level->bricks->size();

	world = new World(readLevel->level);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(WorldScene::TouchBegan,this);
	touchListener->onTouchMoved = CC_CALLBACK_2(WorldScene::TouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(WorldScene::TouchEnded,this);
	getEventDispatcher()->addEventListenerWithFixedPriority(touchListener, 100);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
	setTouchMode(kCCTouchesOneByOne);
 

    labelRecord = LabelTTF::create("Record: ", FONT_EMULOGIC, 14);
    labelRecord->setPosition(Point(100,436));
	labelRecord->setColor(Color3B::YELLOW);

	labelScore = LabelTTF::create("You: ", FONT_EMULOGIC , 14);
    labelScore->setPosition(Point(610,436));
	labelScore->setColor(Color3B::YELLOW);
	

	for(int i=0; i < size; i++){
		this->addChild(readLevel->level->bricks->get(i)->getTexture(), 0);
	}
    this->addChild(labelRecord, 1);
	this->addChild(labelScore, 1);
	this->addChild(world->getPlayer()->getTexture(),2);
	for(int i=0; i < world->spirits->size(); i++){
		this->addChild(world->spirits->get(i)->getTexture(),2);
	}

    this->setKeyboardEnabled(true);
    this->schedule(schedule_selector(WorldScene::updatePlayer),0.05f);
	this->schedule(schedule_selector(WorldScene::updateWorld),0.07f);
	this->schedule(schedule_selector(WorldScene::timerTask),1.0f);
	this->schedule(schedule_selector(WorldScene::speedTask),0.03f);
    return true;
}

void WorldScene::timerTask(float dt){
	if(!isPause){
		if(world->isDefence()){
			seconds++;
                    if (seconds >= 8 && seconds % 2 == 0) {
                        isDefenceSpirit = true;
                    } else {
                        isDefenceSpirit = false;
                    }

                    if (seconds == 12) {
                        world->attackNPC();
						isDefenceSpirit = false;
                        seconds = 0;
						world->setDefenceSpirit(false);
                    }
		}
			
	}
}

void WorldScene::speedTask(float dt){
	if(!isPause){
		for(int i=0; i < world->spirits->size(); i++){	
			if(world->spirits->get(i)->getState() == DEAD)
				world->spirits->get(i)->go(world);
		}
	}
}

bool WorldScene::TouchBegan(Touch *touch, Event *event)
{
	touchX = touch->getLocation().x;
	touchY = touch->getLocation().y;
    return true;
}

 void WorldScene::TouchMoved(Touch* touch, CCEvent* event){
	 int x = touch->getLocation().x;
	 int y = touch->getLocation().y;
	 if (touchX > x && abs(x - touchX) > 20 && abs(y - touchY) < 60)
			direction = LEFT;
		if (touchX < x && abs(x - touchX) > 20 && abs(y - touchY) < 60)
			direction = RIGHT;
		if (touchY > y && abs(y - touchY) > 20 && abs(x - touchX) < 60)
			direction = DOWN;
		if (touchY < y && abs(y - touchY) > 20 && abs(x - touchX) < 60)
			direction = UP;
}
 void WorldScene::TouchEnded(Touch* touch, Event* event){
	 int x = touch->getLocation().x;
	 int y = touch->getLocation().y;
	 if (touchX > x && abs(y - touchY) < 60)
			direction = LEFT;
		if (touchX < x && abs(y - touchY) < 60)
			direction = RIGHT;
		if (touchY > y && abs(x - touchX) < 60)
			direction = DOWN;
		if (touchY < y && abs(x - touchX) < 60)
			direction = UP;
}

void WorldScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event){
	if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID){
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
		Director::getInstance()->pushScene(MainMenuScene::createScene());
	}
}