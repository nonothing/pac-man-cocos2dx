#ifndef LEVEL_MENU_H_
#define LEVEL_MENU_H_

#include "Model\Rectangle.h"
#include "Model\Point.h"
#include "Model\WorldObject.h"

using namespace std;

class LevelMenu :public WorldObject{

	int level;
	int score;
	int spX;
	int offsetX;

public:
	LevelMenu(){};
	LevelMenu(PPoint* position, string texture,int level, int score, int width, int height);
	int getLevel() { return level; }
	bool getLock(){ return (score == 0) ? true : false; }
	int getRecord(){ return score; }
	void setScore(int record){ score = record; }
	PRectangle* getRect();
	void setOffsetX(int x);

};


#endif /* LEVEL_MENU_H_ */
