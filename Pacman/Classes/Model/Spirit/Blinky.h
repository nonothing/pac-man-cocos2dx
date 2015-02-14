#ifndef Blinky_H_
#define Blinky_H_

#include "model/Spirit/Spirit.h"
#include "model/Point.h"
using namespace std;

class Blinky: public Spirit {

public:
	Blinky();
	Blinky(PPoint* point, Level* level);
	void ai(BricksVec bricks, Player* player = NULL, PPoint* point = NULL);
	ETexture left();
	ETexture right();
	ETexture down();
	ETexture up();

};

#endif /* Blinky_H_ */
