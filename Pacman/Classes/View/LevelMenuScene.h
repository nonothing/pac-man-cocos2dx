#ifndef __LEVELMENU_SCENE_H__
#define __LEVELMENU_SCENE_H__

#include "cocos2d.h"
#include "Model\List.h"
#include "Model\LevelMenu.h"
#include "Model\Rectangle.h"

USING_NS_CC;
class LevelMenuScene : public Layer
{
	EventListenerTouchOneByOne* touchListener;
	List<LevelMenu*>* levels;
	PRectangle* rectangle;

public:
    static Scene* createScene();
    virtual bool init();  
    virtual bool TouchBegan(Touch* touch, Event* event);
	virtual void TouchMoved(Touch* touch, Event* event);
	virtual void TouchEnded(Touch* touch, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);
	string parseLevel(int number);

	LevelMenu* createLevel(int x, int y);

    CREATE_FUNC(LevelMenuScene);
};

#endif // __LEVELMENU_SCENE_H__
