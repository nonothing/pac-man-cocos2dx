#include "Controller\WorldController.h"

void WorldController::init(World* world){
	seconds =0;
	this->world = world;
	labelRecord = LabelTTF::create("Record: ", FONT_EMULOGIC, 14);
    labelRecord->setPosition(Point(100,436));
	labelRecord->setColor(Color3B::YELLOW);

	labelScore = LabelTTF::create("You: ", FONT_EMULOGIC , 14);
    labelScore->setPosition(Point(610,436));
	labelScore->setColor(Color3B::YELLOW);
}

void WorldController::updateWorld(float dt){
	if(!isPause){
		for(int i=0; i < world->spirits->size(); i++){	
			if(world->spirits->get(i)->getState() == DEFENCE)
				world->spirits->get(i)->setDefence(isDefenceSpirit);
			world->spirits->get(i)->go(world);
		}
		world->deadPlayer();
		world->deadSpirit();
		 if (world->isGameOver() || world->isVictory()) {
            onPause();
        }

		if (world->getPlayer()->getState() == DEAD || world->isVictory()) {
			world->createSpirit();
			world->startPointPlayer();
			world->getPlayer()->setLife(3);
			world->generationPoint();
			world->setScore(0);
			isPause = false;
			
        }
	}

}

 void WorldController::TouchMoved(int x, int y){
	 if (touchX > x && abs(x - touchX) > 20 && abs(y - touchY) < 60)
			setDirection(LEFT);
		if (touchX < x && abs(x - touchX) > 20 && abs(y - touchY) < 60)
			setDirection(RIGHT);
		if (touchY > y && abs(y - touchY) > 20 && abs(x - touchX) < 60)
			setDirection(DOWN);
		if (touchY < y && abs(y - touchY) > 20 && abs(x - touchX) < 60)
			setDirection(UP);
}

 void WorldController::TouchEnded(int x, int y){

	 if (touchX > x && abs(y - touchY) < 60)
			setDirection(LEFT);
		if (touchX < x && abs(y - touchY) < 60)
			setDirection(RIGHT);
		if (touchY > y && abs(x - touchX) < 60)
			setDirection(DOWN);
		if (touchY < y && abs(x - touchX) < 60)
			setDirection(UP);
}

void WorldController::updatePlayer(float dt){
ostringstream convertScore;   
    convertScore << world->getScore();    
	labelScore->setString("You: " + convertScore.str() );

	if(world->getScore() > record){
		record = world->getScore();
		CCUserDefault::sharedUserDefault()->setIntegerForKey("RECORD", world->getScore());
		CCUserDefault::sharedUserDefault()->flush();
	}
	ostringstream convertRecord;  
	convertRecord<<record;
	labelRecord->setString("Record: " + convertRecord.str());

	if(!isPause){
		world->tryToPlayerGo(direction);
	}
}

void WorldController::timerTask(float dt){
	if(!isPause){
		if(world->isDefence()){
			seconds++;
                    if (seconds >= 8 && seconds % 2 == 0) {
                        isDefenceSpirit = true;
                    } else {
                        isDefenceSpirit = false;
                    }

                    if (seconds == 12) {
                        world->attackNPC();
						isDefenceSpirit = false;
                        seconds = 0;
						world->setDefenceSpirit(false);
                    }
		}
			
	}
}

void WorldController::speedTask(float dt){
	if(!isPause){
		for(int i=0; i < world->spirits->size(); i++){	
			if(world->spirits->get(i)->getState() == DEAD)
				world->spirits->get(i)->go(world);
		}
	}
}

void WorldController::onPause(){
	if(isPause){
		isPause = false;
	} else {
		isPause = true;
	}
}