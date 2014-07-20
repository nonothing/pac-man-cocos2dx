#include "Model\Brick.h"

Brick::Brick(PPoint* position, string texture, int width, int height) :
		WorldObject(position, texture, width, height) {

}

bool Brick::tryToBonus(PRectangle* rectangle){
	  if (bounds->intersects(rectangle) && getTextureName() == "point") {
	            setTexture("background");
	            return true;
	        }
	        return false;
}

bool Brick::tryToEat(PRectangle* rectangle) {
	if (bounds->intersects(rectangle) && getTextureName() == "bonus") {
		setTexture("background");
		return true;
	}
	return false;
}
