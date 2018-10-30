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


void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

extern Game *game;
Game::Game()
{
    
}

void
timerFunc (int n)
{
    game->gameEnd = true;
}

void
gameTimerInit ()
{
    glutTimerFunc (100 * 1000, timerFunc, 1);
}

void
Game::init (void)
{
    map = new Map(800, 800, 50);
    player = new Player(-750,750,DOWN, 50,50,1);
    
    map->mapInit();
    msg = new Message ();
    
    remainingTime = CLOCKS_PER_SEC * 10;
    startTime = clock();
    gameEnd = false;
    gameClear = false;
    gameTimerInit ();
}

Player* Game::getPlayer(void)
{
    return player;
}


void Game::display(void)
{
    
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(400-player->getPos().x, 400-player->getPos().y, 0);
    //gluLookAt(player->getPos().x , player->getPos().y, 0, player->getPos().x, player->getPos().y ,  -1, 0, 1, 0);
    
    
    
    map->display();
    player->display();
    
    if (player->getStatus() == KILLED || gameClear || gameEnd)
        msg->display(gameClear, player->getPos());
    
}

void Game::checkTimeout()
{
    
//    if (clock() > startTime + remainingTime)
//        player->setStatus(KILLED);
}

void Game::restart ()
{
    delete this->player;
    delete this->map;
    delete this->msg;

    init();
}

void Game::moveObjects(void)
{
    if (player->getStatus() == ALIVE && !gameClear && !gameEnd)
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
        //checkTimeout();
        printf ("%d\n",glutGet(GLUT_ELAPSED_TIME));
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
