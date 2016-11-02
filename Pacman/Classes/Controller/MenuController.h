#ifndef MENU_CONTROLLER_H_
#define MENU_CONTROLLER_H_

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "ui/UIText.h"

USING_NS_CC;
class MenuController {

public:
    CC_SYNTHESIZE_READONLY(ui::Text*, buttonPlay_, ButtonPlay);
	CC_SYNTHESIZE_READONLY(ui::Text*, buttonLevel_, ButtonLevel);
	CC_SYNTHESIZE_READONLY(ui::Text*, buttonSound_, ButtonSound);
	CC_SYNTHESIZE_READONLY(ui::Text*, buttonExit_, ButtonExit);
	int selectMenuItem(int y, bool isTouch);
	void init();
};
#endif /* MENU_CONTROLLER_H_ */
