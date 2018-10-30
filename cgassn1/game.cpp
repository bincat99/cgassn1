//
//  game.cpp
//  cgassn1
//
//  Created by Dahun Lee on 2018. 10. 1..
//  Copyright © 2018년 Dahun Lee. All rights reserved.
//





#include "game.h"
#include "util.h"
#include "msg.h"
#include <stdio.h>
#include <list>
#include <iostream>
#include <string>


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
    player = new Player(-750,750,DOWN, 50,50,1);
    
    map->mapInit();
    msg = new Message ();

	remainingTime = CLOCKS_PER_SEC * 100;
	startTime = clock();
}

Player* Game::getPlayer(void)
{
    return player;
}


void Game::display(void)
{
    
	ctm = glm::scale(glm::mat4(1.0f), glm::vec3((float)1 / 800));
	ctm = glm::transpose(glm::translate(ctm, glm::vec3(0 - player->getPos().x, 0 - player->getPos().y, 0)));
	temp = ctm;
	glUniformMatrix4fv(matrix_loc, 1, GL_TRUE, value_ptr(ctm));

	/*
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(400-player->getPos().x, 400-player->getPos().y, 0);
    //gluLookAt(player->getPos().x , player->getPos().y, 0, player->getPos().x, player->getPos().y ,  -1, 0, 1, 0);
    */
    
    
    map->display();
    player->display();
	displayTime();
    
   // if (player->getStatus() == KILLED || gameClear)
  //      msg->display(gameClear, player->getPos());
    
}

void Game::displayTime(void) {
	glColor3f(0.f, 0.f, 0.f);
	char buf[100] = { 0 };
	std::string str = "Remain Time : " + std::to_string((int)((remainingTime -clock()) / 1000));
	sprintf_s(buf, str.c_str());
	renderbitmap(500, 1550, GLUT_BITMAP_TIMES_ROMAN_24, buf);
}


void Game::checkTimeout()
{

	if (clock() > startTime + remainingTime)
		player->setStatus(KILLED);
}
void Game::restart()
{
	delete this->player;
	delete this->map;
	delete this->msg;
	init();
}

void Game::moveObjects(void)
{
    if (player->getStatus() == ALIVE && !gameClear)
    {
        
        
        map->checkWallEnemy();
        map->moveEnemy(player->getPos());
        map->cleanWallEnemy ();
        
        map->checkWall(player);
        player->move();
        player->cleanWall();
        
        // bullet check
        map->checkWallWeapon(player->getWeaponList());
        map->checkEnemyKill(player->getWeaponList());
        player->checkWeapon();
        
        // player and item
        
        map->checkItem (player);
        
        player->checkItemDuration();

		player->checkNohit();
		map->checkPlayerKill(player);
		checkTimeout();
    }
    
    // player kill check
    
    else
    {
        if (keyboardBuffer['q'])
        {
            
            glutDestroyWindow ( windowId );
            exit (0);
        }

		if (keyboardBuffer['r'])
		{

			restart();

		}
        
    }
    
}
