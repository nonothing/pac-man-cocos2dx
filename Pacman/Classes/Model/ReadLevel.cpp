#include "Model/ReadLevel.h"

ReadLevel::ReadLevel(){
	level_ = new Level();
}

Level* ReadLevel::getLevel() const{
	return level_;
}

void ReadLevel::readFile(std:: string fileName){
	BricksVec bricks;
	
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
			bricks.push_back(new Brick(new PPoint(x, y), EPoint,30,30));
			break;
		case 2:
			bricks.push_back(new Brick(new PPoint(x, y), EHorizontal,30,30));
			break;
		case 3:
			bricks.push_back(new Brick(new PPoint(x, y), EVertical,30,30));
			break;
		case 4:
			bricks.push_back(new Brick(new PPoint(x, y), EAngleLd,30,30));					            	
			break;
		case 5:
			bricks.push_back(new Brick(new PPoint(x, y), EAangleRd,30,30));
			break;
		case 6:
			bricks.push_back(new Brick(new PPoint(x, y), EAngleRv,30,30));
			break;
		case 7:
			bricks.push_back(new Brick(new PPoint(x, y), EAngleLv,30,30));
			break;
		case 8:
			bricks.push_back(new Brick(new PPoint(x, y), EArcUp,30,30));
			break;
		case 9:
			bricks.push_back(new Brick(new PPoint(x, y), EArcLeft,30,30));
			break;
		case 10:
			bricks.push_back(new Brick(new PPoint(x, y), EArcRight,30,30));
			break;
		case 11:
			bricks.push_back(new Brick(new PPoint(x, y), EArcDown,30,30));
			break;
		case 12:
			bricks.push_back(new Brick(new PPoint(x, y), EArc2Up,30,30));
			break;
		case 13:
			bricks.push_back(new Brick(new PPoint(x, y), EArc2Right,30,30));
			break;
		case 14:
			bricks.push_back(new Brick(new PPoint(x, y), EArc2Left,30,30));
			break;
		case 15:
			bricks.push_back(new Brick(new PPoint(x, y), EArc2Down,30,30));
			break;
		case 16:
			bricks.push_back(new Brick(new PPoint(x, y), EBonus,30,30));
			break;
		case 90:
			level_->setPointBlinky(new PPoint(x, y));
			bricks.push_back(new Brick(new PPoint(x, y), ENone,30,30));
			break;
		case 91:
			level_->setPointPinky(new PPoint(x, y));
			bricks.push_back(new Brick(new PPoint(x, y), ENone,30,30));
			break;
		case 92:
			level_->setPointClyde(new PPoint(x, y));
			bricks.push_back(new Brick(new PPoint(x, y), ENone,30,30));
			break;
		case 93:
			level_->setPointInky(new PPoint(x, y));
			bricks.push_back(new Brick(new PPoint(x, y), ENone,30,30));
			break;
		case 99:
			bricks.push_back(new Brick(new PPoint(x, y), ENone,30,30));
			break;
		default:
			bricks.push_back(new Brick(new PPoint(x, y), EBackground,30,30));
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