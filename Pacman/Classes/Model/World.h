#ifndef World_H_
#define World_H_

#include "Player.h"
#include "Point.h"
#include "Brick.h"
#include "Model\List.h"
#include "model/Spirit/Spirit.h"
#include "Level.h"

class Spirit;
class World {
    
 private:
	 Player* player;
 bool isSound;
  int  width;
  int  height;
  int countPoint;
  int record;
  int score;

//  Fruit* fruit;

 public:
  World();
  World(Level* level);
  ~World();
//     void startPointSpirit(Level level) ;
//     void nextLevel(Level level, int record);
	 List<Brick*>* bricks;
	 List<Spirit*>* spirits;
     void startPointPlayer();
     void createSpirit() ;
     void generateFruit();
     bool collidesWithLevel(PRectangle* rect) ;
     int collidesWithRefresh(PRectangle* rect);
     int generationPoint();
     void newGame();
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
     int getWidth(){return 25;};
     int getHeight(){return 15;} ;
     Player* getPlayer() ;
     int getRecord();
     void setRecord(int newRecord);
	 int getScore(){return score;};
     int leftSpirit;
     void setScore(int score);
//     Fruit getFruit();
    
};
#endif /* World_H_ */
