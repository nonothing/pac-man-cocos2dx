#include "World.h"
#include "model/Spirit/Blinky.h"
#include "model/Spirit/Clyde.h"
#include "model/Spirit/Inky.h"
#include "model/Spirit/Pinky.h"
#include "Controller/SoundController.h"
#include <numeric>

World::World(Level* level, SoundController* soundController){
	isSound_ = UserDefault::getInstance()->getBoolForKey("SOUND", false);
	player_ = new Player(new PPoint(12, 9), EPacmanUpOpen, 30, 30);
	player_->setDirection(LEFT);
	spirits_.push_back(new Blinky(level->getPointBlinky(), level));
	spirits_.push_back(new Clyde(level->getPointClyde(), level));
	spirits_.push_back(new Inky(level->getPointInky(), level));
	spirits_.push_back(new Pinky(level->getPointPinky(), level));
	bricks_ = level->getBricks();
	score_ = 0;
	isDefenceSpirit_ = false;
	countPoint_ = generationPoint();

	if(isSound_) {
		soundController_->preloadEffect(ESounds::ES_PACMAN_COINING);
		soundController_->preloadEffect(ESounds::ES_EAT_FRUIT);
		soundController_->preloadEffect(ESounds::ES_EAT_SPIRIT);
	}
}

World::~World(){
	delete player_;
	for(auto brick: bricks_) {
		delete brick;
	}
	bricks_.clear();

	for(auto spirit: spirits_) {
		delete spirit;
	}
	spirits_.clear();
}

void World::tryToPlayerGo(int direction){
	player_->onMove(direction);

	if(!collidesWithLevel(player_->getBounds())){
		player_->setDirection(direction);
	}
	player_->onMove(player_->getDirection());
	if(!collidesWithLevel(player_->getBounds())){
		player_->setPosition(player_->getBounds());
		player_->animate();
		player_->getTexture()->setPosition(player_->getPosition()->getX()  + 15, player_->getPosition()->getY() + 15);
	}
	eatBonus();
	eatPoint();
	eatFruit();
}

Player* World::getPlayer(){
	return player_;
}

int World::generationPoint() {
	int result = 0;
	for(auto brick: bricks_) {
		if(brick->getTextureName() == EBackground) {
			brick->setTexture(EPoint);
			result++;
		}
	}
	countPoint_ += result;
	return result;
}

void World::generationFruit() {
	std::vector<int> emptyBrick;
	for(time_t i=0; i < bricks_.size(); i++){
		if(bricks_.at(i)->getTextureName() == EBackground){
			emptyBrick.push_back(i);
		}
		if(isFruit(bricks_.at(i)->getTextureName())) {
			bricks_.at(i)->setTexture(EBackground);
			return;
		}
	}
	if((int)emptyBrick.size() > bricks_.size() / 10) {
		int randomNumber = rand() % emptyBrick.size();
		int randomFruit = rand() % 6;
		ETexture textureName;

		switch (randomFruit) {
		case 0:   textureName = EBanana;		break;
		case 1:   textureName = EApple;			break;
		case 2:   textureName = EAppleRed;		break;
		case 3:   textureName = EVinograd;		break;
		case 4:   textureName = EOrange;		break;
		case 5:   textureName = ECocos;			break;
		default:  textureName = EBackground;	break;
		}

		bricks_.at(emptyBrick.at(randomNumber))->setTexture(textureName);
	}
}

bool World::eatPoint(){
	if (player_->eatPoint(bricks_)) {
		countPoint_--;
		score_ += 50;
		if(isSound_){
			soundController_->playEffect(ESounds::ES_PACMAN_COINING);
		}
		return true;
	}
	return false;
}

bool World::eatBonus(){
	if (player_->eatBonus(bricks_)) {
		score_ += 500;
		defenceNPC();
		isDefenceSpirit_ = true;
		if(isSound_){
			soundController_->playEffect(ESounds::ES_EAT_FRUIT);	
		}
		return true;
	}
	return false;
}


void World::defenceNPC() {
	for(auto spirit: spirits_) {
		if (spirit->getState() == ATTACK) {
			spirit->setState(DEFENCE);
		}
	}
}

void World::attackNPC() {
	for(auto spirit: spirits_) {
		if (spirit->getState() == DEFENCE) {
			spirit->setState(ATTACK);
		}
	}
	player_->setState(DEFENCE);
}

bool World::deadSpirit() {
	for(auto spirit: spirits_) {
		if ((spirit->getBounds()->intersects(player_->getBounds()))) {
			if (player_->getState() == ATTACK && spirit->getState() != DEAD){
				score_ += 1000;
				spirit->setState(DEAD);
				if(isSound_){
					soundController_->playEffect(ESounds::ES_EAT_FRUIT);
				}
				return true;
			}
		}
	}
	return false;
}

bool World::deadPlayer(){
	for(auto spirit: spirits_) {
		if ((spirit->getBounds()->intersects(player_->getBounds()))) {
			if (spirit->getState() == ATTACK){
				player_->setState(DEAD);
				player_->setLife(player_->getLife() - 1);
				return true;
			}
		}
	}
	return false;
}

bool World::eatFruit(){
	if (player_->eatFruit(bricks_)) {
		score_ += 500;

		if(isSound_){
			soundController_->playEffect(ESounds::ES_EAT_FRUIT);
		}
		return true;
	}
	return false;
}

bool World::collidesWithLevel(PRectangle* rect) {
	return find_if(bricks_.begin(), bricks_.end(), [rect](Brick* brick){return brick->getBounds()->intersects(rect) && brick->getTextureName() > ECocos;}) != bricks_.end(); 
}

void World::startPointPlayer(){
	player_->setState(DEFENCE);
	player_->setPosition(new PRectangle(360,270,30,30));
	player_->setDirection(RIGHT);
}

void World::createSpirit(){
	for(auto spirit: spirits_) {
		spirit->setDirection(DOWN);
		spirit->setPositionPoint(spirit->getStartPoint());
		spirit->setCountStep(0);
	}
}

bool World::isVictory() {
	return countPoint_ > 0 ? false:true;
}

bool World::isGameOver() {
	return player_->getLife() > 0 ? false:true;
}

bool World::isFruit(ETexture textureName) {
	return textureName >= EBanana && textureName <= ECocos;
}

SpiritsVec World::getSpirits() const {
	return spirits_;
}

BricksVec World::getBricks() const {
	return bricks_;
}
