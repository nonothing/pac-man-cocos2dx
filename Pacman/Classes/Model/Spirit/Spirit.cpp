#include "model/Spirit/Spirit.h"
#include "model/World.h"

Spirit::Spirit(PPoint* position, string texture, int width, int height, Level* level) :
		WorldObjectMove(position, texture, width, height) {
		level_ = level;
		setState(ATTACK);
		setCountStep(0);
		createMap(level_->getWidth(), level_->getHeight());
	}

     void Spirit::refresh(World* world) {
        if (getState() == DEAD) {
        	setState( world->collidesWithRefresh(getBounds()));
        }
    }

     void Spirit::go(World* world) {
        clearMap();
        ai(world);
		sprite_->setPosition(position_->getX() + 15,position_->getY() + 15);
    }

     void Spirit::onLoadImageAttack() {
        switch (direction_) {
        case LEFT:
            setTexture(left());
            break;
        case RIGHT:
            setTexture(right());
            break;
        case DOWN:
            setTexture(down());
            break;
        case UP:
            setTexture(up());
            break;
        }
    }

	 void Spirit::clearMap(){
		for (int row = 0; row < level_->getWidth(); row++) {
		  for (int column = 0; column < level_->getHeight(); column++) {
			  map[row][column] = 0;
		  }
		}
	 }

     void Spirit::onLoadImageDead() {
        switch (direction_) {
        case LEFT:
            setTexture("orbLeft");
            break;
        case RIGHT:
            setTexture("orbRight");
            break;
        case UP:
            setTexture("orbUp");
            break;
        case DOWN:
            setTexture("orbDown");
            break;
        }
    }

     void Spirit::onLoadImageDefence(bool isWhite) {
        if (isWhite) {
            setTexture("spiritDefenceWhite");
        } else {
            setTexture("spiritDefence");
        }
    }

     void Spirit::onLoadImage() {
        switch (getState()) {
        case ATTACK:
            onLoadImageAttack();
            break;
        case DEFENCE:
            onLoadImageDefence(leftDefence);
            break;
        case DEAD:
            onLoadImageDead();
            break;
        }
    }

    void Spirit::move(World* world) {
        onLoadImage();
        refresh(world);
        onMove(direction_);

        if (!world->collidesWithLevel(getBounds())) {
            setPosition(getBounds());
        }
        countStep++;
    }

    void Spirit::findDirection(World* world, PPoint* point, Spirit* spirit) {
        potencialMap(point, spirit, world->getBricks());
        if (getCountStep() >= (30 / SPEED_)) {
            int ** map = getMap();
			
            int step = map[getPointX()][getPointY()];

            if (map[getPointX() - 1][getPointY()] < step + 1) {
                setDirection(LEFT);
            }
            if (map[getPointX() + 1][getPointY()] < step + 1) {
                setDirection(RIGHT);
            }
            if (map[getPointX()][getPointY() - 1] < step + 1) {
				setDirection(DOWN);
            }
            if (map[getPointX()][getPointY() + 1] < step + 1) {
				setDirection(UP);
            }

            setCountStep(0);
        }
    }

    int Spirit::getCountStep() {
        return countStep;
    }

    void Spirit::setCountStep(int countStep) {
        this->countStep = countStep;
    }

    void Spirit::setDefence(bool isDefence) {
        this->leftDefence = isDefence;
    }

    void Spirit::createMap(int width, int height) {
            this->width_ = width;
            this->height_ = height;
            map = new int*[width];
                for (int i=0; i<width; i++)
                    map[i] = new int[height];
        }

     void Spirit::potencialMap(PPoint* point, Spirit* spirit, List<Brick*>* bricks) {
            inverseMap(bricks);
            int count = 0;
            step = 2;

            map[point->getX() / 30][point->getY() / 30] = 1;

            if (spirit->getState() != DEAD) {
                changeMap(spirit);
            }

            while (count < 40) {
                for (int row = 0; row < width_; row++) {
                    for (int column = 0; column < height_; column++) {
                        if (map[row][column] == step - 1) {
                            if (row > 1) {
                                if (map[row - 1][column] == 0) {
                                    map[row - 1][column] = step;
                                }
                            }
                            if (row < width_ - 1) {
                                if (map[row + 1][column] == 0) {
                                    map[row + 1][column] = step;
                                }
                            }
                            if (column > 1) {
                                if (map[row][column - 1] == 0) {
                                    map[row][column - 1] = step;
                                }
                            }
                            if (column < height_ - 1) {
                                if (map[row][column + 1] == 0) {
                                    map[row][column + 1] = step;
                                }
                            }
                        }
                    }
                }
                step++;
                count++;
            }

        }
	 
         void Spirit::changeMap(Spirit* spirit) {
            if (spirit->getDirection() == LEFT) {
                map[(spirit->getPointX()) + 1][spirit->getPointY()] = WALL;
            }

            if (spirit->getDirection() == RIGHT) {
                map[(spirit->getPointX()) - 1][spirit->getPointY()] = WALL;
            }

            if (spirit->getDirection() == DOWN) {
                map[spirit->getPointX()][(spirit->getPointY()) + 1] = WALL;
            }

            if (spirit->getDirection() == UP) {
                map[spirit->getPointX()][(spirit->getPointY()) - 1] = WALL;
            }
        }

         void Spirit::inverseMap(List<Brick*>* bricks) {
            int row = 0;
            int column = 0;
            for(int i=0; i < bricks->size(); i++){
            		if(bricks->get(i)->getTextureName() == "background"
                        || bricks->get(i)->getTextureName() == "point"
						|| bricks->get(i)->getTextureName() == "none"
                        || bricks->get(i)->getTextureName() == "bonus") {
                    map[row][column] = 0;
                } else {
                    map[row][column] = WALL;
                }
                row++;
                if (row == width_) {
                    row = 0;
                    column++;
                }
                if (column == height_) {
                    column = 0;
                }
            }
        }

         int** Spirit::getMap() {
            return map;
        }


