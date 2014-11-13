#ifndef Level_H_
#define Level_H_

#include "Model\Brick.h"
#include "Model\List.h"

class Level {

private:
	PPoint* pointBlinky_;
	PPoint* pointInky_;
	PPoint* pointPinky_;
	PPoint* pointClyde_;
	List<Brick*>* bricks_;

public:
	  
	CC_SYNTHESIZE(int, width_, Width);
	CC_SYNTHESIZE(int, height_, Height);

	List<Brick*>* getBricks() const;
	void setBricks(List<Brick*>* bricks);
	  

	void setPointBlinky(PPoint* point);
	PPoint* getPointBlinky() const;

	void setPointInky(PPoint* point);
	PPoint* getPointInky() const;

	void setPointPinky(PPoint* point);
	PPoint* getPointPinky() const;

	void setPointClyde(PPoint* point);
	PPoint* getPointClyde() const;


	~Level(){
		delete bricks_;
		delete pointBlinky_;
		delete pointInky_;
		delete pointPinky_;
		delete pointClyde_;
	}
};
#endif /* Level_H_ */
