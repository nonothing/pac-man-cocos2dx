#include "WorldObjectMove.h"

WorldObjectMove::WorldObjectMove(PPoint* point, ETexture texture, int width, int height) :WorldObject(point,texture,width, height){
	SPEED_ =5;
    direction_ = UP;
 }

 void WorldObjectMove::onMove(int direction) {
     switch (direction) {
     case RIGHT:setNext(SPEED_, 0);         break;
     case LEFT: setNext(inverse(SPEED_), 0);break;
	 case UP:   setNext(0, SPEED_);break;
     case DOWN: setNext(0, inverse(SPEED_));         break;
     }
 }

 int WorldObjectMove::getSpeed(){
     return SPEED_;
 }

 int WorldObjectMove::getState() {
     return state_;
 }

 void WorldObjectMove::setState(int state) {
     this->state_ = state;
 }

 int WorldObjectMove::getDirection() {
     return direction_;
 }

 void WorldObjectMove::setDirection(int direction) {
     this->direction_ = direction;
 }

 void WorldObjectMove::setPosition(PRectangle* rect) {
     this->position_ = new PPoint(rect);
     bounds_ = rect;
 }

 void WorldObjectMove::setNext(int speedX, int speedY) {
     this->bounds_ = new PRectangle(position_->getX() + speedX, position_->getY()
             + speedY, getWidth(), getHeight());
}

 int WorldObjectMove::getPointX(){
     return position_->getX() / getWidth();
 }

  int WorldObjectMove::getPointY(){
     return position_->getY() / getHeight();
 }

