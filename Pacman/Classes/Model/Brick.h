#ifndef BRICK_H_
#define BRICK_H_

#include "Rectangle.h"
#include "Point.h"
#include "WorldObject.h"

using namespace std;

class Brick :public WorldObject{
public:
	Brick(){};
	Brick(PPoint* position , string texture ,int width, int height);
    bool tryToEat(PRectangle* rectangle);
    bool tryToBonus(PRectangle* rectangle);
};


#endif /* BRICK_H_ */
