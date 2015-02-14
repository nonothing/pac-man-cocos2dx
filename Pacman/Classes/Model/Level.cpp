#include "Model/Level.h"

void Level::setPointBlinky(PPoint* point) {
	pointBlinky_ = point;
}

PPoint* Level::getPointBlinky() const {
	return pointBlinky_;
}

void Level::setPointPinky(PPoint* point) {
	pointPinky_ = point;
}

PPoint* Level::getPointPinky() const {
	return pointPinky_;
}

void Level::setPointClyde(PPoint* point) {
	pointClyde_ = point;
}

PPoint* Level::getPointClyde() const {
	return pointClyde_;
}

void Level::setPointInky(PPoint* point) {
	pointInky_ = point;
}

PPoint* Level::getPointInky() const {
	return pointInky_;
}

BricksVec Level::getBricks() const {
	return bricks_;
}

void Level::setBricks(BricksVec bricks) {
	bricks_ = bricks;
}
