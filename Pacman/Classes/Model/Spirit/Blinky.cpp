#include "model/Spirit/Blinky.h"

Blinky::Blinky(PPoint* point, Level* level) :
		Spirit(point, EBlinkyUp, 30, 30, level) {
	START_POINT = new PPoint(point->getX(), point->getY());
	DEFENCE_POINT = new PPoint(21, 1);
}

void Blinky::ai(World* world) {
	switch (getState()) {
	case ATTACK:
		findDirection(world, world->getPlayer()->getPosition(), this);
		break;
	case DEFENCE:
		findDirection(world, DEFENCE_POINT->multiply(getWidth()), this);
		break;
	case DEAD:
		findDirection(world, START_POINT->multiply(getWidth()), this);
		break;
	}

	move(world);
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

