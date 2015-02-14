#ifndef Clyde_H_
#define Clyde_H_
#include "model/Spirit/Spirit.h"
#include "model/Point.h"

using namespace std;

class Clyde: public Spirit {

public:
	Clyde();
	Clyde(PPoint* point, Level* level);
	void ai(BricksVec bricks, Player* player = NULL, PPoint* point = NULL);
	void AIattack(Player* player, BricksVec bricks);
	ETexture left();
	ETexture right();
	ETexture down();
	ETexture up();

};
#endif /* Clyde_H_ */
