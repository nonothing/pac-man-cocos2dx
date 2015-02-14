#include "model/Spirit/Spirit.h"
#include "model/World.h"

Spirit::Spirit(PPoint* position, ETexture texture, int width, int height, Level* level) :
		WorldObjectMove(position, texture, width, height) {
		level_ = level;
		setState(ATTACK);
		setCountStep(0);
		createMap(level_->getWidth(), level_->getHeight());
		countCollision_ = 0;
	}

void Spirit::refresh(BricksVec bricks) {
	if (getState() == DEAD) {
		setState(collidesWithRefresh(getBounds(), bricks));
	}
}

int Spirit::collidesWithRefresh(PRectangle* rect, BricksVec bricks) {
	return find_if(bricks.begin(), bricks.end(), [rect](Brick* brick){return brick->getBounds()->intersects(rect) && brick->getTextureName() == ENone;}) != bricks.end() ? ATTACK : DEAD; 
}

bool Spirit::collidesWithLevel(PRectangle* rect, BricksVec bricks) {
	return find_if(bricks.begin(), bricks.end(), [rect](Brick* brick){return brick->getBounds()->intersects(rect) && brick->getTextureName() > ECocos;}) != bricks.end(); 
}

void Spirit::go(BricksVec bricks, Player* player, PPoint* point) {
	clearMap();
	ai(bricks, player, point);
	sprite_->setPosition(position_->getX() + 15,position_->getY() + 15);
}

void Spirit::onLoadImageAttack() {
	switch (direction_) {
	case LEFT:
		setTexture(left());
		break;
	case RIGHT:
		setTexture(right());
		break;
	case DOWN:
		setTexture(down());
		break;
	case UP:
		setTexture(up());
		break;
	}
}

void Spirit::clearMap(){
	for (int row = 0; row < level_->getWidth(); row++) {
		for (int column = 0; column < level_->getHeight(); column++) {
			map[row][column] = 0;
		}
	}
}

void Spirit::onLoadImageDead() {
	switch (direction_) {
	case LEFT:
		setTexture(EOrbLeft);
		break;
	case RIGHT:
		setTexture(EOrbRight);
		break;
	case UP:
		setTexture(EOrbUp);
		break;
	case DOWN:
		setTexture(EOrbDown);
		break;
	}
}

void Spirit::onLoadImageDefence(bool isWhite) {
	setTexture(isWhite ? ESpiritDefenceWhite : EspiritDefence);
}

void Spirit::onLoadImage() {
	switch (getState()) {
	case ATTACK:
		onLoadImageAttack();
		break;
	case DEFENCE:
		onLoadImageDefence(leftDefence_);
		break;
	case DEAD:
		onLoadImageDead();
		break;
	}
}

void Spirit::move(BricksVec bricks) {
	onLoadImage();
	refresh(bricks);
	onMove(direction_);

	if (!collidesWithLevel(getBounds(), bricks)) {
		setPosition(getBounds());
		countCollision_ = 0;
	} else {
		countCollision_++;
		if(countCollision_ > 10){
			changeDirection(direction_);
			countCollision_ = 0;
		}
	}
	countStep_++;
}

void Spirit::findDirection(BricksVec bricks, PPoint* point) {
	potencialMap(point, bricks);
	if (getCountStep() >= (30 / SPEED_)) {
		for(int i=1 ; i <= 4; i++) {
			moveTo(getMap(), (Direction)i);
		}
		setCountStep(0);
	}
}

void Spirit::moveTo(int** map, Direction dir) {
	if (map[getPointX() + getHorizontalOffset(dir)][getPointY() + getVerticalOffset(dir)] < map[getPointX()][getPointY()] + 1) {
		setDirection(dir);
	}
}

int Spirit::getCountStep() {
	return countStep_;
}

void Spirit::setCountStep(int countStep) {
	this->countStep_ = countStep;
}

void Spirit::setDefence(bool isDefence) {
	this->leftDefence_ = isDefence;
}

void Spirit::createMap(int width, int height) {
	this->width_ = width;
	this->height_ = height;
	map = new int*[width];
	for (int i=0; i<width; i++)
		map[i] = new int[height];
}

void Spirit::potencialMap(PPoint* point, vector<Brick*> bricks) {
	inverseMap(bricks);
	int count = 0;
	step = 2;

	map[point->getX() / 30][point->getY() / 30] = 1;

	if (getState() != DEAD) {
		changeMap();
	}

	while (count < 40) {
		for (int row = 0; row < width_; row++) {
			for (int column = 0; column < height_; column++) {
				if (map[row][column] == step - 1) {
					if (row > 1) {
						if (map[row - 1][column] == 0) {
							map[row - 1][column] = step;
						}
					}
					if (row < width_ - 1) {
						if (map[row + 1][column] == 0) {
							map[row + 1][column] = step;
						}
					}
					if (column > 1) {
						if (map[row][column - 1] == 0) {
							map[row][column - 1] = step;
						}
					}
					if (column < height_ - 1) {
						if (map[row][column + 1] == 0) {
							map[row][column + 1] = step;
						}
					}
				}
			}
		}
		step++;
		count++;
	}

}

void Spirit::changeMap() {
	if (getDirection() == LEFT) {
		map[(getPointX()) + 1][getPointY()] = WALL;
	}

	if (getDirection() == RIGHT) {
		map[(getPointX()) - 1][getPointY()] = WALL;
	}

	if (getDirection() == DOWN) {
		map[getPointX()][(getPointY()) + 1] = WALL;
	}

	if (getDirection() == UP) {
		map[getPointX()][(getPointY()) - 1] = WALL;
	}
}

void Spirit::inverseMap(BricksVec bricks) {
	int row = 0;
	int column = 0;
	for(auto brick: bricks) {
		if(brick->getTextureName() <= ECocos) {
				map[row][column] = 0;
		} else {
			map[row][column] = WALL;
		}
		row++;
		if (row == width_) {
			row = 0;
			column++;
		}
		if (column == height_) {
			column = 0;
		}
	}
}

int** Spirit::getMap() {
	return map;
}

void Spirit::changeDirection(int dir) {
	int direction = dir + 1;
	if(direction > RIGHT) direction = UP;
	direction_ = direction;
}

int Spirit::getHorizontalOffset(Direction dir) {
	return dir == RIGHT ? 1 : dir == LEFT ? -1 : 0;
}

int Spirit::getVerticalOffset(Direction dir) {
	return dir == UP ? 1 : dir == DOWN ? -1 : 0;
}

