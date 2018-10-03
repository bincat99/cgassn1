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
  


}


void
Game::init (void)
{
    map = new Map(5, 5, 5);
	player = new Player(0.1,0.2,UP, 0.1,0.1,0.0005);
}

Player* Game::getPlayer(void) {
	return player;
}


void Game::display(void) {

    glClear(GL_COLOR_BUFFER_BIT);
       glLoadIdentity();
    glTranslated(0.5-player->getXcord(), 0.5-player->getYcord(), 0);
    //gluLookAt(50.0, 50.0f, 10.0, player->getXcord(), player->getYcord(), .0, 0.0, .0, 1.0);

    map->display();
    player->display();

}
   

void Game::moveObjects(void) {
	player->move();
}
