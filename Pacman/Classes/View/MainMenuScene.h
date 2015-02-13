#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "View/AbstractScene.h"
#include "Controller/MenuController.h"
#include "Controller/SoundController.h"

class MainMenuScene : public AbstractScene {

private:
	EventListenerTouchOneByOne* touchListener_;
	EventListenerKeyboard* keyboardListener_;

	MenuController* menuController_;
	SoundController* soundController_;
public:
	CC_SYNTHESIZE(bool, isSound_,Sound);
    static MainMenuScene* create(SoundController* soundController);
    virtual bool init(SoundController* soundController);  
    virtual bool TouchBegan(Touch* touch, Event* event);
	virtual void TouchMoved(Touch* touch, Event* event);
	virtual void TouchEnded(Touch* touch, Event* event);
	void setMenu(int item);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);
};

#endif // __MAINMENU_SCENE_H__
