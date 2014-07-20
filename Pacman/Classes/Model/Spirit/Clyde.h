#ifndef Clyde_H_
#define Clyde_H_
#include "model/Spirit/Spirit.h"
#include "model/Point.h"

using namespace std;

class Clyde: public Spirit {

public:
	Clyde();
	Clyde(PPoint* point);
	void ai(World* world);
	void AIattack(World* world);
	string left();
	string right();
	string down();
	string up();

};
#endif /* Clyde_H_ */
