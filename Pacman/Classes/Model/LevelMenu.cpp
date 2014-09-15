#include "Model\LevelMenu.h"

LevelMenu::LevelMenu(PPoint* position, string texture, int level, int score, int width, int height) :
WorldObject(position, texture, width, height) {
	this->level_ = level;
	if (level <8){
		score = 400;
	} else if (level> 8 && level < 16){
		score = 23700;
	}
	else {
		this->score_ = score;
	}
	offsetX_ = 0;
	
	if (score > 10000) setTexture("three_gold_star");
	if (score < 10000) setTexture("two_gold_star");
	if (score < 1000) setTexture("one_gold_star");
	if (score < 100) setTexture("silver_stars");
	if (score == 0) setTexture("lock");
	spX_ = sprite_->getPositionX();

		stringstream ss;
		ss << level+1;
		levelName_ = ss.str();
		createLabel();
		
}

bool LevelMenu::getLock(){
	return (score_ == 0) ? true : false; 
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
		label_ = LabelTTF::create(levelName_, "fonts/Mistral.ttf", 50);
		label_->setColor(Color3B(210, 160, 30));
		label_->setPosition(Point(getSpriteX()+10,getSpriteY()-10));
}