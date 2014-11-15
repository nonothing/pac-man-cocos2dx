#ifndef WorldObjectMove_H_
#define WorldObjectMove_H_
#include "Direction.h"
#include "WorldObject.h"
#include "State.h"
using namespace std;

class WorldObjectMove: public WorldObject {

protected:
	int direction_;
	int SPEED_;
	int state_;

public:
	WorldObjectMove(PPoint* point, ETexture texture, int width, int height);
	virtual ~WorldObjectMove(){};
	void onMove(int direction);
	int getSpeed();
	int getState();
	int getDirection();
	void setState(int state);
	void setDirection(int direction);
	void setPosition(PRectangle* rect);
	void setNext(int speedX, int speedY);
	int getPointX();
	int getPointY();

};
#endif /* WorldObjectMove_H_ */
