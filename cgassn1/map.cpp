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
#include "BmpLoader.h"
#include <iostream>
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
		int idx = (int)(x+width)/gridLength;
		map[0][idx] = 1;
		map[31][idx] = 1;
    }
    for (y = - height; y < height; y += gridLength)
    {
        listWall.push_back (new Wall (-width, y));
        listWall.push_back (new Wall (width, y));
		int idx = (int)(y + height) / gridLength;
		map[idx][0] = 1;
		map[idx][31] = 1;
    }
    listWall.push_back (new Wall (width, height));

	listWall.push_back(new Wall(5 * gridLength - width, height - 3 * gridLength));
	listWall.push_back(new Wall(6 * gridLength - width, height - 3 * gridLength));
	listWall.push_back(new Wall(10 * gridLength - width, height - 3 * gridLength));
	listWall.push_back(new Wall(11 * gridLength - width, height - 3 * gridLength));
	listWall.push_back(new Wall(12 * gridLength - width, height - 3 * gridLength));
	listWall.push_back(new Wall(14 * gridLength - width, height - 3 * gridLength));
	listWall.push_back(new Wall(15 * gridLength - width, height - 3 * gridLength));
	listWall.push_back(new Wall(16 * gridLength - width, height - 3 * gridLength));
	listWall.push_back(new Wall(17 * gridLength - width, height - 3 * gridLength));
	listWall.push_back(new Wall(19 * gridLength - width, height - 3 * gridLength));
	listWall.push_back(new Wall(20 * gridLength - width, height - 3 * gridLength));
	listWall.push_back(new Wall(21 * gridLength - width, height - 3 * gridLength));


	listWall.push_back(new Wall(4 * gridLength - width, height - 4 * gridLength));
	listWall.push_back(new Wall(7 * gridLength - width, height - 4 * gridLength));
	listWall.push_back(new Wall(9 * gridLength - width, height - 4 * gridLength));
	listWall.push_back(new Wall(14 * gridLength - width, height - 4 * gridLength));
	listWall.push_back(new Wall(19 * gridLength - width, height - 4 * gridLength));
	listWall.push_back(new Wall(22 * gridLength - width, height - 4 * gridLength));


	listWall.push_back(new Wall(4 * gridLength - width, height - 5 * gridLength));
	listWall.push_back(new Wall(10 * gridLength - width, height - 5 * gridLength));
	listWall.push_back(new Wall(11 * gridLength - width, height - 5 * gridLength));
	listWall.push_back(new Wall(14 * gridLength - width, height - 5 * gridLength));
	listWall.push_back(new Wall(15 * gridLength - width, height - 5 * gridLength));
	listWall.push_back(new Wall(16 * gridLength - width, height - 5 * gridLength));
	listWall.push_back(new Wall(19 * gridLength - width, height - 5 * gridLength));
	listWall.push_back(new Wall(22 * gridLength - width, height - 5 * gridLength));


	listWall.push_back(new Wall(4 * gridLength - width, height - 6 * gridLength));
	listWall.push_back(new Wall(7 * gridLength - width, height - 6 * gridLength));
	listWall.push_back(new Wall(12 * gridLength - width, height - 6 * gridLength));
	listWall.push_back(new Wall(14 * gridLength - width, height - 6 * gridLength));
	listWall.push_back(new Wall(19 * gridLength - width, height - 6 * gridLength));
	listWall.push_back(new Wall(22 * gridLength - width, height - 6 * gridLength));


	listWall.push_back(new Wall(5 * gridLength - width, height - 7 * gridLength));
	listWall.push_back(new Wall(6 * gridLength - width, height - 7 * gridLength));
	listWall.push_back(new Wall(9 * gridLength - width, height - 7 * gridLength));
	listWall.push_back(new Wall(10 * gridLength - width, height - 7 * gridLength));
	listWall.push_back(new Wall(11 * gridLength - width, height - 7 * gridLength));
	listWall.push_back(new Wall(14 * gridLength - width, height - 7 * gridLength));
	listWall.push_back(new Wall(15 * gridLength - width, height - 7 * gridLength));
	listWall.push_back(new Wall(16 * gridLength - width, height - 7 * gridLength));
	listWall.push_back(new Wall(17 * gridLength - width, height - 7 * gridLength));
	listWall.push_back(new Wall(19 * gridLength - width, height - 7 * gridLength));
	listWall.push_back(new Wall(20 * gridLength - width, height - 7 * gridLength));
	listWall.push_back(new Wall(21 * gridLength - width, height - 7 * gridLength));


	listWall.push_back(new Wall(6 * gridLength - width, height - 9 * gridLength));
	listWall.push_back(new Wall(9 * gridLength - width, height - 9 * gridLength));
	listWall.push_back(new Wall(10 * gridLength - width, height - 9 * gridLength));
	listWall.push_back(new Wall(11 * gridLength - width, height - 9 * gridLength));
	listWall.push_back(new Wall(12 * gridLength - width, height - 9 * gridLength));
	listWall.push_back(new Wall(15 * gridLength - width, height - 9 * gridLength));

	listWall.push_back(new Wall(5 * gridLength - width, height - 10 * gridLength));
	listWall.push_back(new Wall(6 * gridLength - width, height - 10 * gridLength));
	listWall.push_back(new Wall(9 * gridLength - width, height - 10 * gridLength));
	listWall.push_back(new Wall(14 * gridLength - width, height - 10 * gridLength));
	listWall.push_back(new Wall(15 * gridLength - width, height - 10 * gridLength));


	listWall.push_back(new Wall(4 * gridLength - width, height - 11 * gridLength));
	listWall.push_back(new Wall(6 * gridLength - width, height - 11 * gridLength));
	listWall.push_back(new Wall(9 * gridLength - width, height - 11 * gridLength));
	listWall.push_back(new Wall(10 * gridLength - width, height - 11 * gridLength));
	listWall.push_back(new Wall(11 * gridLength - width, height - 11 * gridLength));
	listWall.push_back(new Wall(15 * gridLength - width, height - 11 * gridLength));

	listWall.push_back(new Wall(4 * gridLength - width, height - 12 * gridLength));
	listWall.push_back(new Wall(5 * gridLength - width, height - 12 * gridLength));
	listWall.push_back(new Wall(6 * gridLength - width, height - 12 * gridLength));
	listWall.push_back(new Wall(7 * gridLength - width, height - 12 * gridLength));
	listWall.push_back(new Wall(12 * gridLength - width, height - 12 * gridLength));
	listWall.push_back(new Wall(15 * gridLength - width, height - 12 * gridLength));

	listWall.push_back(new Wall(6 * gridLength - width, height - 13 * gridLength));
	listWall.push_back(new Wall(9 * gridLength - width, height - 13 * gridLength));
	listWall.push_back(new Wall(10 * gridLength - width, height - 13 * gridLength));
	listWall.push_back(new Wall(11 * gridLength - width, height - 13 * gridLength));
	listWall.push_back(new Wall(14 * gridLength - width, height - 13 * gridLength));
	listWall.push_back(new Wall(15 * gridLength - width, height - 13 * gridLength));
	listWall.push_back(new Wall(16 * gridLength - width, height - 13 * gridLength));


	listWall.push_back(new Wall(5 * gridLength - width, height - 15 * gridLength));
	listWall.push_back(new Wall(6 * gridLength - width, height - 15 * gridLength));
	listWall.push_back(new Wall(10 * gridLength - width, height - 15 * gridLength));
	listWall.push_back(new Wall(11 * gridLength - width, height - 15 * gridLength));
	listWall.push_back(new Wall(12 * gridLength - width, height - 15 * gridLength));
	listWall.push_back(new Wall(15 * gridLength - width, height - 15 * gridLength));
	listWall.push_back(new Wall(16 * gridLength - width, height - 15 * gridLength));
	listWall.push_back(new Wall(17 * gridLength - width, height - 15 * gridLength));
	listWall.push_back(new Wall(19 * gridLength - width, height - 15 * gridLength));
	listWall.push_back(new Wall(22 * gridLength - width, height - 15 * gridLength));
	listWall.push_back(new Wall(25 * gridLength - width, height - 15 * gridLength));


	listWall.push_back(new Wall(4 * gridLength - width, height - 16 * gridLength));
	listWall.push_back(new Wall(7 * gridLength - width, height - 16 * gridLength));
	listWall.push_back(new Wall(9 * gridLength - width, height - 16 * gridLength));
	listWall.push_back(new Wall(14 * gridLength - width, height - 16 * gridLength));
	listWall.push_back(new Wall(19 * gridLength - width, height - 16 * gridLength));
	listWall.push_back(new Wall(20 * gridLength - width, height - 16 * gridLength));
	listWall.push_back(new Wall(22 * gridLength - width, height - 16 * gridLength));
	listWall.push_back(new Wall(24 * gridLength - width, height - 16 * gridLength));
	listWall.push_back(new Wall(25 * gridLength - width, height - 16 * gridLength));

	listWall.push_back(new Wall(4 * gridLength - width, height - 17 * gridLength));
	listWall.push_back(new Wall(5 * gridLength - width, height - 17 * gridLength));
	listWall.push_back(new Wall(6 * gridLength - width, height - 17 * gridLength));
	listWall.push_back(new Wall(7 * gridLength - width, height - 17 * gridLength));
	listWall.push_back(new Wall(10 * gridLength - width, height - 17 * gridLength));
	listWall.push_back(new Wall(11 * gridLength - width, height - 17 * gridLength));
	listWall.push_back(new Wall(15 * gridLength - width, height - 17 * gridLength));
	listWall.push_back(new Wall(16 * gridLength - width, height - 17 * gridLength));
	listWall.push_back(new Wall(19 * gridLength - width, height - 17 * gridLength));
	listWall.push_back(new Wall(21 * gridLength - width, height - 17 * gridLength));
	listWall.push_back(new Wall(22 * gridLength - width, height - 17 * gridLength));
	listWall.push_back(new Wall(25 * gridLength - width, height - 17 * gridLength));



	listWall.push_back(new Wall(4 * gridLength - width, height - 18 * gridLength));
	listWall.push_back(new Wall(7 * gridLength - width, height - 18 * gridLength));
	listWall.push_back(new Wall(12 * gridLength - width, height - 18 * gridLength));
	listWall.push_back(new Wall(17 * gridLength - width, height - 18 * gridLength));
	listWall.push_back(new Wall(19 * gridLength - width, height - 18 * gridLength));
	listWall.push_back(new Wall(22 * gridLength - width, height - 18 * gridLength));
	listWall.push_back(new Wall(25 * gridLength - width, height - 18 * gridLength));


	listWall.push_back(new Wall(4 * gridLength - width, height - 19 * gridLength));
	listWall.push_back(new Wall(7 * gridLength - width, height - 19 * gridLength));
	listWall.push_back(new Wall(9 * gridLength - width, height - 19 * gridLength));
	listWall.push_back(new Wall(10 * gridLength - width, height - 19 * gridLength));
	listWall.push_back(new Wall(11 * gridLength - width, height - 19 * gridLength));
	listWall.push_back(new Wall(14 * gridLength - width, height - 19 * gridLength));
	listWall.push_back(new Wall(15 * gridLength - width, height - 19 * gridLength));
	listWall.push_back(new Wall(16 * gridLength - width, height - 19 * gridLength));
	listWall.push_back(new Wall(19 * gridLength - width, height - 19 * gridLength));
	listWall.push_back(new Wall(22 * gridLength - width, height - 19 * gridLength));
	listWall.push_back(new Wall(24 * gridLength - width, height - 19 * gridLength));
	listWall.push_back(new Wall(25 * gridLength - width, height - 19 * gridLength));
	listWall.push_back(new Wall(26 * gridLength - width, height - 19 * gridLength));



	listWall.push_back(new Wall(4 * gridLength - width, height - 21 * gridLength));
	listWall.push_back(new Wall(5 * gridLength - width, height - 21 * gridLength));
	listWall.push_back(new Wall(6 * gridLength - width, height - 21 * gridLength));
	listWall.push_back(new Wall(7 * gridLength - width, height - 21 * gridLength));
	listWall.push_back(new Wall(8 * gridLength - width, height - 21 * gridLength));
	listWall.push_back(new Wall(10 * gridLength - width, height - 21 * gridLength));
	listWall.push_back(new Wall(11 * gridLength - width, height - 21 * gridLength));
	listWall.push_back(new Wall(12 * gridLength - width, height - 21 * gridLength));
	listWall.push_back(new Wall(13 * gridLength - width, height - 21 * gridLength));
	listWall.push_back(new Wall(16 * gridLength - width, height - 21 * gridLength));
	listWall.push_back(new Wall(17 * gridLength - width, height - 21 * gridLength));
	listWall.push_back(new Wall(20 * gridLength - width, height - 21 * gridLength));
	listWall.push_back(new Wall(24 * gridLength - width, height - 21 * gridLength));


	listWall.push_back(new Wall(6 * gridLength - width, height - 22 * gridLength));
	listWall.push_back(new Wall(10 * gridLength - width, height - 22 * gridLength));
	listWall.push_back(new Wall(15 * gridLength - width, height - 22 * gridLength));
	listWall.push_back(new Wall(18 * gridLength - width, height - 22 * gridLength));
	listWall.push_back(new Wall(20 * gridLength - width, height - 22 * gridLength));
	listWall.push_back(new Wall(21 * gridLength - width, height - 22 * gridLength));
	listWall.push_back(new Wall(23 * gridLength - width, height - 22 * gridLength));
	listWall.push_back(new Wall(24 * gridLength - width, height - 22 * gridLength));


	listWall.push_back(new Wall(6 * gridLength - width, height - 23 * gridLength));
	listWall.push_back(new Wall(10 * gridLength - width, height - 23 * gridLength));
	listWall.push_back(new Wall(11 * gridLength - width, height - 23 * gridLength));
	listWall.push_back(new Wall(12 * gridLength - width, height - 23 * gridLength));
	listWall.push_back(new Wall(15 * gridLength - width, height - 23 * gridLength));
	listWall.push_back(new Wall(16 * gridLength - width, height - 23 * gridLength));
	listWall.push_back(new Wall(17 * gridLength - width, height - 23 * gridLength));
	listWall.push_back(new Wall(18 * gridLength - width, height - 23 * gridLength));
	listWall.push_back(new Wall(20 * gridLength - width, height - 23 * gridLength));
	listWall.push_back(new Wall(22 * gridLength - width, height - 23 * gridLength));
	listWall.push_back(new Wall(24 * gridLength - width, height - 23 * gridLength));


	listWall.push_back(new Wall(6 * gridLength - width, height - 24 * gridLength));
	listWall.push_back(new Wall(10 * gridLength - width, height - 24 * gridLength));
	listWall.push_back(new Wall(15 * gridLength - width, height - 24 * gridLength));
	listWall.push_back(new Wall(18 * gridLength - width, height - 24 * gridLength));
	listWall.push_back(new Wall(20 * gridLength - width, height - 24 * gridLength));
	listWall.push_back(new Wall(24 * gridLength - width, height - 24 * gridLength));


	listWall.push_back(new Wall(6 * gridLength - width, height - 25 * gridLength));
	listWall.push_back(new Wall(10 * gridLength - width, height - 25 * gridLength));
	listWall.push_back(new Wall(11 * gridLength - width, height - 25 * gridLength));
	listWall.push_back(new Wall(12 * gridLength - width, height - 25 * gridLength));
	listWall.push_back(new Wall(13 * gridLength - width, height - 25 * gridLength));
	listWall.push_back(new Wall(15 * gridLength - width, height - 25 * gridLength));
	listWall.push_back(new Wall(18 * gridLength - width, height - 25 * gridLength));
	listWall.push_back(new Wall(20 * gridLength - width, height - 25 * gridLength));
	listWall.push_back(new Wall(24 * gridLength - width, height - 25 * gridLength));


	listWall.push_back(new Wall(4 * gridLength - width, height - 27 * gridLength));
	listWall.push_back(new Wall(5 * gridLength - width, height - 27 * gridLength));
	listWall.push_back(new Wall(6 * gridLength - width, height - 27 * gridLength));
	listWall.push_back(new Wall(7 * gridLength - width, height - 27 * gridLength));
	listWall.push_back(new Wall(9 * gridLength - width, height - 27 * gridLength));
	listWall.push_back(new Wall(12 * gridLength - width, height - 27 * gridLength));
	listWall.push_back(new Wall(14 * gridLength - width, height - 27 * gridLength));
	listWall.push_back(new Wall(15 * gridLength - width, height - 27 * gridLength));
	listWall.push_back(new Wall(16 * gridLength - width, height - 27 * gridLength));
	listWall.push_back(new Wall(18 * gridLength - width, height - 27 * gridLength));
	listWall.push_back(new Wall(19 * gridLength - width, height - 27 * gridLength));
	listWall.push_back(new Wall(20 * gridLength - width, height - 27 * gridLength));
	listWall.push_back(new Wall(21 * gridLength - width, height - 27 * gridLength));
	listWall.push_back(new Wall(22 * gridLength - width, height - 27 * gridLength));
	listWall.push_back(new Wall(25 * gridLength - width, height - 27 * gridLength));
	listWall.push_back(new Wall(26 * gridLength - width, height - 27 * gridLength));


	listWall.push_back(new Wall(4 * gridLength - width, height - 28 * gridLength));
	listWall.push_back(new Wall(9 * gridLength - width, height - 28 * gridLength));
	listWall.push_back(new Wall(12 * gridLength - width, height - 28 * gridLength));
	listWall.push_back(new Wall(15 * gridLength - width, height - 28 * gridLength));
	listWall.push_back(new Wall(20 * gridLength - width, height - 28 * gridLength));
	listWall.push_back(new Wall(24 * gridLength - width, height - 28 * gridLength));
	listWall.push_back(new Wall(27 * gridLength - width, height - 28 * gridLength));



	listWall.push_back(new Wall(4 * gridLength - width, height - 29 * gridLength));
	listWall.push_back(new Wall(5 * gridLength - width, height - 29 * gridLength));
	listWall.push_back(new Wall(6 * gridLength - width, height - 29 * gridLength));
	listWall.push_back(new Wall(10 * gridLength - width, height - 29 * gridLength));
	listWall.push_back(new Wall(11 * gridLength - width, height - 29 * gridLength));
	listWall.push_back(new Wall(15 * gridLength - width, height - 29 * gridLength));
	listWall.push_back(new Wall(20 * gridLength - width, height - 29 * gridLength));
	listWall.push_back(new Wall(25 * gridLength - width, height - 29 * gridLength));
	listWall.push_back(new Wall(26 * gridLength - width, height - 29 * gridLength));


	listWall.push_back(new Wall(4 * gridLength - width, height - 30 * gridLength));
	listWall.push_back(new Wall(9 * gridLength - width, height - 30 * gridLength));
	listWall.push_back(new Wall(12 * gridLength - width, height - 30 * gridLength));
	listWall.push_back(new Wall(15 * gridLength - width, height - 30 * gridLength));
	listWall.push_back(new Wall(20 * gridLength - width, height - 30 * gridLength));
	listWall.push_back(new Wall(24 * gridLength - width, height - 30 * gridLength));
	listWall.push_back(new Wall(27 * gridLength - width, height - 30 * gridLength));


	listWall.push_back(new Wall(4 * gridLength - width, height - 31 * gridLength));
	listWall.push_back(new Wall(5 * gridLength - width, height - 31 * gridLength));
	listWall.push_back(new Wall(6 * gridLength - width, height - 31 * gridLength));
	listWall.push_back(new Wall(7 * gridLength - width, height - 31 * gridLength));
	listWall.push_back(new Wall(9 * gridLength - width, height - 31 * gridLength));
	listWall.push_back(new Wall(12 * gridLength - width, height - 31 * gridLength));
	listWall.push_back(new Wall(14 * gridLength - width, height - 31 * gridLength));
	listWall.push_back(new Wall(15 * gridLength - width, height - 31 * gridLength));
	listWall.push_back(new Wall(16 * gridLength - width, height - 31 * gridLength));
	listWall.push_back(new Wall(20 * gridLength - width, height - 31 * gridLength));
	listWall.push_back(new Wall(25 * gridLength - width, height - 31 * gridLength));
	listWall.push_back(new Wall(26 * gridLength - width, height - 31 * gridLength));





    
    for (y = - height; y < height; y += gridLength)
    {
        
        for (x = -width ; x < width; x += gridLength)
        {
            listEmpty.push_back (new EmptySpace (x, y));
        }
        
    }

    
    /* create enemies */
    for (int i = 0; i < 1; i++)
    {
        listEnemy.push_back(new Enemy(300, 300, (enum Direction)(rand () % 4), GLOBAL_GRID_LENGTH, GLOBAL_GRID_LENGTH, 1));
        listEnemy.push_back(new Enemy(350, 250, (enum Direction)(rand () % 4), GLOBAL_GRID_LENGTH, GLOBAL_GRID_LENGTH, 1));
    }
    
    /* create items */
    listItem.push_back(new Item(-100, 300, TWO));
    
    
}

