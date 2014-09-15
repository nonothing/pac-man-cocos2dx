#include "Player.h"

Player::Player(PPoint* position , string texture ,int width, int height) :WorldObjectMove(position,texture,width,height){
		life_ = 3;
		state_ = DEFENCE;
	}

bool Player::eatPoint(List<Brick*>* bricks){
	for(int i=0; i < bricks->size(); i++){
	            if(bricks->get(i)->tryToEat(bounds_))
	                return true;
	        }
	        return false;
}

bool Player::eatBonus(List<Brick*>* bricks) {
	for(int i=0; i < bricks->size(); i++){
		if(bricks->get(i)->tryToBonus(bounds_)){
           state_ = ATTACK;
           return true;
           }
   }
   return false;
}

void Player::animate() {
        bool change =
                (getPosition()->getX() % 15 == 0 && (direction_ == LEFT || direction_ == RIGHT))
                || (getPosition()->getY() % 15 == 0 && (direction_ == UP || direction_ == DOWN));
		
        if(change){
        	if(isOpen_)isOpen_ = false;
        	else isOpen_ = true;
        }

        if (direction_ == LEFT) {
            if (isOpen_) {
                setTexture("pacmanLeftOpen");
            } else {
                setTexture("pacmanLeftClose");
            }
        }
        if (direction_ == RIGHT) {
            if (isOpen_) {
                setTexture("pacmanRightOpen");
            } else {
                setTexture("pacmanRightClose");
            }
        }
        if (direction_ == UP) {
            if (isOpen_) {
                setTexture("pacmanUpOpen");
            } else {
                setTexture("pacmanUpClose");
            }
        }
        if (direction_ == DOWN) {
            if (isOpen_) {
                setTexture("pacmanDownOpen");
            } else {
                setTexture("pacmanDownClose");
            }
        }
    }
