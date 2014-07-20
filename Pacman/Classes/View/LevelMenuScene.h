#ifndef __LEVELMENU_SCENE_H__
#define __LEVELMENU_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;
class LevelMenuScene : public cocos2d::Layer
{
	Sprite* background;
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
	
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
	
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    virtual bool TouchBegan(Touch* touch, Event* event);

    // implement the "static create()" method manually
    CREATE_FUNC(LevelMenuScene);

	void update(float dt);
};

#endif // __LEVELMENU_SCENE_H__
