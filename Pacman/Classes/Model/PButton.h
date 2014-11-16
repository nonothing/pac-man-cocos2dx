#ifndef PBUTTON_H_
#define PBUTTON_H_

#include "Rectangle.h"
#include "Point.h"
#include "WorldObject.h"

using namespace std;

class PButton :public WorldObject {
public:
	PButton(){};
	PButton(PPoint* position, ETexture texture, int width, int height);
	PRectangle* getRect();
	void show(int currentPage,int pageMinMax);
};


#endif /* BRICK_H_ */
