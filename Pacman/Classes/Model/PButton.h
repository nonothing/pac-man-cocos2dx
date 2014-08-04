#ifndef PBUTTON_H_
#define PBUTTON_H_

#include "Rectangle.h"
#include "Point.h"
#include "WorldObject.h"

using namespace std;

class PButton :public WorldObject{
public:
	PButton(){};
	PButton(PPoint* position, string texture, int width, int height);
	PRectangle* getRect();
};


#endif /* BRICK_H_ */