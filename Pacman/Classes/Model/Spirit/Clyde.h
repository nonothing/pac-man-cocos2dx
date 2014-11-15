#ifndef Clyde_H_
#define Clyde_H_
#include "model/Spirit/Spirit.h"
#include "model/Point.h"

using namespace std;

class Clyde: public Spirit {

public:
	Clyde();
	Clyde(PPoint* point, Level* level);
	void ai(World* world);
	void AIattack(World* world);
	ETexture left();
	ETexture right();
	ETexture down();
	ETexture up();

};
#endif /* Clyde_H_ */