void Map::display()
{
    
    for (std::list<EmptySpace*>::iterator it = listEmpty.begin(); it != listEmpty.end(); it++)
        (*it)->display();
    
    for (std::list<Wall*>::iterator it = listWall.begin(); it != listWall.end(); it++)
        (*it)->display();
    
    
    for (std::list<Enemy*>::iterator it = listEnemy.begin(); it != listEnemy.end(); it++)
        (*it)->display();
    
    for (std::list<Item*>::iterator it = listItem.begin(); it != listItem.end(); it++)
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

void Map::checkItem(Player * player)
{

    std::list<Item*>::iterator it = listItem.begin();
    
    while (it != listItem.end ())
    {
        if (CheckCollision(player->getPos(), (*it)->getPos()) != 0)
        {
            Item *tmp = NULL;
            tmp = *it;

            it = listItem.erase(it);
         

            player->addItem (tmp);
        }
        else it++;
    }
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

void Map::checkWallWeapon(std::list<Weapon*> l)
{
    if (l.empty())
    {
        return;
    }
    
    for (std::list<Weapon*>::iterator it = l.begin(); it != l.end(); it++)
    {
        
        for (std::list<Wall*>::iterator itWall = listWall.begin(); itWall != listWall.end(); itWall++)
        {
            unsigned int colBit = 0;
            colBit = CheckCollisionWeapon((*it)->getPos(), (*itWall)->getPos());
            
            if (colBit != 0)
            {
                (*it)->killed();
            }
        }
    }
}
void Map::checkEnemyKill (std::list<Weapon*> l)
{
    if (l.empty())
    {
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
     
     while (it != l.end ())0
     {
     if ((*it)->getStatus() == KILLED)
     {00000
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
            itEnemy = listEnemy.erase(itEnemy);
            
            delete tmp;
        }
        else itEnemy++;
    }
}
