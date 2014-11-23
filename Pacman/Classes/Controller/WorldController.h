#ifndef WORLD_CONTROLLER_H_
#define WORLD_CONTROLLER_H_
#include "Model/World.h"
#include "Controller/SoundController.h"
#define FONT_EMULOGIC "fonts/emulogic.ttf"
using namespace std;

class WorldController{
private:
	World* world;
	SoundController* soundController_;
	bool isPause;
	bool isDefenceSpirit;
	int seconds;
	int record;
	Direction direction;
	CCLabelTTF* labelScore;
	CCLabelTTF* labelRecord;
	int touchX;
	int touchY;
public:
	void init(World* world, SoundController* soundController);
	void onPause();
	void updateWorld(float dt);
	void updatePlayer(float dt);
	void timerTask(float dt);
	void speedTask(float dt);
	void generateFruit(float dt);
	void setRecord(int score){record = score;}
	void setDirection(Direction d){ direction = d;}
	LabelTTF* getLabelScore(){return labelScore;}
	LabelTTF* getLabelRecord(){return labelRecord;}
	void setTouch(int x, int y){touchX = x;	touchY = y;}
	void TouchMoved(int x, int y);
	void TouchEnded(int x, int y);
	World* getWorld(){ return world; }
	void newWorld();
	void respawn();
};
#endif /* WORLD_CONTROLLER_H_ */
