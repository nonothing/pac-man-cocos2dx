#include "Model\WorldObject.h"
#include "View\WorldScene.h"

using namespace std;

    WorldObject::WorldObject(PPoint* point, string texture, int width, int height) {
    	this->width = width;
    	this->height = height;
        position = new PPoint(point->getX(), point->getY(), width, height);
        bounds = new PRectangle(position->getX(), position->getY(), width, height);
		this->textureName = texture;
        this->sprite = Sprite::create(texture + ".png");
		this->sprite->setPosition(point->getX() * 30 + 15, point->getY() * 30 + 15);
    }

     WorldObject::~WorldObject(){
    	delete position;
    	delete bounds;
    }

    int WorldObject::getWidth() {
        return width;
    }
    int WorldObject::getHeight() {
        return height;
    }

    void WorldObject::setWidth(int width){
    	this->width = width;
    }
    void WorldObject::setHeight(int height){
    	this->height = height;
    }

    PPoint* WorldObject::getPosition() {
        return position;
    }

    Sprite* WorldObject::getTexture() {
        return sprite;
    }

	string WorldObject::getTextureName() {
        return textureName;
    }

    PRectangle* WorldObject::getBounds() {
        return bounds;
    }

    void WorldObject::setBounds(int x, int y,  int width, int height){
        bounds = new PRectangle(x, y, width, height);
    }

    void WorldObject::setTexture(string texture) {
		this->textureName = texture;
		Texture2D *t= Director::getInstance()->getTextureCache()->addImage(texture + ".png");
		this->sprite->setTexture(t);
    }

    void WorldObject::setPositionPoint(PPoint* point){
    	position = new PPoint(point->getX(), point->getY(), width, height);
    	bounds = new PRectangle(position->getX(), position->getY(), width, height);
    }

    int WorldObject::inverse(int count) {
        return (-1) * count;
    }
