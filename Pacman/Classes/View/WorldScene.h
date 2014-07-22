#ifndef __WORLD_SCENE_H__
#define __WORLD_SCENE_H__

#include "cocos2d.h"
#include "Model\ReadLevel.h"
#include "Model\World.h"
#include "Model\Direction.h"
#include "Controller\WorldController.h"

using namespace std;

USING_NS_CC;
class WorldScene : public cocos2d::Layer
{
	WorldController* worldController;
	ReadLevel* readLevel; 
	World* world;

public:
	
	bool isSound;
	bool isPause;
	bool isDefenceSpirit;
    static cocos2d::Scene* createScene();
    virtual bool init();  
	virtual bool TouchBegan(Touch* touch, Event* event);
	virtual void TouchMoved(Touch* touch, Event* event);
	virtual void TouchEnded(Touch* touch, Event* event);
    CREATE_FUNC(WorldScene);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);
	void updatePlayer(float dt);
	void updateWorld(float dt);
	void timerTask(float dt);
	void speedTask(float dt);
};
#endif // __HELLOWORLD_SCENE_H__
