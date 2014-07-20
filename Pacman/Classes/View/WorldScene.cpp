#include "View\WorldScene.h"
#include "Model\ReadLevel.h"

using namespace cocos2d;
USING_NS_CC;

Scene* WorldScene::createScene()
{
    auto scene = Scene::create();
    auto layer = WorldScene::create();
    scene->addChild(layer);
    return scene;
}

void WorldScene::update(float dt){
	
		world->tryToPlayerGo(LEFT);		
}

bool WorldScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	readLevel = new ReadLevel();
	readLevel->readFile("level_1.txt", map);
	int size = readLevel->level->bricks->size();

	world = new World(readLevel->level);
	
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(WorldScene::TouchBegan,this);
	getEventDispatcher()->addEventListenerWithFixedPriority(touchListener, 100);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
	setTouchMode(kCCTouchesOneByOne);
 

    auto labelRecord = LabelTTF::create("Record: ", FONT_EMULOGIC, 14);
    labelRecord->setPosition(Point(100,436));
	labelRecord->setColor(Color3B::YELLOW);

	auto labelScore = LabelTTF::create("You: ", FONT_EMULOGIC , 14);
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
    this->schedule(schedule_selector(WorldScene::update),0.05f);
    return true;
}

bool WorldScene::TouchBegan(Touch *touch, Event *event)
{
	CCLOG("x=%f  y=%f", touch->getLocation().x, touch->getLocation().y);
    return true;
}

void WorldScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event){
	if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID){
		Director::getInstance()->popScene();
	}
}