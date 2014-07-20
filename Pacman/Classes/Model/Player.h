#ifndef Player_H_
#define Player_H_
#include "WorldObjectMove.h"
#include "Brick.h"
#include  "Model\list.h"

using namespace std;

class Player :public WorldObjectMove{
private:
	int life;
	bool isOpen;
public:
Player(PPoint* position , string texture ,int width, int height);
~Player(){
};
    bool eatPoint(List<Brick*>* bricks);
    bool eatBonus(List<Brick*>* bricks);

    void animate();
    int getLife();
    void setLife(int life);

};
#endif /* Player_H_ */
