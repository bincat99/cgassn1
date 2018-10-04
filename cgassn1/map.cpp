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
        
        
//        glBegin (GL_QUAD_STRIP);
//        //glVertex3f(x, y, .0);
//
        for (x = -width ; x < width; x += gridLength)
        {
            listEmpty.push_back (new EmptySpace (x, y));
        }
//        glVertex2f(width, y);
//        glVertex2f(width, y+ gridLength);
//        glEnd();
    }
    
    for (int i = 0; i < 1; i++)
    {
        listEnemy.push_back(new Enemy(300, 300, UP, GLOBAL_GRID_LENGTH, GLOBAL_GRID_LENGTH, 1));
    }
}

void Map::display()
{
    float x, y;

  
    

//    for (y = - height; y < height; y += gridLength)
//    {
//
//
//        glBegin (GL_QUAD_STRIP);
//        //glVertex3f(x, y, .0);
//
//        for (x = -width ; x < width; x += gridLength)
//        {
//            glColor3f(0 , 0, 1.0);
//            glVertex2f(x, y);
//            glVertex2f(x, y + gridLength);
//        }
//        glVertex2f(width, y);
//        glVertex2f(width, y+ gridLength);
//        glEnd();
//    }
    
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
    if (colBit != 0) printf ("%d\n", colBit);
    colSide[LEFT] = colBit & COL_LEFT;
    colSide[UP] = colBit & COL_UP;
    colSide[RIGHT] = colBit & COL_RIGHT;
    colSide[DOWN] = colBit & COL_DOWN;
    
    player->checkWall (colSide);
}


void Map::moveEnemy (position playerPos)
{
    for (std::list<Enemy*>::iterator it = listEnemy.begin(); it != listEnemy.end(); it++)
        (*it)->move(playerPos.x, playerPos.y);
}
