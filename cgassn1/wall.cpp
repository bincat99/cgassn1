//
//  wall.cpp
//  cgassn1
//
//  Created by Dahun Lee on 2018. 10. 1..
//  Copyright © 2018년 Dahun Lee. All rights reserved.
//

#include "wall.h"


Wall::Wall (float x, float y)
{
    pos.x = x;
    pos.y = y;
    width = GLOBAL_GRID_LENGTH;
    height = GLOBAL_GRID_LENGTH;
}

position Wall::getPos()
{
    return pos;
}

void Wall::display()
{
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(pos.x, pos.y);
    glVertex2f(pos.x, pos.y + height);
    glVertex2f(pos.x + width, pos.y + height);
    glVertex2f(pos.x + width, pos.y);
    glEnd();
}
