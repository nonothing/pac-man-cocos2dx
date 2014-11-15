#include "Model\PButton.h"

PButton::PButton(PPoint* position, ETexture texture, int width, int height) :
		WorldObject(position, texture, width, height) {

}

PRectangle* PButton::getRect(){
	return new PRectangle(getSpriteX(), getSpriteY(), 80, 80);
}