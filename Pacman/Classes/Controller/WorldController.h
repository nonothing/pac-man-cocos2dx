#ifndef WORLD_CONTROLLER_H_
#define WORLD_CONTROLLER_H_
#include "Model\World.h"
#define FONT_EMULOGIC "fonts/emulogic.ttf"
using namespace std;

class WorldController{
	World* world;
	bool isPause;
	bool isDefenceSpirit;
	int seconds;
	int record;
	Direction direction;
	LabelTTF* labelScore;
	LabelTTF* labelRecord;
	int touchX;
	int touchY;
public:
	void init(World* world);
	void onPause();
	void updateWorld(float dt);
	void updatePlayer(float dt);
	void timerTask(float dt);
	void speedTask(float dt);
	void setRecord(int score){record = score;}
	void setDirection(Direction d){ direction = d;}
	LabelTTF* getLabelScore(){return labelScore;}
	LabelTTF* getLabelRecord(){return labelRecord;}
	void setTouch(int x, int y){touchX = x;	touchY = y;}
	void TouchMoved(int x, int y);
	void TouchEnded(int x, int y);
};
#endif /* WORLD_CONTROLLER_H_ */
