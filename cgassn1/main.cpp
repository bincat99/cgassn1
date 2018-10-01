//
//  main.cpp
//  cgassn1
//
//  Created by Dahun Lee on 2018. 10. 1..
//  Copyright © 2018년 Dahun Lee. All rights reserved.
//

#include <iostream>

//#include "map.h"
//#include "enemy.h"
//#include "player.h"
//#include "weapon.h"
#include "game.h"


using namespace std;


int
main (int argc, char * argv[])
{
    Game *game = new Game();
    
    game->init(&argc, argv);

}

