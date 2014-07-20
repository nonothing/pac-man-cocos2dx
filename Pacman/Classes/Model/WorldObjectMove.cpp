#include "WorldObjectMove.h"

WorldObjectMove::WorldObjectMove(PPoint* point, string texture, int width, int height) :WorldObject(point,texture,width, height){
	SPEED =5;
    direction = UP;
 }

 void WorldObjectMove::onMove(int direction) {
     switch (direction) {
     case RIGHT:setNext(SPEED, 0);         break;
     case LEFT: setNext(inverse(SPEED), 0);break;
	 case UP:   setNext(0, SPEED);break;
     case DOWN: setNext(0, inverse(SPEED));         break;
     }
 }

 int WorldObjectMove::getSpeed(){
     return SPEED;
 }

 int WorldObjectMove::getState() {
     return state;
 }

 void WorldObjectMove::setState(int state) {
     this->state = state;
 }

 int WorldObjectMove::getDirection() {
     return direction;
 }

 void WorldObjectMove::setDirection(int direction) {
     this->direction = direction;
 }

 void WorldObjectMove::setPosition(PRectangle* rect) {
     this->position = new PPoint(rect);
     bounds = rect;
 }

 void WorldObjectMove::setNext(int speedX, int speedY) {
     this->bounds = new PRectangle(position->getX() + speedX, position->getY()
             + speedY, getWidth(), getHeight());
}

 int WorldObjectMove::getPointX(){
     return position->getX() / getWidth();
 }

  int WorldObjectMove::getPointY(){
     return position->getY() / getHeight();
 }

