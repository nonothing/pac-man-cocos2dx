#include "Model/LevelMenu.h"
#include "View/LevelMenuScene.h"

LevelMenu::LevelMenu(PPoint* position, ETexture texture, int level, int score, int width, int height) :
WorldObject(position, texture, width, height) {
	this->level_ = level;
	this->score_ = score;
	name_ = LevelMenuScene::parseLevel(level + 1);
	offsetX_ = 0;

	score_ = UserDefault::getInstance()->getIntegerForKey(name_.c_str(), level == 0 ? 1 : 0);
	
	if (score_ > 10000) setTexture(EThreeGoldStar);
	if (score_ < 10000) setTexture(ETwoGoldStar);
	if (score_ < 1000) setTexture(EOneGoldStar);
	if (score_ < 100) setTexture(ESilverStars);
	if (score_ == 0) setTexture(Elock);
	spX_ = sprite_->getPositionX();

		stringstream ss;
		ss << level+1;
		numberLevel_ = ss.str();
		createLabel();
		
}

bool LevelMenu::getLock(){
	return score_ <= 0 ? true : false; 
}

LabelTTF* LevelMenu::getLabel(){
	return label_;
}

PRectangle* LevelMenu::getRect(){
	return new PRectangle(getSpriteX(), getSpriteY(), 80, 80);
}

void LevelMenu::setOffsetX(int x){
	offsetX_ += x;
	sprite_->setPositionX(spX_ + offsetX_);
	createLabel();
}

void LevelMenu::createLabel(){
	label_ = LabelTTF::create(numberLevel_, "fonts/Mistral.ttf", 50);
	label_->setColor(Color3B(210, 160, 30));
	label_->setPosition(Point(getSpriteX() + 10, getSpriteY() - 10));
}