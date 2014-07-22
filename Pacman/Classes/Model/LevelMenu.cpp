#include "Model\LevelMenu.h"

LevelMenu::LevelMenu(PPoint* position, string texture, int level, int score, int width, int height) :
WorldObject(position, texture, width, height) {
	this->level = level;
	this->score = score;

	if (score > 10000) setTexture("three_gold_star");
	if (score < 10000) setTexture("two_gold_star");
	if (score < 1000) setTexture("one_gold_star");
	if (score < 100) setTexture("silver_stars");
	if (score == 0) setTexture("lock");

}


PRectangle* LevelMenu::getRect(){
	return new PRectangle(getSpriteX(), getSpriteY(), 80, 80);
}


