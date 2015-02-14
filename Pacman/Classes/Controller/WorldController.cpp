#include "Controller/WorldController.h"
#include "View/LevelMenuScene.h"
#include "View/WorldScene.h"

#define MIN_OFFSET 20
#define MAX_OFFSET 60

void WorldController::init(World* world, SoundController* soundController){

	soundController_ = soundController;
	seconds = 0;

	record = UserDefault::getInstance()->getIntegerForKey(LevelMenuScene::parseLevel(world->getCurrentLevel()).c_str(), 0);
	UserDefault::getInstance()->setIntegerForKey("LAST_LEVEL", world->getCurrentLevel());
	UserDefault::getInstance()->flush();
	this->world = world;
	labelRecord = LabelTTF::create("Record: ", FONT_EMULOGIC, 14);
    labelRecord->setPosition(Point(100, 436));
	labelRecord->setColor(Color3B::YELLOW);

	labelScore = LabelTTF::create("You: ", FONT_EMULOGIC , 14);
    labelScore->setPosition(Point(610, 436));
	labelScore->setColor(Color3B::YELLOW);
}

void WorldController::updateWorld(float dt){
	if(!isPause){
		for(int i=0; i < world->getSpirits().size(); i++){	
			if(world->getSpirits().at(i)->getState() == DEFENCE)
				world->getSpirits().at(i)->setDefence(isDefenceSpirit);
			world->getSpirits().at(i)->go(world->getBricks(), world->getPlayer(), world->getSpirits().at(0)->getPosition());
		}
	
		if(world->deadPlayer()) {
			onPause();
			respawn();
		}

		world->deadSpirit();
	
		if(world->isVictory()) {
			onPause();
			UserDefault::getInstance()->setIntegerForKey(LevelMenuScene::parseLevel(world->getCurrentLevel()).c_str(), record);
			UserDefault::getInstance()->setIntegerForKey(LevelMenuScene::parseLevel(world->getCurrentLevel() + 1).c_str(), 1);
			UserDefault::getInstance()->flush();
			Director::getInstance()->pushScene(WorldScene::create(LevelMenuScene::parseLevel(world->getCurrentLevel() + 1), world->getCurrentLevel() + 1, soundController_)->getScene());
			newWorld();
		}

		if(world->isGameOver()) {
			onPause();
			newWorld();
		}
		 
	}

}

void WorldController::newWorld() {
	respawn();
	world->getPlayer()->setLife(3);
	world->generationPoint();
	world->setScore(0);
	record = UserDefault::getInstance()->getIntegerForKey(LevelMenuScene::parseLevel(world->getCurrentLevel()).c_str(), 0);
}

void WorldController::respawn() {
	world->createSpirit();
	world->startPointPlayer();
	isPause = false;
}

 void WorldController::TouchMoved(int x, int y){
	 if (touchX > x && abs(x - touchX) > MIN_OFFSET && abs(y - touchY) < MAX_OFFSET)
		 setDirection(LEFT);
	 if (touchX < x && abs(x - touchX) > MIN_OFFSET && abs(y - touchY) < MAX_OFFSET)
		 setDirection(RIGHT);
	 if (touchY > y && abs(y - touchY) > MIN_OFFSET && abs(x - touchX) < MAX_OFFSET)
		 setDirection(DOWN);
	 if (touchY < y && abs(y - touchY) > MIN_OFFSET && abs(x - touchX) < MAX_OFFSET)
		 setDirection(UP);
}

 void WorldController::TouchEnded(int x, int y){
	 if (touchX > x && abs(y - touchY) < MAX_OFFSET)
		 setDirection(LEFT);
	 if (touchX < x && abs(y - touchY) < MAX_OFFSET)
		 setDirection(RIGHT);
	 if (touchY > y && abs(x - touchX) < MAX_OFFSET)
		 setDirection(DOWN);
	 if (touchY < y && abs(x - touchX) < MAX_OFFSET)
		 setDirection(UP);
}

void WorldController::updatePlayer(float dt){
	ostringstream convertScore;   
    convertScore << world->getScore();    
	labelScore->setString("You: " + convertScore.str() );

	if(world->getScore() > record){
		record = world->getScore();
	}
	ostringstream convertRecord;  
	convertRecord<<record;
	labelRecord->setString("Record: " + convertRecord.str());

	if (!isPause) {
		world->tryToPlayerGo(direction);
	}
}

void WorldController::timerTask(float dt){
	if(!isPause) {
		if(world->getDefenceSpirit()) {
			seconds++;
			isDefenceSpirit = seconds >= 8 && seconds % 2 == 0;

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
	if (!isPause) {
		for(auto spirit: world->getSpirits()) {
			if(spirit->getState() == DEAD) {
				spirit->go(world->getBricks());
			}
		}
	}
}

void WorldController::onPause(){
	isPause = !isPause;
}

void WorldController::generateFruit(float dt) {
	if (!isPause) {
		world->generationFruit();
	}
}