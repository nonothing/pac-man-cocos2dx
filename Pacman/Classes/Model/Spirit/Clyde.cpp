#include "model/Spirit/Clyde.h"

Clyde::Clyde(PPoint* point, Level* level): Spirit(point, EClydeUp,30,30, level) {
	START_POINT = new PPoint(point->getX(), point->getY());
	DEFENCE_POINT = new PPoint(2, 13);
}

void Clyde::ai(BricksVec bricks, Player* player, PPoint* point) {
	switch (getState()) {
	case ATTACK:
		AIattack(player, bricks);
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

void Clyde::AIattack(Player* player, BricksVec bricks) {
	potencialMap(player->getPosition(), bricks);

	int step = getMap()[getPointX()][getPointY()];

	if (step <= 9) {
		findDirection(bricks, new PPoint(1 , 2, getWidth(),getHeight()));
	} else {
		findDirection(bricks, player->getPosition());
	}
}

ETexture Clyde::left() {
	return EClydeLeft;
}

ETexture Clyde::right() {
	return EClydeRight;
}

ETexture Clyde::down() {
	return EClydeDown;
}

ETexture Clyde::up() {
	return EClydeUp;
}

