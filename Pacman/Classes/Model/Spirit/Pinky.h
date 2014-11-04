#ifndef Pinky_H_
#define Pinky_H_

#include "model/Spirit/Spirit.h"
#include "model/Point.h"

class Pinky: public Spirit {

private:
	PPoint* findPathFourStep(World* world);
public:
	Pinky();
	Pinky(PPoint* point, Level* level);
	void ai(World* world);
	string left();
	string right();
	string down();
	string up();

};

#endif /* Pinky_H_ */
