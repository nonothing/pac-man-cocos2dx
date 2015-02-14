#ifndef Pinky_H_
#define Pinky_H_

#include "model/Spirit/Spirit.h"
#include "model/Point.h"

class Pinky: public Spirit {

private:
	PPoint* findPathFourStep(Player* player);
	Level* level_;
public:
	Pinky();
	Pinky(PPoint* point, Level* level);
	void ai(BricksVec bricks, Player* player = NULL, PPoint* point = NULL);
	ETexture left();
	ETexture right();
	ETexture down();
	ETexture up();

};

#endif /* Pinky_H_ */
