#ifndef __READ_LEVEL_H__
#define __READ_LEVEL_H__

#include <fstream>
#include "cocos2d.h"
#include "Model\Level.h"

using namespace std;
using namespace cocos2d;
USING_NS_CC;

class ReadLevel 
{
	
public:
    Level* level;
	ReadLevel(){
		level = new Level();
	}

	void readFile(std:: string fileName, int map[][15]){
		List<Brick*>* bricks = new List<Brick*>();
     int maxR = 25;
	string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName.c_str());
	ssize_t fileSize = 0;
  	unsigned char * fileContents = CCFileUtils::sharedFileUtils( ) -> getFileData( fullPath.c_str() , "r", &fileSize );
	stringstream strValue;
	strValue<<fileContents;
	int number;
	int x =0,y =0;
	while(strValue>>number){
		map[x][y] = number;

		switch (map[x][y]) {
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
					            	level->pointBlinky = new PPoint(x, y);
					            	bricks->append(new Brick(new PPoint(x, y), "none",30,30));
					                break;
					            case 91:
					            	level->pointPinky = new PPoint(x, y);
					            	bricks->append(new Brick(new PPoint(x, y), "none",30,30));
					                break;
					            case 92:
					            	level->pointClyde = new PPoint(x, y);
					            	bricks->append(new Brick(new PPoint(x, y), "none",30,30));
					                break;
					            case 93:
					            	level->pointInky = new PPoint(x, y);
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
		if(x == maxR){
			x = 0;
			y++;
		}
	}
	level->bricks = bricks;
   }

};

#endif // __READ_LEVEL_H__