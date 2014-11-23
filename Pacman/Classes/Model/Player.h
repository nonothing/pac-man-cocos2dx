#ifndef Player_H_
#define Player_H_
#include "WorldObjectMove.h"
#include "Brick.h"
#include  "Model/list.h"

using namespace std;

class Player :public WorldObjectMove{
private:

	bool isOpen_;
public:

	CC_SYNTHESIZE(int, life_, Life);
Player(PPoint* position , ETexture texture ,int width, int height);
~Player(){
};
    bool eatPoint(List<Brick*>* bricks);
    bool eatBonus(List<Brick*>* bricks);
	bool eatFruit(List<Brick*>* bricks);

    void animate();

};
#endif /* Player_H_ */
