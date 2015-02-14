#ifndef World_H_
#define World_H_

#include "Player.h"
#include "Point.h"
#include "Brick.h"
#include "model/Spirit/Spirit.h"
#include "Level.h"
#include "Controller/SoundController.h"

class World {
    
private:
	Player* player_;
	bool isSound_;
	int countPoint_;
	BricksVec bricks_;
	SpiritsVec spirits_;
	SoundController* soundController_;

public:
	World();
	World(Level* level, SoundController* soundController);
	~World();
	CC_SYNTHESIZE(int, currentLevel_, CurrentLevel);
	CC_SYNTHESIZE(bool, isDefenceSpirit_, DefenceSpirit);
	CC_SYNTHESIZE(int, score_, Score);

	SpiritsVec getSpirits() const;
	BricksVec  getBricks() const;

	void startPointPlayer();
	void createSpirit() ;
	bool collidesWithLevel(PRectangle* rect);
	int generationPoint();
	void generationFruit();
	bool eatFruit();
	bool eatPoint();
	bool eatBonus();
	void tryToPlayerGo(int direction);
	void defenceNPC();
	void attackNPC() ;
	bool deadPlayer ();
	bool deadSpirit();
	bool isVictory();
	bool isGameOver();
	Player* getPlayer();
	bool isFruit(ETexture textureName);
    
};
#endif /* World_H_ */
