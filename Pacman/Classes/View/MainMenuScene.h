#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;
class MainMenuScene : public cocos2d::Layer
{
	LabelTTF* buttonPlay;
	LabelTTF* buttonLevel;
	LabelTTF* buttonSound;
	LabelTTF* buttonExit;
	EventListenerTouchOneByOne* touchListener;
public:
	bool isSound;
    static cocos2d::Scene* createScene();
    virtual bool init();  
    virtual bool TouchBegan(Touch* touch, Event* event);
	virtual void TouchMoved(Touch* touch, Event* event);
	virtual void TouchEnded(Touch* touch, Event* event);
	static bool getBooleanForKey(const char* key);
    static void setBooleanForKey(const char* key, bool obj);
	void selectMenuItem(int y, bool isTouch);
    CREATE_FUNC(MainMenuScene);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);
};

#endif // __MAINMENU_SCENE_H__
