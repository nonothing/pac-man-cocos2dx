#include "Player.h"

Player::Player(PPoint* position , ETexture texture ,int width, int height) :WorldObjectMove(position,texture,width,height){
		life_ = 3;
		state_ = DEFENCE;
	}

bool Player::eatPoint(const BricksVec bricks) const {
	return find_if(bricks.begin(), bricks.end(), [this](Brick* brick){ return brick->tryToEat(this->bounds_); }) != bricks.end();
}

bool Player::eatBonus(const BricksVec bricks) {
	if(find_if(bricks.begin(), bricks.end(), [this](Brick* brick){ return brick->tryToBonus(this->bounds_); }) != bricks.end()) {
		state_ = ATTACK;
		return true;
	}
	return false;
}

bool Player::eatFruit(const BricksVec bricks) const{
	return find_if(bricks.begin(), bricks.end(), [this](Brick* brick){ return brick->tryToFruit(this->bounds_); }) != bricks.end();
}

void Player::animate() {
        bool change =
                (getPosition()->getX() % 15 == 0 && (direction_ == LEFT || direction_ == RIGHT))
                || (getPosition()->getY() % 15 == 0 && (direction_ == UP || direction_ == DOWN));
		
        if(change){
        	isOpen_ = !isOpen_;
        }
		int open = isOpen_ ? 1:0;

		switch (direction_)	{
		case LEFT:	setTexture(getNumber(EPacmanLeftClose, open));	break;
		case RIGHT: setTexture(getNumber(EPacmanRightClose, open)); break;
		case DOWN:	setTexture(getNumber(EPacmanDownClose, open)); break;
		case UP:	setTexture(getNumber(EPacmanUpClose, open)); break;
		}
    }

ETexture Player::getNumber(ETexture texture, int open) const {
	return ETexture((int)texture - open);
}


