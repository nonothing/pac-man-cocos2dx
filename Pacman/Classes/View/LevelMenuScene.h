#ifndef __LEVELMENU_SCENE_H__
#define __LEVELMENU_SCENE_H__

#include "cocos2d.h"
#include "Model\List.h"
#include "Model\LevelMenu.h"
#include "Model\Rectangle.h"
#include "Model\PButton.h"

USING_NS_CC;
class LevelMenuScene : public Layer
{
	EventListenerTouchOneByOne* touchListener;
	List<LevelMenu*>* levels;
	PRectangle* rectangle;
	PButton* buttonArrowLeft;
	PButton* buttonArrowRight;
	int page;

public:
    static Scene* createScene();
    virtual bool init();  
    virtual bool TouchBegan(Touch* touch, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);
	string parseLevel(int number);

	LevelMenu* createLevel(int x, int y);

    CREATE_FUNC(LevelMenuScene);
};

#endif // __LEVELMENU_SCENE_H__
