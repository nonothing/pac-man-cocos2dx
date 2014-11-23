#include "Model/Point.h"

PPoint::PPoint(int x, int y) {
	this->x = x;
	this->y = y;
}

PPoint::PPoint(int x, int y, int width, int height) {
	this->x = x * width;
	this->y = y * height;
}

PPoint::PPoint(PRectangle* rectangle) {
	this->x = rectangle->getX();
	this->y = rectangle->getY();
}

int PPoint::getX() {
	return x;
}

int PPoint::getY() {
	return y;
}

PPoint* PPoint::multiply(int size) {
	return new PPoint(x, y, size,size);
}
