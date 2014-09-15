#ifndef WorldObject_H_
#define WorldObject_H_
#include "model/Point.h"
#include "model/Rectangle.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class WorldObject {
private:
	string textureName_;
	int width_;
	int height_;

protected:
     PPoint* position_;
     PRectangle* bounds_;
	 Sprite* sprite_;

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
	int getSpriteX(){ return sprite_->getPositionX(); }
	int getSpriteY(){ return sprite_->getPositionY(); }
    void setBounds(int x, int y, int width, int height);
    void setTexture(string texture);
    virtual void animate() {
        // do nothing
    }
    int inverse(int count);
};
#endif /* WorldObject_H_ */
