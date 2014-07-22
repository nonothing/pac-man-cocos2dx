#ifndef WorldObject_H_
#define WorldObject_H_
#include "model/Point.h"
#include "model/Rectangle.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class WorldObject {
private:
	string textureName;
	int width;
	int height;

protected:
     PPoint* position;
     PRectangle* bounds;
	 Sprite* sprite;

public:
    WorldObject(){};
    virtual ~WorldObject();
    WorldObject(PPoint* point, string texture, int width, int height);
    int getWidth();
    int getHeight();
    void setWidth(int width);
    void setHeight(int height);
    PPoint* getPosition();
    void setPositionPoint(PPoint* point);
    Sprite* getTexture() ;
	string getTextureName();
    PRectangle* getBounds();
	int getSpriteX(){ return sprite->getPositionX(); }
	int getSpriteY(){ return sprite->getPositionY(); }
    void setBounds(int x, int y, int width, int height);
    void setTexture(string texture);
    virtual void animate() {
        // do nothing
    }
    int inverse(int count);
};
#endif /* WorldObject_H_ */
