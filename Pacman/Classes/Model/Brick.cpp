#include "Model/Brick.h"

Brick::Brick(PPoint* position, ETexture texture, int width, int height) :
		WorldObject(position, texture, width, height) {

}

bool Brick::tryToBonus(PRectangle* rectangle) {
	  if (bounds_->intersects(rectangle) && getTextureName() == EBonus) {
	            setTexture(EBackground);
	            return true;
	        }
	  return false;
}

bool Brick::tryToEat(PRectangle* rectangle) {
	if (bounds_->intersects(rectangle) && getTextureName() == EPoint) {
		setTexture(EBackground);
		return true;
	}
	return false;
}

bool Brick::tryToFruit(PRectangle* rectangle) {
	if (bounds_->intersects(rectangle) 
		&&( getTextureName() >= EBanana &&  getTextureName() <= ECocos)) {
		setTexture(EBackground);
		return true;
	}
	return false;
}
