#ifndef MENU_CONTROLLER_H_
#define MENU_CONTROLLER_H_

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
class MenuController{

	LabelTTF* buttonPlay;
	LabelTTF* buttonLevel;
	LabelTTF* buttonSound;
	LabelTTF* buttonExit;
	bool isSound;

public:
	int selectMenuItem(int y, bool isTouch);
	void init();
	LabelTTF* getButtonPlay(){return buttonPlay;}
	LabelTTF* getButtonLevel(){return buttonLevel;}
	LabelTTF* getButtonSound(){return buttonSound;}
	LabelTTF* getButtonExit(){return buttonExit;}
};
#endif /* MENU_CONTROLLER_H_ */
