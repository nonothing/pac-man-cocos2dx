#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"
#include "Controller\MenuController.h"

USING_NS_CC;
class MainMenuScene : public cocos2d::Layer
{
	
	EventListenerTouchOneByOne* touchListener;
	MenuController* menuController;
public:
	bool isSound;
    static cocos2d::Scene* createScene();
    virtual bool init();  
    virtual bool TouchBegan(Touch* touch, Event* event);
	virtual void TouchMoved(Touch* touch, Event* event);
	virtual void TouchEnded(Touch* touch, Event* event);
    CREATE_FUNC(MainMenuScene);
	void setMenu(int item);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);
};

#endif // __MAINMENU_SCENE_H__
