#include "model/Spirit/Clyde.h"

     Clyde::Clyde(PPoint* point): Spirit(point, "clydeUp",30,30) {
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
        potencialMap(world->getPlayer()->getPosition(), this, world->bricks);

        int** map = getMap();
        int step = map[getPointX()][getPointY()];

        if (step <= 9) {
            findDirection(world, new PPoint(1 , 2, getWidth(),getHeight()), this);
        } else {
            findDirection(world, world->getPlayer()->getPosition(), this);
        }
    }

     string Clyde::left() {
        return "clydeLeft";
    }

     string Clyde::right() {
        return "clydeRight";
    }

     string Clyde::down() {
        return "clydeDown";
    }

     string Clyde::up() {
        return "clydeUp";
    }

