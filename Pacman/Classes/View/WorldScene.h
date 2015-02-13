#ifndef __WORLD_SCENE_H__
#define __WORLD_SCENE_H__

#include "View/AbstractScene.h"
#include "Model/ReadLevel.h"
#include "Model/World.h"
#include "Model/Direction.h"
#include "Controller/WorldController.h"
#include "Controller/SoundController.h"

class WorldScene : public AbstractScene {

private:
	WorldController* worldController_;
	SoundController* soundController_;

	EventListenerTouchOneByOne* touchListener_;
	EventListenerKeyboard*		keyboardListener_;
	ReadLevel* readLevel_; 
	World* world_;

	Layer* worldLayer_;
	Size size_;
	float positionX_;
	float positionY_;
	void updatePosition();

public:
	CC_SYNTHESIZE(bool, isSound_, Sound);
	CC_SYNTHESIZE(bool, isPause_, Pause);
	CC_SYNTHESIZE(bool, isDefenceSpirit_, DefenceSpirit);

    static WorldScene* create(std::string levelName, int currentLevel, SoundController* soundController);
    virtual bool init(std::string levelName, int currentLevel, SoundController* soundController);  
	virtual bool TouchBegan(Touch* touch, Event* event);
	virtual void TouchMoved(Touch* touch, Event* event);
	virtual void TouchEnded(Touch* touch, Event* event);

	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);
	void updatePlayer(float dt);
	void updateWorld(float dt);
	void timerTask(float dt);
	void speedTask(float dt);
	void generateFruit(float dt);
	
};
#endif // __HELLOWORLD_SCENE_H__
