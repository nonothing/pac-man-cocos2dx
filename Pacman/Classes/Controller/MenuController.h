#ifndef MENU_CONTROLLER_H_
#define MENU_CONTROLLER_H_

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
class MenuController {

public:
	CC_SYNTHESIZE_READONLY(LabelTTF*, buttonPlay_, ButtonPlay);
	CC_SYNTHESIZE_READONLY(LabelTTF*, buttonLevel_, ButtonLevel);
	CC_SYNTHESIZE_READONLY(LabelTTF*, buttonSound_, ButtonSound);
	CC_SYNTHESIZE_READONLY(LabelTTF*, buttonExit_, ButtonExit);
	int selectMenuItem(int y, bool isTouch);
	void init();
};
#endif /* MENU_CONTROLLER_H_ */
