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
  Player* player_;
  bool isSound_;
  int countPoint_;
  int score_;
  bool isDefenceSpirit_;

 public:
  World();
  World(Level* level);
  ~World();
//     void startPointSpirit(Level level) ;
//     void nextLevel(Level level, int record);
	 List<Brick*>* bricks;
	 List<Spirit*>* spirits;

	 bool isDefence(){return isDefenceSpirit_;}
	 void setDefenceSpirit(bool is){ isDefenceSpirit_ = is;}
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
	 Player* getPlayer();
     int getRecord();
     void setRecord(int newRecord);
	 int getScore(){return score_;};
     int leftSpirit;
	 void setScore(int score){this->score_ = score;};
//     Fruit getFruit();
    
};
#endif /* World_H_ */
