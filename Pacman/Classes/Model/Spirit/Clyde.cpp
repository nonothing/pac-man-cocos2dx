#include "model/Spirit/Clyde.h"

     Clyde::Clyde(PPoint* point, Level* level): Spirit(point, EClydeUp,30,30, level) {
        START_POINT = new PPoint(point->getX(), point->getY());
		DEFENCE_POINT = new PPoint(2, 13);
    }

     void Clyde::ai(World* world) {
        switch (getState()) {
        case ATTACK:
            AIattack(world);
            break;
        case DEFENCE:
            findDirection(world, DEFENCE_POINT->multiply(getWidth()), this);
            break;
        case DEAD:
            findDirection(world, START_POINT->multiply(getWidth()), this);
            break;
        }
        move(world);
    }

     void Clyde::AIattack(World* world) {
        potencialMap(world->getPlayer()->getPosition(), this, world->getBricks());

        int** map = getMap();
        int step = map[getPointX()][getPointY()];

        if (step <= 9) {
            findDirection(world, new PPoint(1 , 2, getWidth(),getHeight()), this);
        } else {
            findDirection(world, world->getPlayer()->getPosition(), this);
        }
    }

     ETexture Clyde::left() {
        return EClydeLeft;
    }

     ETexture Clyde::right() {
        return EClydeRight;
    }

     ETexture Clyde::down() {
        return EClydeDown;
    }

     ETexture Clyde::up() {
        return EClydeUp;
    }

