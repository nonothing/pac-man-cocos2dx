#ifndef __LEVELMENU_SCENE_H__
#define __LEVELMENU_SCENE_H__

#include "cocos2d.h"
#include "Model\List.h"
#include "Model\LevelMenu.h"

USING_NS_CC;
class LevelMenuScene : public cocos2d::Layer
{
	EventListenerTouchOneByOne* touchListener;
	List<LevelMenu*>* levels;

public:
    static cocos2d::Scene* createScene();
    virtual bool init();  
    virtual bool TouchBegan(Touch* touch, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);
	LevelMenu* createLevel(int x, int y);

    CREATE_FUNC(LevelMenuScene);
};

#endif // __LEVELMENU_SCENE_H__
