#include "World.h"
#include "model/Spirit/Blinky.h"
#include "model/Spirit/Clyde.h"
#include "model/Spirit/Inky.h"
#include "model/Spirit/Pinky.h"
#include "SimpleAudioEngine.h"


World::World(Level* level){
	isSound_ = CCUserDefault::sharedUserDefault()->getBoolForKey("SOUND", false);
	player_ = new Player(new PPoint(12, 9),"pacmanUpOpen",30,30);
	player_->setDirection(LEFT);
	spirits = new List<Spirit*>();
	spirits->append(new Blinky(level->pointBlinky, level));
	spirits->append(new Clyde(level->pointClyde, level));
	spirits->append(new Inky(level->pointInky, level));
	spirits->append(new Pinky(level->pointPinky, level));
	bricks = level->bricks;
	score_ = 0;
	countPoint_ = generationPoint();
	leftSpirit=3;
	if(isSound_){
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/pacman_coinin.wav");
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/eatfruit.wav");	
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/eatspirit.wav");	
	}
}

World::~World(){
	delete player_;
	delete bricks;
	delete spirits;
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
}

Player* World::getPlayer(){
	return player_;
}

int World::generationPoint(){
	int result=0;
	for(int i=0; i < bricks->size(); i++){
		if(bricks->get(i)->getTextureName() == "background"){
			bricks->get(i)->setTexture("point");
			result++;
		}
	}
	countPoint_ += result;
	return result;
}

bool World::eatPoint(){
	  if (player_->eatPoint(bricks)) {
		  	  	  countPoint_--;
		  	  	  score_ += 50;
				  if(isSound_){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/pacman_coinin.wav");
				  }
	            return true;
	        }
	        return false;
}

bool World::eatBonus(){
        if (player_->eatBonus(bricks)) {
            score_ += 500;
            defenceNPC();
			isDefenceSpirit_ = true;
			if(isSound_){
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/eatfruit.wav");	
			}
            return true;
        }
        return false;
    }


void World::defenceNPC(){
	for(int i=0; i < spirits->size(); i++){
	            if (spirits->get(i)->getState() == ATTACK) {
	            	spirits->get(i)->setState(DEFENCE);
	            }
	        }
}

void World::attackNPC(){
	for(int i=0; i < spirits->size(); i++){
		if (spirits->get(i)->getState() == DEFENCE) {
			spirits->get(i)->setState(ATTACK);
          }
      }
      player_->setState(DEFENCE);
}

bool World::deadSpirit(){
	for(int i=0; i < spirits->size(); i++){
            if ((spirits->get(i)->getBounds()->intersects(player_->getBounds()))) {
                if (player_->getState() == ATTACK && spirits->get(i)->getState() != DEAD){
                    score_ += 1000;
                    spirits->get(i)->setState(DEAD);
					if(isSound_){
						CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/eatspirit.wav");	
					}
                    return true;
                }
            }
        }
        return false;
}

bool World::deadPlayer(){
	for(int i=0; i < spirits->size(); i++){
	            if ((spirits->get(i)->getBounds()->intersects(player_->getBounds()))) {
	                if (spirits->get(i)->getState() == ATTACK){
	                    player_->setState(DEAD);
	                    player_->setLife(player_->getLife() - 1);
	                    return true;
	                }
	            }
	        }
	        return false;
}

bool World::eatFruit(){
//        if(fruit->getBounds()->intersects(player->getBounds()) && fruit->getTexture()!= none){
//            fruit->setTexture(Texture->none);
//            score += 500;
//            return true;
//        }
            return false;
    }

 bool World::collidesWithLevel(PRectangle* rect) {
	 for(int i=0; i < bricks->size(); i++){
            if (bricks->get(i)->getBounds()->intersects(rect)
            		&& bricks->get(i)->getTextureName() != "background"
            		&& bricks->get(i)->getTextureName() != "point"
					&& bricks->get(i)->getTextureName() != "bonus"
                    && bricks->get(i)->getTextureName() != "none"
                    ) {
                return true;
            }
        }
        return false;
    }

 int World::collidesWithRefresh(PRectangle* rect){
	 for(int i=0; i < bricks->size(); i++){
	            if (bricks->get(i)->getBounds()->intersects(rect) && bricks->get(i)->getTextureName() == "none") {
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
	 for(int i=0; i < spirits->size(); i++){
					spirits->get(i)->setDirection(DOWN);
	 	            spirits->get(i)->setPositionPoint(spirits->get(i)->getStartPoint());
	 	            spirits->get(i)->setCountStep(0);
	 }
 }

bool World::isVictory() {
        return countPoint_ > 0 ? false:true;
}
    
bool World::isGameOver() {
	return player_->getLife() > 0? false:true;
}