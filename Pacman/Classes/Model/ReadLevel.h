#ifndef __READ_LEVEL_H__
#define __READ_LEVEL_H__

#include <fstream>
#include "cocos2d.h"
#include "Model/Level.h"

using namespace std;
using namespace cocos2d;
USING_NS_CC;

class ReadLevel {
private:
	Level* level_;

public:
	ReadLevel();
	Level* getLevel() const;
	void readFile(std:: string fileName);

};

#endif // __READ_LEVEL_H__