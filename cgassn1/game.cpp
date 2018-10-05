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


Game::Game()
{
    
}


void
Game::init (void)
{
    map = new Map(1600, 1600, 50);
    player = new Player(50,50,UP, 50,50,1);
    
    map->mapInit();
    msg = new Message ();
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
    
    if (player->getStatus() == KILLED || gameClear)
        msg->display(gameClear, player->getPos());
    
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
        
        map->checkPlayerKill(player);
    }
    
    // player kill check
    
    else
    {
        if (keyboardBuffer['q'])
        {
            
            glutDestroyWindow ( windowId );
            exit (0);
        }
        
    }
    
}
