#ifndef Inky_H_
#define Inky_H_

#include "model/Spirit/Spirit.h"
#include "model/Point.h"
using namespace std;
class Inky: public Spirit {

private:
	 static const  int Y = 1;
	 static const int X = 0;
	 PPoint* doubleVectorBetweenTwoPoints(PPoint* point1, PPoint* point2);
	 PPoint* findPathTwoStep(World* world);
	 int aMatrix[3];
     int bMatrix[3][3];
	 int point[3];
public:
	Inky();
	Inky(PPoint* point, Level* level);
	void ai(World* world);
	string left();
	string right();
	string down();
	string up();

};

#endif /* Inky_H_ */
