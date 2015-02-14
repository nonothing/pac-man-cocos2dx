#ifndef BRICK_H_
#define BRICK_H_

#include "Rectangle.h"
#include "Point.h"
#include "WorldObject.h"

using namespace std;



class Brick :public WorldObject{
public:
	Brick(){};
	Brick(PPoint* position , ETexture texture ,int width, int height);
    bool tryToEat(PRectangle* rectangle);
    bool tryToBonus(PRectangle* rectangle);
	bool tryToFruit(PRectangle* rectangle);
};

typedef vector<Brick*> BricksVec;

#endif /* BRICK_H_ */
