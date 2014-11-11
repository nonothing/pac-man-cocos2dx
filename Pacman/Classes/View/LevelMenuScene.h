#ifndef __LEVELMENU_SCENE_H__
#define __LEVELMENU_SCENE_H__

#include "View\AbstractScene.h"
#include "Model\List.h"
#include "Model\LevelMenu.h"
#include "Model\Rectangle.h"
#include "Model\PButton.h"

class LevelMenuScene :public AbstractScene {
	EventListenerTouchOneByOne* touchListener_;
	List<LevelMenu*>* levels_;
	PRectangle* rectangle_;
	PButton* buttonArrowLeft_;
	PButton* buttonArrowRight_;
	int page_;

public:
    static LevelMenuScene* create();
    virtual bool init();  
    virtual bool TouchBegan(Touch* touch, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);
	static string parseLevel(int number);

	LevelMenu* createLevel(int x, int y);
};

#endif // __LEVELMENU_SCENE_H__
