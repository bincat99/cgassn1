//
//  game.cpp
//  cgassn1
//
//  Created by Dahun Lee on 2018. 10. 1..
//  Copyright © 2018년 Dahun Lee. All rights reserved.
//


#include "game.h"


Game::Game()
{
    map = new Map();
    player = new Player();
    enemy = new Enemy ();
}
