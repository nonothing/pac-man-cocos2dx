#include "Controller/MenuController.h"
#define FONT_EMULOGIC "fonts/emulogic.ttf"
#define FONT_SIZE   26

void MenuController::init(){
	buttonPlay_ = LabelTTF::create("Play", FONT_EMULOGIC, FONT_SIZE);
	buttonPlay_->setColor(Color3B::YELLOW);
	buttonPlay_->setPosition(Point(300, 300));

	buttonLevel_ = LabelTTF::create("Select level", FONT_EMULOGIC, FONT_SIZE);
	buttonLevel_->setColor(Color3B::YELLOW);
	buttonLevel_->setPosition(Point(402, 250));

	buttonSound_ = LabelTTF::create("sound on", FONT_EMULOGIC, FONT_SIZE);
	buttonSound_->setColor(Color3B::YELLOW);
	buttonSound_->setPosition(Point(350, 200));
	if(!UserDefault::getInstance()->getBoolForKey("SOUND", false)){
		buttonSound_->setString("Sound off");
		buttonSound_->setPosition(Point(363, 200));
	} 

	buttonExit_ = LabelTTF::create("exit", FONT_EMULOGIC, FONT_SIZE);
	buttonExit_->setColor(Color3B::YELLOW);
	buttonExit_->setPosition(Point(300, 150));

}

int MenuController::selectMenuItem(int y, bool isTouch){
	int item = 0;
	
	if(y >= 130 && y < 180){
		buttonExit_->setColor(Color3B::RED);
		item = 4;
	} else {
		buttonExit_->setColor(Color3B::YELLOW);
	}
	if(y >= 180 && y < 230){
		item = 3;
		buttonSound_->setColor(Color3B::RED);
	} else {
		buttonSound_->setColor(Color3B::YELLOW);
	}
	if(y >= 230 && y < 280){
		item = 2;
		buttonLevel_->setColor(Color3B::RED);
	} else {
		buttonLevel_->setColor(Color3B::YELLOW);
	}
	if(y >= 280 && y < 330){
		item = 1;
		buttonPlay_->setColor(Color3B::RED);
	} else {
		buttonPlay_->setColor(Color3B::YELLOW);
	}

	if(!isTouch){
		return item;
	} else {
		return 0;
	}
}