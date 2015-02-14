#include "Pinky.h"

Pinky::Pinky(PPoint* point, Level* level) :
		Spirit(point, EPinkyUp, 30, 30, level) {
	START_POINT = new PPoint(point->getX(), point->getY());
	DEFENCE_POINT =  new PPoint(1, 2);
	level_ = level;
}
void Pinky::ai(BricksVec bricks, Player* player, PPoint* point) {
	switch (getState()) {
	case ATTACK:
		findDirection(bricks, findPathFourStep(player));
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

PPoint* Pinky::findPathFourStep(Player* player) {
	potencialMap(player->getPosition(), level_->getBricks());

	PPoint* point = new PPoint(0, 0);
	int** map = getMap();
	int min = 0;
	int max = 999;

	for (int row = 0; row < level_->getWidth(); row++) {
		for (int column = 0; column < level_->getHeight(); column++) {
			if (map[row][column] == 5) {
				switch (player->getDirection()) {
				case LEFT: 
					if (max > row) {
						max = row;
						point = new PPoint(row, column, getWidth(), getHeight());
					}
					break;
				case RIGHT: 
					if (min < row) {
						min = row;
						point = new PPoint(row, column, getWidth(), getHeight());
					}
					break;
				case UP:
					if (max > column) {
						max = column;
						point = new PPoint(row, column, getWidth(), getHeight());
					}
					break;
				case DOWN:
					if (min < column) {
						min = column;
						point = new PPoint(row, column, getWidth(), getHeight());
					}
					break;
				default:
					break;
				}
			}
		}
	}

	return point;
}

ETexture Pinky::left() {
    return EPinkyLeft;
}

ETexture Pinky::right() {
    return EPinkyRight;
}

ETexture Pinky::down() {
    return EPinkyDown;
}

ETexture Pinky::up() {
    return EPinkyUp;
}

