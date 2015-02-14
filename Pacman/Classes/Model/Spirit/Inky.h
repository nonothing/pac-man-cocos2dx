#ifndef Inky_H_
#define Inky_H_

#include "Spirit.h"
#include "Model/Point.h"

using namespace std;
class Inky: public Spirit {

private:
	 static const  int Y = 1;
	 static const int X = 0;
	 PPoint* doubleVectorBetweenTwoPoints(PPoint* point1, PPoint* point2);
	 PPoint* findPathTwoStep(Player* player);
	 int aMatrix[3];
     int bMatrix[3][3];
	 int point[3];
	 Level* level_;
public:
	Inky();
	Inky(PPoint* point, Level* level);
	void ai(BricksVec bricks, Player* player = NULL, PPoint* point = NULL);
	ETexture left();
	ETexture right();
	ETexture down();
	ETexture up();

};

#endif /* Inky_H_ */
