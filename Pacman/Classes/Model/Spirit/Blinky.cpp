#include "model/Spirit/Blinky.h"

Blinky::Blinky(PPoint* point, Level* level) :
		Spirit(point, EBlinkyUp, 30, 30, level) {
	START_POINT = new PPoint(point->getX(), point->getY());
	DEFENCE_POINT = new PPoint(21, 1);
}

void Blinky::ai(BricksVec bricks, Player* player, PPoint* point) {
	switch (getState()) {
	case ATTACK:
		findDirection(bricks, player->getPosition());
		break;
	case DEFENCE:
		findDirection(bricks, DEFENCE_POINT->multiply(getWidth()));
		break;
	case DEAD:
		findDirection(bricks, START_POINT->multiply(getWidth()));
		break;
	}

	move(bricks);
}

ETexture Blinky::left() {
	return EBlinkyLeft;
}

ETexture Blinky::right() {
	return EBlinkyRight;
}

ETexture Blinky::down() {
	return EBlinkyDown;
}

ETexture Blinky::up() {
	return EBlinkyUp;
}

