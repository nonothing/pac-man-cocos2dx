#include "Model\WorldObject.h"
#include "View\WorldScene.h"

using namespace std;

    WorldObject::WorldObject(PPoint* point, string texture, int width, int height) {
    	this->width_ = width;
    	this->height_ = height;
        position_ = new PPoint(point->getX(), point->getY(), width, height);
        bounds_ = new PRectangle(position_->getX(), position_->getY(), width, height);
		this->textureName_ = texture;
        this->sprite_ = Sprite::create(texture + ".png");
		this->sprite_->setPosition(point->getX() * 30 + 15, point->getY() * 30 + 15);
    }

     WorldObject::~WorldObject(){
    	delete position_;
    	delete bounds_;
    }

    int WorldObject::getWidth() {
        return width_;
    }
    int WorldObject::getHeight() {
        return height_;
    }

    void WorldObject::setWidth(int width){
    	this->width_ = width;
    }
    void WorldObject::setHeight(int height){
    	this->height_ = height;
    }

    PPoint* WorldObject::getPosition() {
        return position_;
    }

    Sprite* WorldObject::getTexture() {
        return sprite_;
    }

	string WorldObject::getTextureName() {
        return textureName_;
    }

    PRectangle* WorldObject::getBounds() {
        return bounds_;
    }

    void WorldObject::setBounds(int x, int y,  int width, int height){
        bounds_ = new PRectangle(x, y, width, height);
    }

    void WorldObject::setTexture(string texture) {
		this->textureName_ = texture;
		Texture2D *t= Director::getInstance()->getTextureCache()->addImage(texture + ".png");
		this->sprite_->setTexture(t);
    }

    void WorldObject::setPositionPoint(PPoint* point){
    	position_ = new PPoint(point->getX(), point->getY(), width_, height_);
    	bounds_ = new PRectangle(position_->getX(), position_->getY(), width_, height_);
    }

    int WorldObject::inverse(int count) {
        return (-1) * count;
    }
