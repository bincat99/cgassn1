//
//  item.cpp
//  cgassn1
//
//  Created by Dahun Lee on 2018. 10. 4..
//  Copyright © 2018년 Dahun Lee. All rights reserved.
//

#include "util.h"
#include "item.h"


Item::Item (float x, float y, enum ItemType type)
{
    pos.x = x;
    pos.y = y;
    width = GLOBAL_GRID_LENGTH;
    height = GLOBAL_GRID_LENGTH;
    type = type;
    
}

position Item::getPos ()
{
    return pos;
}

void Item::display()
{
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(pos.x, pos.y);
    glVertex2f(pos.x, pos.y + height);
    glVertex2f(pos.x + width, pos.y + height);
    glVertex2f(pos.x + width, pos.y);
    glEnd();
}

Item::~Item ()
{
    //printf ("used!\n");
}
