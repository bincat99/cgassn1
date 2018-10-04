//
//  map.cpp
//  cgassn1
//
//  Created by Dahun Lee on 2018. 10. 1..
//  Copyright © 2018년 Dahun Lee. All rights reserved.
//

#include "map.h"
#include <stdio.h>
#include "util.h"
#include "weapon.h"

Map::Map()
{
    
}


/*
 create map  (-w, -h) to (w, h)
 */
Map::Map (float w, float h, float g)
{
    width = w;
    height = h;
    gridLength = g;
}


void Map::mapInit()
{
    float x, y;
    
    
    for (x = - width; x < width; x += gridLength)
    {
        listWall.push_back (new Wall (x, -height));
        listWall.push_back (new Wall (x, height));
    }
    for (y = - height; y < height; y += gridLength)
    {
        listWall.push_back (new Wall (-width, y));
        listWall.push_back (new Wall (width, y));
    }
    listWall.push_back (new Wall (width, height));
    
    for (y = - height; y < height; y += gridLength)
    {
        
        for (x = -width ; x < width; x += gridLength)
        {
            listEmpty.push_back (new EmptySpace (x, y));
        }
        
    }
    
    for (int i = 0; i < 1; i++)
    {
        listEnemy.push_back(new Enemy(300, 300, (enum Direction)(rand () % 4), GLOBAL_GRID_LENGTH, GLOBAL_GRID_LENGTH, 1));
        listEnemy.push_back(new Enemy(350, 250, (enum Direction)(rand () % 4), GLOBAL_GRID_LENGTH, GLOBAL_GRID_LENGTH, 1));
    }
}

void Map::display()
{
    
    for (std::list<EmptySpace*>::iterator it = listEmpty.begin(); it != listEmpty.end(); it++)
        (*it)->display();
    
    for (std::list<Wall*>::iterator it = listWall.begin(); it != listWall.end(); it++)
        (*it)->display();
    
    
    for (std::list<Enemy*>::iterator it = listEnemy.begin(); it != listEnemy.end(); it++)
        (*it)->display();
    
}


void Map::checkWall (Player * player)
{    
    unsigned int colBit = 0;
    bool colSide[4] = {0,};
    for (std::list<Wall*>::iterator it = listWall.begin(); it != listWall.end(); it++)
    {
        colBit |= CheckCollision(player->getPos(), (*it)->getPos());
    }
    
    colSide[LEFT] = colBit & COL_LEFT;
    colSide[UP] = colBit & COL_UP;
    colSide[RIGHT] = colBit & COL_RIGHT;
    colSide[DOWN] = colBit & COL_DOWN;
    
    player->checkWall (colSide);
}

void Map::checkWallEnemy ()
{
    for (std::list<Enemy*>::iterator it = listEnemy.begin(); it != listEnemy.end(); it++)
    {
        unsigned int colBit = 0;
        bool colSide[4] = {0,};
        for (std::list<Wall*>::iterator itWall = listWall.begin(); itWall != listWall.end(); itWall++)
        {
            colBit |= CheckCollision((*it)->getPos(), (*itWall)->getPos());
        }
        
        colSide[LEFT] = colBit & COL_LEFT;
        colSide[UP] = colBit & COL_UP;
        colSide[RIGHT] = colBit & COL_RIGHT;
        colSide[DOWN] = colBit & COL_DOWN;
        
        (*it)->checkWall (colSide);
    }
    
}

void Map::cleanWallEnemy ()
{
    for (std::list<Enemy*>::iterator it = listEnemy.begin(); it != listEnemy.end(); it++)
        (*it)->cleanWall();
}

void Map::moveEnemy (position playerPos)
{
    for (std::list<Enemy*>::iterator it = listEnemy.begin(); it != listEnemy.end(); it++)
        (*it)->move(playerPos.x, playerPos.y);
}


void Map::checkEnemyKill (std::list<Weapon*> l)
{
    if (l.empty()) {
        return;
    }
    //puts ("test");
    for (std::list<Weapon*>::iterator it = l.begin(); it != l.end(); it++)
    {
      
        for (std::list<Enemy*>::iterator itEnemy = listEnemy.begin(); itEnemy != listEnemy.end(); itEnemy++)
        {
            unsigned int colBit = 0;
            colBit = CheckCollision((*it)->getPos(), (*itEnemy)->getPos());
            
            if (colBit != 0)
            {
                (*itEnemy)->killed();
                (*it)->killed();
            }
        }
    }
    
    /*
    std::list<Weapon*>::iterator it = l.begin();
    
    while (it != l.end ())
    {
        if ((*it)->getStatus() == KILLED)
        {
            Weapon *tmp = NULL;
            tmp = *it;
            l.erase(it);
            it++;
            delete tmp;
        }
        
        else it++;
    }*/
    
    std::list<Enemy*>::iterator itEnemy = listEnemy.begin();
    
    while (itEnemy != listEnemy.end ())
    {
        if ((*itEnemy)->getStatus() == KILLED)
        {
            Enemy *tmp = NULL;
            tmp = *itEnemy;
            listEnemy.erase(itEnemy);
            itEnemy++;
            delete tmp;
        }
        else itEnemy++;
    }
}
