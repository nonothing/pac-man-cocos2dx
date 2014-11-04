#ifndef Spirit_H_
#define Spirit_H_

#include "Model\Point.h"
#include "Model\WorldObjectMove.h"
#include "Model\List.h"
#include "Model\Brick.h"
#include "Model\World.h"
#include "Model\Level.h"

using namespace std;
class World;
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
	Spirit(PPoint* position , string texture ,int width, int height, Level* level);
	virtual void ai(World* world){};
	virtual string left(){return NULL;}
	virtual string right(){return NULL;}
	virtual string down(){return NULL;}
	virtual string up(){return NULL;}
	void go(World* world);
	void move(World* world);
	void findDirection(World* world, PPoint* point, Spirit* spirit);
	int getCountStep();
	void setCountStep(int countStep);
	void setDefence(bool isDefence);
	PPoint* getStartPoint(){return START_POINT;}

private:
	int countStep;
	bool leftDefence;
	void refresh(World* world);
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
     void changeMap(Spirit* spirit);
     void inverseMap(List<Brick*>* bricks);
     void createMap(int width, int height);
     void potencialMap(PPoint* point, Spirit* spirit, List<Brick*>* bricks);
	 void clearMap();
     int ** getMap();

};
#endif /* Spirit_H_ */
