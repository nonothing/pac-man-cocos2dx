#include "World.h"
#include "model/Spirit/Blinky.h"
#include "model/Spirit/Clyde.h"
#include "model/Spirit/Inky.h"
#include "model/Spirit/Pinky.h"
#include "Controller\SoundController.h"

World::World(Level* level, SoundController* soundController){
	isSound_ = CCUserDefault::sharedUserDefault()->getBoolForKey("SOUND", false);
	player_ = new Player(new PPoint(12, 9), EPacmanUpOpen, 30, 30);
	player_->setDirection(LEFT);
	spirits_ = new List<Spirit*>();
	spirits_->append(new Blinky(level->getPointBlinky(), level));
	spirits_->append(new Clyde(level->getPointClyde(), level));
	spirits_->append(new Inky(level->getPointInky(), level));
	spirits_->append(new Pinky(level->getPointPinky(), level));
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
	delete bricks_;
	delete spirits_;
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

int World::generationPoint(){
	int result=0;
	for(int i=0; i < bricks_->size(); i++){
		if(bricks_->get(i)->getTextureName() == EBackground){
			bricks_->get(i)->setTexture(EPoint);
			result++;
		}
	}
	countPoint_ += result;
	return result;
}

void World::generationFruit() {
	std::vector<int> emptyBrick;
	for(int i=0; i < bricks_->size(); i++){
		if(bricks_->get(i)->getTextureName() == EBackground){
			emptyBrick.push_back(i);
		}
		if(isFruit(bricks_->get(i)->getTextureName())) {
			bricks_->get(i)->setTexture(EBackground);
			return;
		}
	}
	if((int)emptyBrick.size() > bricks_->size() / 10) {
		int randomNumber = rand() % emptyBrick.size();
		int randomFruit = rand() % 6;
		ETexture textureName;

		switch (randomFruit) {
		case 0:   textureName = EBanana;		break;
		case 1:   textureName = EApple;		break;
		case 2:   textureName = EAppleRed;	break;
		case 3:   textureName = EVinograd;		break;
		case 4:   textureName = EOrange;		break;
		case 5:   textureName = ECocos;		break;
		default:  textureName = EBackground;	break;
		}

		bricks_->get(emptyBrick.at(randomNumber))->setTexture(textureName);
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


void World::defenceNPC(){
	for(int i=0; i < spirits_->size(); i++){
	            if (spirits_->get(i)->getState() == ATTACK) {
	            	spirits_->get(i)->setState(DEFENCE);
	            }
	        }
}

void World::attackNPC(){
	for(int i=0; i < spirits_->size(); i++){
		if (spirits_->get(i)->getState() == DEFENCE) {
			spirits_->get(i)->setState(ATTACK);
          }
      }
      player_->setState(DEFENCE);
}

bool World::deadSpirit(){
	for(int i=0; i < spirits_->size(); i++){
            if ((spirits_->get(i)->getBounds()->intersects(player_->getBounds()))) {
                if (player_->getState() == ATTACK && spirits_->get(i)->getState() != DEAD){
                    score_ += 1000;
                    spirits_->get(i)->setState(DEAD);
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
	for(int i=0; i < spirits_->size(); i++){
	            if ((spirits_->get(i)->getBounds()->intersects(player_->getBounds()))) {
	                if (spirits_->get(i)->getState() == ATTACK){
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
	 for(int i=0; i < bricks_->size(); i++){
            if (bricks_->get(i)->getBounds()->intersects(rect) && bricks_->get(i)->getTextureName() > ECocos)  {
                return true;
            }
        }
        return false;
    }

 int World::collidesWithRefresh(PRectangle* rect){
	 for(int i=0; i < bricks_->size(); i++){
	            if (bricks_->get(i)->getBounds()->intersects(rect) && bricks_->get(i)->getTextureName() == ENone) {
	                return ATTACK;
	            }
	        }
	        return DEAD;
 }

 void World::startPointPlayer(){
	 player_->setState(DEFENCE);
	 player_->setPosition(new PRectangle(360,270,30,30));
	 player_->setDirection(RIGHT);
	 
 }

 void World::createSpirit(){
	 for(int i=0; i < spirits_->size(); i++){
					spirits_->get(i)->setDirection(DOWN);
	 	            spirits_->get(i)->setPositionPoint(spirits_->get(i)->getStartPoint());
	 	            spirits_->get(i)->setCountStep(0);
	 }
 }

bool World::isVictory() {
        return countPoint_ > 0 ? false:true;
}
    
bool World::isGameOver() {
	return player_->getLife() > 0? false:true;
}

bool World::isFruit(ETexture textureName) {
	return textureName >= EBanana && textureName <= ECocos;
}

List<Spirit*>* World::getSpirits() const {
	return spirits_;
}

List<Brick*>* World::getBricks() const {
	return bricks_;
}
