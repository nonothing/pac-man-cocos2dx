#ifndef Player_H_
#define Player_H_
#include "WorldObjectMove.h"
#include "Brick.h"

using namespace std;

class Player :public WorldObjectMove{
private:
	bool isOpen_;
	ETexture getNumber(ETexture texture, int open) const;
public:

	CC_SYNTHESIZE(int, life_, Life);
	Player(PPoint* position , ETexture texture ,int width, int height);

    bool eatPoint(const BricksVec bricks) const;
    bool eatBonus(const BricksVec bricks);
	bool eatFruit(const BricksVec bricks) const;
    void animate();

};
#endif /* Player_H_ */
