#include "Controller\MenuController.h"
void MenuController::init(){
	buttonPlay = LabelTTF::create("Play", "fonts/emulogic.ttf", 26);
	buttonPlay->setColor(Color3B::YELLOW);
	buttonPlay->setPosition(Point(300, 300));

	buttonLevel = LabelTTF::create("Select level", "fonts/emulogic.ttf", 26);
	buttonLevel->setColor(Color3B::GRAY);
	buttonLevel->setPosition(Point(402, 250));

	buttonSound = LabelTTF::create("sound on", "fonts/emulogic.ttf", 26);
	buttonSound->setColor(Color3B::YELLOW);
	buttonSound->setPosition(Point(350, 200));
	if(!isSound){
		buttonSound->setString("Sound off");
		buttonSound->setPosition(Point(363, 200));
	} 

	buttonExit = LabelTTF::create("exit", "fonts/emulogic.ttf", 26);
	buttonExit->setColor(Color3B::YELLOW);
	buttonExit->setPosition(Point(300, 150));

}
int MenuController::selectMenuItem(int y, bool isTouch){
	int item = 0;
	
	if(y >= 130 && y < 180){
		buttonExit->setColor(Color3B::RED);
		item = 4;
	} else {
		buttonExit->setColor(Color3B::YELLOW);
	}
	if(y >= 180 && y < 230){
		item = 3;
		buttonSound->setColor(Color3B::RED);
	} else {
		buttonSound->setColor(Color3B::YELLOW);
	}
	/*//TODO 
	if(y >= 230 && y < 280){
		item = 2;
		buttonLevel->setColor(Color3B::RED);
	} else {
		buttonLevel->setColor(Color3B::YELLOW);
	}
	*/
	if(y >= 280 && y < 330){
		item = 1;
		buttonPlay->setColor(Color3B::RED);
	} else {
		buttonPlay->setColor(Color3B::YELLOW);
	}

	if(!isTouch){
		return item;
	} else {
		return 0;
	}
}