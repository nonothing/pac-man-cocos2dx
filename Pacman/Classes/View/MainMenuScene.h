#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "View\AbstractScene.h"
#include "Controller\MenuController.h"

class MainMenuScene : public AbstractScene {

private:
	EventListenerTouchOneByOne* touchListener_;
	MenuController* menuController_;

public:
	CC_SYNTHESIZE(bool, isSound_,Sound);
    static MainMenuScene* create();
    virtual bool init();  
    virtual bool TouchBegan(Touch* touch, Event* event);
	virtual void TouchMoved(Touch* touch, Event* event);
	virtual void TouchEnded(Touch* touch, Event* event);
	void setMenu(int item);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);
};

#endif // __MAINMENU_SCENE_H__
