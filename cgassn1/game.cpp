//
//  game.cpp
//  cgassn1
//
//  Created by Dahun Lee on 2018. 10. 1..
//  Copyright © 2018년 Dahun Lee. All rights reserved.
//




#include "game.h"
#include "util.h"
#include <stdio.h>
using namespace std;

void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

Game::Game()
{
    map = new Map();

 /*   player = new Player();
    enemy = new Enemy ();*/
}


Game* myGame = new Game();

void
Game::init (void)
{

    
}


