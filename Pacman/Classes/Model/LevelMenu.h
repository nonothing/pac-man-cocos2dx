#ifndef LEVEL_MENU_H_
#define LEVEL_MENU_H_

#include "Rectangle.h"
#include "Point.h"
#include "WorldObject.h"

using namespace std;

class LevelMenu :public WorldObject{
public:
	LevelMenu(){};
	LevelMenu(PPoint* position, string texture, int width, int height);

};


#endif /* LEVEL_MENU_H_ */
