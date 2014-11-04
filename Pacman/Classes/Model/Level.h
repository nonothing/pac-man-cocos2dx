#ifndef Level_H_
#define Level_H_

#include "Model\Brick.h"
#include "Model\List.h"

class Level{
public:
	  List<Brick*>* bricks;
	  PPoint* pointBlinky;
	  PPoint* pointInky;
	  PPoint* pointPinky;
	  PPoint* pointClyde;
	  int _width;
	  int _height;


	  ~Level(){
		  delete bricks;
		  delete pointBlinky;
		  delete pointInky;
		  delete pointPinky;
		  delete pointClyde;
	  }
};
#endif /* Level_H_ */
