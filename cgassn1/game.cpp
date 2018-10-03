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


}


Game* myGame = new Game();

void
Game::init (void)
{
	player = new Player(0.1,0.2,UP, 0.1,0.2,0.0005);
}


void Game::display(void) {
	player->display();
}

void Game::moveObjects(void) {
	player->move();
}