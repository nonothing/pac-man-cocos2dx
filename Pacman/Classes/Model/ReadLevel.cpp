#include "Model/ReadLevel.h"

ReadLevel::ReadLevel(){
	level_ = new Level();
}

Level* ReadLevel::getLevel() const{
	return level_;
}

void ReadLevel::readFile(std:: string fileName){
	List<Brick*>* bricks = new List<Brick*>();
	
	string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName.c_str());
	ssize_t fileSize = 0;
	unsigned char * fileContents = CCFileUtils::sharedFileUtils( ) -> getFileData( fullPath.c_str() , "r", &fileSize );
	stringstream strValue;
	strValue<<fileContents;

	int maxW = 0;
	strValue>>maxW;
	int number;
	int x =0,y =0;
	while(strValue>>number){

		switch (number) {
		case 1:
			bricks->append(new Brick(new PPoint(x, y), "point",30,30));
			break;
		case 2:
			bricks->append(new Brick(new PPoint(x, y), "horizontal",30,30));
			break;
		case 3:
			bricks->append(new Brick(new PPoint(x, y), "vertical",30,30));
			break;
		case 4:
			bricks->append(new Brick(new PPoint(x, y), "angle_ld",30,30));					            	
			break;
		case 5:
			bricks->append(new Brick(new PPoint(x, y), "angle_rd",30,30));
			break;
		case 6:
			bricks->append(new Brick(new PPoint(x, y), "angle_rv",30,30));
			break;
		case 7:
			bricks->append(new Brick(new PPoint(x, y), "angle_lv",30,30));
			break;
		case 8:
			bricks->append(new Brick(new PPoint(x, y), "arc_up",30,30));
			break;
		case 9:
			bricks->append(new Brick(new PPoint(x, y), "arc_left",30,30));
			break;
		case 10:
			bricks->append(new Brick(new PPoint(x, y), "arc_right",30,30));
			break;
		case 11:
			bricks->append(new Brick(new PPoint(x, y), "arc_down",30,30));
			break;
		case 12:
			bricks->append(new Brick(new PPoint(x, y), "arc2_up",30,30));
			break;
		case 13:
			bricks->append(new Brick(new PPoint(x, y), "arc2_right",30,30));
			break;
		case 14:
			bricks->append(new Brick(new PPoint(x, y), "arc2_left",30,30));
			break;
		case 15:
			bricks->append(new Brick(new PPoint(x, y), "arc2_down",30,30));
			break;
		case 16:
			bricks->append(new Brick(new PPoint(x, y), "bonus",30,30));
			break;
		case 90:
			level_->setPointBlinky(new PPoint(x, y));
			bricks->append(new Brick(new PPoint(x, y), "none",30,30));
			break;
		case 91:
			level_->setPointPinky(new PPoint(x, y));
			bricks->append(new Brick(new PPoint(x, y), "none",30,30));
			break;
		case 92:
			level_->setPointClyde(new PPoint(x, y));
			bricks->append(new Brick(new PPoint(x, y), "none",30,30));
			break;
		case 93:
			level_->setPointInky(new PPoint(x, y));
			bricks->append(new Brick(new PPoint(x, y), "none",30,30));
			break;
		case 99:
			bricks->append(new Brick(new PPoint(x, y), "none",30,30));
			break;
		default:
			bricks->append(new Brick(new PPoint(x, y), "background",30,30));
			break;
		}

		x++;
		if(x == maxW){
			x = 0;
			y++;
		}
	}
	level_->setBricks(bricks);
	level_->setWidth(maxW);
	level_->setHeight(y);
}