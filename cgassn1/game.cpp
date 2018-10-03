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
    map = new Map(800, 800, 50);
	player = new Player(50,50,UP, 50,50,1);
    
    map->mapInit();
}

Player* Game::getPlayer(void) {
	return player;
}


void Game::display(void) {

    glClear(GL_COLOR_BUFFER_BIT);
       glLoadIdentity();
    glTranslated(400-player->getXcord(), 400-player->getYcord(), 0);
    //gluLookAt(50.0, 50.0f, 10.0, player->getXcord(), player->getYcord(), .0, 0.0, .0, 1.0);

    map->display();
    player->display();

}
   

void Game::moveObjects(void) {
    map->checkWall(player);
	player->move();
    player->cleanWall();
    
}
