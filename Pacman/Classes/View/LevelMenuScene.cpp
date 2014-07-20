#include "LevelMenuScene.h"

using namespace cocos2d;
USING_NS_CC;

Scene* LevelMenuScene::createScene()
{

    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LevelMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

void LevelMenuScene::update(float dt){
	//CCLOG("%f", x);

	//sprite.position = ccp(sprite.x + x, sprite.y);

}

// on "init" you need to initialize your instance
bool LevelMenuScene::init()
{

    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(LevelMenuScene::TouchBegan,this);
	getEventDispatcher()->addEventListenerWithFixedPriority(touchListener, 100);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
	setTouchMode(kCCTouchesOneByOne);
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(LevelMenuScene::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("MainMenuScene", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    background = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    background->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(background, 0);
	//auto action = MoveBy::create(1, Point(100,3));
	//sprite->runAction(action);

    this->scheduleUpdate();
    return true;
}



void LevelMenuScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

bool LevelMenuScene::TouchBegan(Touch *touch, Event *event)
{
	CCLOG("x=%f  y=%f", touch->getLocation().x, touch->getLocation().y);
    CCLOG("dasdsa");
    return true;
}
