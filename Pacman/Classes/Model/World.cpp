#include "World.h"
#include "model/Spirit/Blinky.h"
#include "model/Spirit/Clyde.h"
#include "model/Spirit/Inky.h"
#include "model/Spirit/Pinky.h"
#include "SimpleAudioEngine.h"


World::World(Level* level){
	isSound = CCUserDefault::sharedUserDefault()->getBoolForKey("SOUND", false);
	player = new Player(new PPoint(12, 9),"pacmanUpOpen",30,30);
	player->setDirection(LEFT);
	spirits = new List<Spirit*>();
	spirits->append(new Blinky(level->pointBlinky));
	spirits->append(new Clyde(level->pointClyde));
	spirits->append(new Inky(level->pointInky));
	spirits->append(new Pinky(level->pointPinky));
	bricks = level->bricks;
	score = 0;
	countPoint = generationPoint();
	leftSpirit=3;
	if(isSound){
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/pacman_coinin.wav");
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/eatfruit.wav");	
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/eatspirit.wav");	
	}
}

World::~World(){
	delete player;
	delete bricks;
	delete spirits;
}

void World::tryToPlayerGo(int direction){
	player->onMove(direction);
	
	if(!collidesWithLevel(player->getBounds())){
		player->setDirection(direction);
	}
	player->onMove(player->getDirection());
	if(!collidesWithLevel(player->getBounds())){
		player->setPosition(player->getBounds());
		player->animate();
		player->getTexture()->setPosition(player->getPosition()->getX()  + 15, player->getPosition()->getY() + 15);
	}
	eatBonus();
	eatPoint();
}

Player* World::getPlayer(){
	return player;
}

int World::generationPoint(){
	int result=0;
	for(int i=0; i < bricks->size()-1; i++){
		if(bricks->get(i)->getTextureName() == "background"){
			bricks->get(i)->setTexture("point");
			result++;
		
		}
	}
	countPoint += result;
	return result;
}

bool World::eatPoint(){
	  if (player->eatPoint(bricks)) {
		  	  	  countPoint--;
		  	  	  score += 50;
				  if(isSound){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/pacman_coinin.wav");
				  }
	            return true;
	        }
	        return false;
}

bool World::eatBonus(){
        if (player->eatBonus(bricks)) {
            score += 500;
            defenceNPC();
			isDefenceSpirit = true;
			if(isSound){
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
      player->setState(DEFENCE);
}

bool World::deadSpirit(){
	for(int i=0; i < spirits->size(); i++){
            if ((spirits->get(i)->getBounds()->intersects(player->getBounds()))) {
                if (player->getState() == ATTACK && spirits->get(i)->getState() != DEAD){
                    score += 1000;
                    spirits->get(i)->setState(DEAD);
					if(isSound){
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
	            if ((spirits->get(i)->getBounds()->intersects(player->getBounds()))) {
	                if (spirits->get(i)->getState() == ATTACK){
	                    player->setState(DEAD);
	                    player->setLife(player->getLife() - 1);
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
            		&& bricks->get(i)->getTextureName() !="background"
            		&& bricks->get(i)->getTextureName() !="point"
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
	 player->setState(DEFENCE);
	 player->setPosition(new PRectangle(300,270,30,30));
	 player->setDirection(RIGHT);
	 
 }

 void World::createSpirit(){
	 for(int i=0; i < spirits->size(); i++){
					spirits->get(i)->setDirection(DOWN);
	 	            spirits->get(i)->setPositionPoint(spirits->get(i)->getStartPoint());
	 	            spirits->get(i)->setCountStep(0);
	 }
 }

bool World::isVictory(){
	if(countPoint <= 0 )
		return true;
            
        return false;
}
    
bool World::isGameOver(){
	if(player->getLife() <= 0 )
		return true;
        
	return false;
}