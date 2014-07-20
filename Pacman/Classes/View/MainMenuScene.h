#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;
class MainMenuScene : public cocos2d::Layer
{
	Sprite* background;
	char* token;
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
	
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
	
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    virtual bool TouchBegan(Touch* touch, Event* event);


    // implement the "static create()" method manually
    CREATE_FUNC(MainMenuScene);
	void playButtonCallback(Ref* pSender);
	void update(float dt);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);
};

#endif // __MAINMENU_SCENE_H__
