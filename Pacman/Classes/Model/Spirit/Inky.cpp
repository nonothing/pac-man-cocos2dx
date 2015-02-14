#include "Inky.h"

Inky::Inky(PPoint* point, Level* level) :
		Spirit(point, EInkyUp, 30, 30, level) {
	START_POINT = new PPoint(point->getX(), point->getY());
	DEFENCE_POINT = new PPoint(21, 13);
	level_ = level;
}

void Inky::ai(BricksVec bricks, Player* player, PPoint* point) {
    switch (getState()) {
    case ATTACK:
        findDirection(bricks, doubleVectorBetweenTwoPoints(findPathTwoStep(player), point));
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

PPoint* Inky::doubleVectorBetweenTwoPoints(PPoint* point1, PPoint* point2) {

	aMatrix[0] = point2->getX() / getWidth();
	aMatrix[1] = point2->getY() / getHeight();
	aMatrix[2] = 1;
		 
	bMatrix[0][1] = -1;
	bMatrix[0][2] = 0;
	bMatrix[0][3] = 0;

	bMatrix[1][1] = 0;
	bMatrix[1][2] = -1;
	bMatrix[1][3] = 0;

	bMatrix[2][1] = 2 * (point1->getX() / getWidth());
	bMatrix[2][2] = 2 * (point1->getY() / getHeight());
	bMatrix[2][3] = 1;

       
		point[0] =0;
		point[1] =0;
		point[2] =0;

    for (int column = 0; column < 3; column++) {
        for (int inner = 0; inner < 3; inner++) {
            point[column] += aMatrix[inner] * bMatrix[inner][column];
        }

    }
    if (point[X] >= 25) {
        point[X] = 24;
    }
    if (point[X] < 1) {
        point[X] = 1;
    }
    if (point[Y] >= 14) {
        point[Y] = 13;
    }
    if (point[Y] < 1) {
        point[Y] = 1;
    }

    return new PPoint(point[X], point[Y],getWidth(), getHeight());
}


PPoint* Inky::findPathTwoStep(Player* player) {
    potencialMap(player->getPosition(), level_->getBricks());

    int** map = getMap();
    int min = 0;
    int max = 999;

    PPoint* point = new PPoint(0,0);
    for (int row = 0; row < level_->getWidth(); row++) {
        for (int column = 0; column < level_->getHeight(); column++) {
            if (map[row][column] == 3) {

				switch (player->getDirection()) {
				case LEFT: 
					if (max > row) {
						max = row;
						point = new PPoint(row, column,getWidth(), getHeight());
					}
					break;
				case RIGHT:
					if (min < row) {
						min = row;
						point = new PPoint(row, column,getWidth(), getHeight());
					}
					break;
				case DOWN: 
					if (min < column) {
						min = column;
						point = new PPoint(row, column,getWidth(), getHeight());
					}
					break;
				case  UP:
					if (max > column) {
						max = column;
						point = new PPoint(row, column,getWidth(), getHeight());
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

ETexture Inky::left() {
    return EInkyLeft;
}

ETexture Inky::right() {
    return EInkyRight;
}

ETexture Inky::down() {
    return EInkyDown;
}

ETexture  Inky::up() {
    return EInkyUp;
}

