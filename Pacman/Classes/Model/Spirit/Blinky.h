#ifndef Blinky_H_
#define Blinky_H_

#include "model/Spirit/Spirit.h"
#include "model/Point.h"
using namespace std;

class Blinky: public Spirit {

public:
	Blinky();
	Blinky(PPoint* point);
	void ai(World* world);
	string left();
	string right();
	string down();
	string up();

};

#endif /* Blinky_H_ */
