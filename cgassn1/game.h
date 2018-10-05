//
//  game.h
//  cgassn1
//
//  Created by Dahun Lee on 2018. 10. 1..
//  Copyright © 2018년 Dahun Lee. All rights reserved.
//

#ifndef game_h
#define game_h

#include "map.h"
#include "player.h"

#include "enemy.h"
#include "msg.h"


class Game
{
    
private:
    Map *map;
    Player *player;
    Enemy *enemy;
	Message *msg;
    
    
public:
    Game ();

    void init (void);

    void play ();
	void display(void);
	void reshape(int w, int h);
	void moveObjects();

	Player* getPlayer();

    
};

#endif /* game_h */
