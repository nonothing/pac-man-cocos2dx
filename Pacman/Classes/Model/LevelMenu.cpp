#include "Model\LevelMenu.h"

LevelMenu::LevelMenu(PPoint* position, string texture, int level, int score, int width, int height) :
WorldObject(position, texture, width, height) {
	this->level = level;
	if (level <8){
		score = 400;
	} else if (level> 8 && level < 16){
		score = 23700;
	}
	else {
		this->score = score;
	}
	offsetX = 0;
	
	if (score > 10000) setTexture("three_gold_star");
	if (score < 10000) setTexture("two_gold_star");
	if (score < 1000) setTexture("one_gold_star");
	if (score < 100) setTexture("silver_stars");
	if (score == 0) setTexture("lock");
	spX = sprite->getPositionX();

		stringstream ss;
		ss << level+1;
		levelName = ss.str();
		createLabel();
		
}

PRectangle* LevelMenu::getRect(){
	return new PRectangle(getSpriteX(), getSpriteY(), 80, 80);
}

void LevelMenu::setOffsetX(int x){
	offsetX += x;
	sprite->setPositionX(spX + offsetX);
	createLabel();
}

void LevelMenu::createLabel(){
		label = LabelTTF::create(levelName, "fonts/Mistral.ttf", 50);
		label->setColor(Color3B(210, 160, 30));
		label->setPosition(Point(getSpriteX()+10,getSpriteY()-10));
}