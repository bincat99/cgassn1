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
#include <list>


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

Player* Game::getPlayer(void)
{
	return player;
}


void Game::display(void)
{

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslated(400-player->getXcord(), 400-player->getYcord(), 0);

    map->display();
    player->display();
}
   

void Game::moveObjects(void)
{
    map->moveEnemy(player->getPos());
    map->checkWall(player);
	player->move();
    player->cleanWall();
}
