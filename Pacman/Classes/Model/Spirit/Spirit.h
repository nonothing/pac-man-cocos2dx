#ifndef Spirit_H_
#define Spirit_H_

#include "Model/Point.h"
#include "Model/WorldObjectMove.h"
#include "Model/Brick.h"
#include "Model/Player.h"
#include "Model/Level.h"

using namespace std;

class Spirit: public WorldObjectMove {
protected:
	PPoint* START_POINT;
	PPoint* DEFENCE_POINT;

public:
	Spirit();
	~Spirit(){
		for (int i = 0; i < width_; i++)
		  delete map[i];
		delete map;
	};
	Spirit(PPoint* position , ETexture texture ,int width, int height, Level* level);
	virtual void ai(BricksVec bricks, Player* player, PPoint* point) = 0;
	virtual ETexture left() = 0;
	virtual ETexture right() = 0;
	virtual ETexture down() = 0;
	virtual ETexture up() = 0;
	void go(BricksVec bricks, Player* player = NULL, PPoint* point = NULL);
	void move(BricksVec bricks);
	void findDirection(BricksVec bricks, PPoint* point);
	void changeDirection(int dir);
	int getCountStep();
	void setCountStep(int countStep);
	void setDefence(bool isDefence);
	PPoint* getStartPoint(){return START_POINT;}
	void moveTo(int** map, Direction dir);
	int getHorizontalOffset(Direction dir);
	int getVerticalOffset(Direction dir);

private:
	Level* level_;
	int countStep_;
	bool leftDefence_;
	int countCollision_;
	void refresh(BricksVec bricks);

	int collidesWithRefresh(PRectangle* rect, BricksVec bricks);
	bool collidesWithLevel(PRectangle* rect, BricksVec bricks);

	void onLoadImageAttack();
	void onLoadImageDead();
	void onLoadImageDefence(bool isWhite);
	void onLoadImage();
protected:
	static const int WALL = 200;
	int **map;
	int step;
	int width_;
	int height_;
	void changeMap();
	void inverseMap(BricksVec bricks);
	void createMap(int width, int height);
	void potencialMap(PPoint* point, BricksVec bricks);
	void clearMap();
	int ** getMap();

};

typedef vector<Spirit*>  SpiritsVec;
#endif /* Spirit_H_ */
