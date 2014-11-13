#include "Pinky.h"

Pinky::Pinky(PPoint* point, Level* level) :
		Spirit(point, "pinkyUp", 30, 30, level) {
	START_POINT = new PPoint(point->getX(), point->getY());
	DEFENCE_POINT =  new PPoint(1, 2);
	level_ = level;
}
   void Pinky::ai(World* world) {
        switch (getState()) {
        case ATTACK:
            findDirection(world, findPathFourStep(world->getPlayer()), this);
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

PPoint* Pinky::findPathFourStep(Player* player) {
	potencialMap(player->getPosition(), this, level_->getBricks());

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

    string Pinky::left() {
        return "pinkyLeft";
    }

    string Pinky::right() {
        return "pinkyRight";
    }

    string Pinky::down() {
        return "pinkyDown";
    }

    string Pinky::up() {
        return "pinkyUp";
    }

