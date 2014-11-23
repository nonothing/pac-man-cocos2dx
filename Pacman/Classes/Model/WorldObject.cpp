#include "Model/WorldObject.h"
#include "View/WorldScene.h"

using namespace std;

static char textures[ETextureLast][60] = {
"background.png",// 	EBackground = 0,
"none.png",// 	ENone,
"point.png",// 	EPoint,
"bonus.png",// 	EBonus,

"banana.png",// 	EBanana,
"apple.png",// 	EApple,
"apple_red.png",// 	EAppleRed,
"vinograd.png",// 	EVinograd,
"orange.png",// 	EOrange,
"cocos.png",// 	ECocos,

"horizontal.png",// 	EHorizontal,
"vertical.png",// 	EVertical,
"angle_ld.png",// 	EAngleLd,
"angle_rd.png",// 	EAangleRd,
"angle_rv.png",// 	EAngleRv,
"angle_lv.png",// 	EAngleLv,
"arc_up.png",// 	EArcUp,
"arc_left.png",// 	EArcLeft,
"arc_right.png",// 	EArcRight,
"arc_down.png",// 	EArcDown,
"arc2_up.png",// 	EArc2Up,
"arc2_right.png",// 	EArc2Right,
"arc2_left.png",// 	EArc2Left,
"arc2_down.png",// 	EArc2Down,

"three_gold_star.png",// 	EThreeGoldStar,
"two_gold_star.png",// 	ETwoGoldStar,
"one_gold_star.png",// 	EOneGoldStar,
"silver_stars.png",// 	ESilverStars,
"lock_gold_star.png",// 	ELockGoldStar,
"lock.png",// 	Elock,
 
"pacmanLeftOpen.png",// 	EPacmanLeftOpen,
"pacmanLeftClose.png",// 	EPacmanLeftClose,
"pacmanRightOpen.png",// 	EPacmanRightOpen,
"pacmanRightClose.png",// 	EPacmanRightClose,
"pacmanDownClose.png",// 	EPacmanDownClose,
"pacmanDownOpen.png",// 	EPacmanDownOpen,
"pacmanUpClose.png",// 	EPacmanUpClose,
"pacmanUpOpen.png",// 	EPacmanUpOpen,
 
"orbLeft.png",// 	EOrbLeft,
"orbRight.png",// 	EOrbRight,
"orbUp.png",// 	EOrbUp,
"orbDown.png",// 	EOrbDown,
 
"spiritDefenceWhite.png",// 	ESpiritDefenceWhite,
"spiritDefence.png",// 	EspiritDefence,

"clydeLeft.png",// 	EClydeLeft,
"clydeRight.png",// 	EClydeRight,
"clydeDown.png",// 	EClydeDown,
"clydeUp.png",// 	EClydeUp,
 
"blinkyLeft.png",// 	EBlinkyLeft,
"blinkyRight.png",// 	EBlinkyRight,
"blinkyDown.png",// 	EBlinkyDown,
"blinkyUp.png",// 	EBlinkyUp,

"inkyLeft.png",// 	EInkyLeft,
"inkyRight.png",// 	EInkyRight,
"inkyDown.png",// 	EInkyDown,
"inkyUp.png",// 	EInkyUp,

"pinkyLeft.png",// 	EPinkyLeft,
"pinkyRight.png",// 	EPinkyRight,
"pinkyDown.png",// 	EPinkyDown,
"pinkyUp.png",// 	EPinkyUp,
 
"arrow_left.png",// 	EArrow_left,
"arrow_right.png",// 	EArrow_right,
};

WorldObject::WorldObject(PPoint* point, ETexture texture, int width, int height) {
	this->width_ = width;
	this->height_ = height;
	position_ = new PPoint(point->getX(), point->getY(), width, height);
	bounds_ = new PRectangle(position_->getX(), position_->getY(), width, height);
	this->textureName_ = texture;
	this->sprite_ = Sprite::create(textures[texture]);
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

ETexture WorldObject::getTextureName() {
	return textureName_;
}

PRectangle* WorldObject::getBounds() {
	return bounds_;
}

void WorldObject::setBounds(int x, int y,  int width, int height){
	bounds_ = new PRectangle(x, y, width, height);
}

void WorldObject::setTexture(ETexture texture) {
	this->textureName_ = texture;
	Texture2D *t= Director::getInstance()->getTextureCache()->addImage(textures[texture]);
	this->sprite_->setTexture(t);
}

void WorldObject::setPositionPoint(PPoint* point){
	position_ = new PPoint(point->getX(), point->getY(), width_, height_);
	bounds_ = new PRectangle(position_->getX(), position_->getY(), width_, height_);
}

int WorldObject::inverse(int count) {
	return (-1) * count;
}
