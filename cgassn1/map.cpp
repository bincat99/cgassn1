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
    
    for (int x = 0; x < 32; x++)
        for (int y = 0; y < 32; y++)
        {
            objMap[x][y] = EMPTY;
        }
    
    for (int x = 0; x < 32; x++)
    {
        objMap[x][0] = SAFE;
        objMap[0][x] = SAFE;
    }
    
    for (int x = 0; x < 5; x++)
        for (int y = 0; y < 5; y++)
        {
            objMap[x][y] = SAFE;
        }
    
    
    objMap[5][3] = WALL;
    objMap[6][3] = WALL;
    objMap[10][3] = WALL;
    objMap[11][3] = WALL;
    objMap[12][3] = WALL;
    objMap[14][3] = WALL;
    objMap[15][3] = WALL;
    objMap[16][3] = WALL;
    objMap[17][3] = WALL;
    objMap[19][3] = WALL;
    objMap[20][3] = WALL;
    objMap[21][3] = WALL;
    objMap[4][4] = WALL;
    objMap[7][4] = WALL;
    objMap[9][4] = WALL;
    objMap[14][4] = WALL;
    objMap[19][4] = WALL;
    objMap[22][4] = WALL;
    objMap[4][5] = WALL;
    objMap[10][5] = WALL;
    objMap[11][5] = WALL;
    objMap[14][5] = WALL;
    objMap[15][5] = WALL;
    objMap[16][5] = WALL;
    objMap[19][5] = WALL;
    objMap[22][5] = WALL;
    objMap[4][6] = WALL;
    objMap[7][6] = WALL;
    objMap[12][6] = WALL;
    objMap[14][6] = WALL;
    objMap[19][6] = WALL;
    objMap[22][6] = WALL;
    objMap[5][7] = WALL;
    objMap[6][7] = WALL;
    objMap[9][7] = WALL;
    objMap[10][7] = WALL;
    objMap[11][7] = WALL;
    objMap[14][7] = WALL;
    objMap[15][7] = WALL;
    objMap[16][7] = WALL;
    objMap[17][7] = WALL;
    objMap[19][7] = WALL;
    objMap[20][7] = WALL;
    objMap[21][7] = WALL;
    objMap[6][9] = WALL;
    objMap[9][9] = WALL;
    objMap[10][9] = WALL;
    objMap[11][9] = WALL;
    objMap[12][9] = WALL;
    objMap[15][9] = WALL;
    objMap[5][10] = WALL;
    objMap[6][10] = WALL;
    objMap[9][10] = WALL;
    objMap[14][10] = WALL;
    objMap[15][10] = WALL;
    objMap[4][11] = WALL;
    objMap[6][11] = WALL;
    objMap[9][11] = WALL;
    objMap[10][11] = WALL;
    objMap[11][11] = WALL;
    objMap[15][11] = WALL;
    objMap[4][12] = WALL;
    objMap[5][12] = WALL;
    objMap[6][12] = WALL;
    objMap[7][12] = WALL;
    objMap[12][12] = WALL;
    objMap[15][12] = WALL;
    objMap[6][13] = WALL;
    objMap[9][13] = WALL;
    objMap[10][13] = WALL;
    objMap[11][13] = WALL;
    objMap[14][13] = WALL;
    objMap[15][13] = WALL;
    objMap[16][13] = WALL;
    objMap[5][15] = WALL;
    objMap[6][15] = WALL;
    objMap[10][15] = WALL;
    objMap[11][15] = WALL;
    objMap[12][15] = WALL;
    objMap[15][15] = WALL;
    objMap[16][15] = WALL;
    objMap[17][15] = WALL;
    objMap[19][15] = WALL;
    objMap[22][15] = WALL;
    objMap[25][15] = WALL;
    objMap[4][16] = WALL;
    objMap[7][16] = WALL;
    objMap[9][16] = WALL;
    objMap[14][16] = WALL;
    objMap[19][16] = WALL;
    objMap[20][16] = WALL;
    objMap[22][16] = WALL;
    objMap[24][16] = WALL;
    objMap[25][16] = WALL;
    objMap[4][17] = WALL;
    objMap[5][17] = WALL;
    objMap[6][17] = WALL;
    objMap[7][17] = WALL;
    objMap[10][17] = WALL;
    objMap[11][17] = WALL;
    objMap[15][17] = WALL;
    objMap[16][17] = WALL;
    objMap[19][17] = WALL;
    objMap[21][17] = WALL;
    objMap[22][17] = WALL;
    objMap[25][17] = WALL;
    objMap[4][18] = WALL;
    objMap[7][18] = WALL;
    objMap[12][18] = WALL;
    objMap[17][18] = WALL;
    objMap[19][18] = WALL;
    objMap[22][18] = WALL;
    objMap[25][18] = WALL;
    objMap[4][19] = WALL;
    objMap[7][19] = WALL;
    objMap[9][19] = WALL;
    objMap[10][19] = WALL;
    objMap[11][19] = WALL;
    objMap[14][19] = WALL;
    objMap[15][19] = WALL;
    objMap[16][19] = WALL;
    objMap[19][19] = WALL;
    objMap[22][19] = WALL;
    objMap[24][19] = WALL;
    objMap[25][19] = WALL;
    objMap[26][19] = WALL;
    objMap[4][21] = WALL;
    objMap[5][21] = WALL;
    objMap[6][21] = WALL;
    objMap[7][21] = WALL;
    objMap[8][21] = WALL;
    objMap[10][21] = WALL;
    objMap[11][21] = WALL;
    objMap[12][21] = WALL;
    objMap[13][21] = WALL;
    objMap[16][21] = WALL;
    objMap[17][21] = WALL;
    objMap[20][21] = WALL;
    objMap[24][21] = WALL;
    objMap[6][22] = WALL;
    objMap[10][22] = WALL;
    objMap[15][22] = WALL;
    objMap[18][22] = WALL;
    objMap[20][22] = WALL;
    objMap[21][22] = WALL;
    objMap[23][22] = WALL;
    objMap[24][22] = WALL;
    objMap[6][23] = WALL;
    objMap[10][23] = WALL;
    objMap[11][23] = WALL;
    objMap[12][23] = WALL;
    objMap[15][23] = WALL;
    objMap[16][23] = WALL;
    objMap[17][23] = WALL;
    objMap[18][23] = WALL;
    objMap[20][23] = WALL;
    objMap[22][23] = WALL;
    objMap[24][23] = WALL;
    objMap[6][24] = WALL;
    objMap[10][24] = WALL;
    objMap[15][24] = WALL;
    objMap[18][24] = WALL;
    objMap[20][24] = WALL;
    objMap[24][24] = WALL;
    objMap[6][25] = WALL;
    objMap[10][25] = WALL;
    objMap[11][25] = WALL;
    objMap[12][25] = WALL;
    objMap[13][25] = WALL;
    objMap[15][25] = WALL;
    objMap[18][25] = WALL;
    objMap[20][25] = WALL;
    objMap[24][25] = WALL;
    objMap[4][27] = WALL;
    objMap[5][27] = WALL;
    objMap[6][27] = WALL;
    objMap[7][27] = WALL;
    objMap[9][27] = WALL;
    objMap[12][27] = WALL;
    objMap[14][27] = WALL;
    objMap[15][27] = WALL;
    objMap[16][27] = WALL;
    objMap[18][27] = WALL;
    objMap[19][27] = WALL;
    objMap[20][27] = WALL;
    objMap[21][27] = WALL;
    objMap[22][27] = WALL;
    objMap[25][27] = WALL;
    objMap[26][27] = WALL;
    objMap[4][28] = WALL;
    objMap[9][28] = WALL;
    objMap[12][28] = WALL;
    objMap[15][28] = WALL;
    objMap[20][28] = WALL;
    objMap[24][28] = WALL;
    objMap[27][28] = WALL;
    objMap[4][29] = WALL;
    objMap[5][29] = WALL;
    objMap[6][29] = WALL;
    objMap[10][29] = WALL;
    objMap[11][29] = WALL;
    objMap[15][29] = WALL;
    objMap[20][29] = WALL;
    objMap[25][29] = WALL;
    objMap[26][29] = WALL;
    objMap[4][30] = WALL;
    objMap[9][30] = WALL;
    objMap[12][30] = WALL;
    objMap[15][30] = WALL;
    objMap[20][30] = WALL;
    objMap[24][30] = WALL;
    objMap[27][30] = WALL;
    objMap[4][31] = WALL;
    objMap[5][31] = WALL;
    objMap[6][31] = WALL;
    objMap[7][31] = WALL;
    objMap[9][31] = WALL;
    objMap[12][31] = WALL;
    objMap[14][31] = WALL;
    objMap[15][31] = WALL;
    objMap[16][31] = WALL;
    objMap[20][31] = WALL;
    objMap[25][31] = WALL;
    objMap[26][31] = WALL;
    
    /* create enemies */
    //    for (int i = 0; i < 1; i++)
    //    {
    //        listEnemy.push_back(new Enemy(300, 300, (enum Direction)(rand () % 4), GLOBAL_GRID_LENGTH, GLOBAL_GRID_LENGTH, 1));
    //        listEnemy.push_back(new Enemy(350, 250, (enum Direction)(rand () % 4), GLOBAL_GRID_LENGTH, GLOBAL_GRID_LENGTH, 1));
    //    }
    
    int enemyNum = 0;
    
    while (enemyNum < 20)
    {
        int x, y;
        x = rand() % 32;
        y = rand() % 32;
        
        if (objMap[x][y] == EMPTY)
        {
            objMap[x][y] = ENEMY;
            enemyNum ++;
        }
    }
    
    int itemNum = 0;
    while (itemNum < 10)
    {
        int x, y;
        x = rand() % 32;
        y = rand() % 32;
        
        if (objMap[x][y] == EMPTY)
        {
            objMap[x][y] = ITEM;
            itemNum ++;
        }
    }
    
    
    for (int x = 0; x < 32; x++)
        for (int y = 0; y < 32; y++)
        {
            switch (objMap[x][y])
            {
                case WALL:
                    listWall.push_back(new Wall(x * gridLength - width, height - y * gridLength));
                    break;
                case ENEMY:
                    listEnemy.push_back(new Enemy(x * gridLength - width, height - y * gridLength,
                                                  (enum Direction)(rand () % 4), GLOBAL_GRID_LENGTH, GLOBAL_GRID_LENGTH, 1));
                    break;
                case ITEM:
                    listItem.push_back(new Item(x * gridLength - width, height - y * gridLength,
                                                (enum ItemType)(rand () % 2)));
                    break;
                    
                default:
                    break;
            }
        }
}

void Map::display()
{
    
    for (std::list<EmptySpace*>::iterator it = listEmpty.begin(); it != listEmpty.end(); it++)
        (*it)->display();
    
    for (std::list<Wall*>::iterator it = listWall.begin(); it != listWall.end(); it++)
        (*it)->display();
    
    
    for (std::list<Item*>::iterator it = listItem.begin(); it != listItem.end(); it++)
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

void Map::checkItem(Player * player)
{
    
    std::list<Item*>::iterator it = listItem.begin();
    
    while (it != listItem.end ())
    {
        if (CheckCollision(player->getPos(), (*it)->getPos()) != 0 && player->getItemNum() < 6)
        {
            Item *tmp = NULL;
            tmp = *it;
            
            
            it = listItem.erase(it);
            
            player->addItem (tmp);
        }
        else
            it++;
    }
}

void Map::checkPlayerKill(Player * player)
{
    std::list<Enemy*>::iterator it = listEnemy.begin();
    
    while (it != listEnemy.end ())
    {
        if (CheckCollision(player->getPos(), (*it)->getPos()) != 0)
        {
            
            player->killed();
        }
        it++;
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
    
    if (listEnemy.empty())
    {
        gameClear = true;
    }
}

Map::~Map()
{
    
}
