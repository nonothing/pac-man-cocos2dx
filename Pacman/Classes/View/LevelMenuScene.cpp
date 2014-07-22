#include "LevelMenuScene.h"
#include "View\MainMenuScene.h"


using namespace cocos2d;
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
	}

	setTouchMode(kCCTouchesOneByOne);
	this->setKeyboardEnabled(true);
    return true;
}

LevelMenu* LevelMenuScene::createLevel(int x, int y){
	return new LevelMenu(new PPoint(x, y), "lock_gold_star", 80, 80);
}

bool LevelMenuScene::TouchBegan(Touch *touch, Event *event)
{
	CCLOG("x=%f  y=%f", touch->getLocation().x, touch->getLocation().y);
    CCLOG("dasdsa");
    return true;
}

void LevelMenuScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event){
	if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID){
		getEventDispatcher()->removeEventListener(touchListener);
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
		Director::getInstance()->pushScene(MainMenuScene::createScene());
	}
}