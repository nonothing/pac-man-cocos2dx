#ifndef LEVEL_MENU_H_
#define LEVEL_MENU_H_

#include "Model/Rectangle.h"
#include "Model/Point.h"
#include "Model/WorldObject.h"

using namespace std;

class LevelMenu :public WorldObject{

private:
	int spX_;
	int offsetX_;
	LabelTTF* label_;
	string numberLevel_;
	void createLabel();
public:
	LevelMenu(){};
	LevelMenu(PPoint* position, ETexture texture,int level, int score, int width, int height);

	CC_SYNTHESIZE(int, level_, Level);
	CC_SYNTHESIZE(int, score_, Score);
	CC_SYNTHESIZE(string, name_, Name);

	bool getLock();
	PRectangle* getRect();
	void setOffsetX(int x);
	LabelTTF* getLabel();
};


#endif /* LEVEL_MENU_H_ */
