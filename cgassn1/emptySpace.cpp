//
//  emptySpace.cpp
//  cgassn1
//
//  Created by Dahun Lee on 2018. 10. 4..
//  Copyright © 2018년 Dahun Lee. All rights reserved.
//


#include "emptySpace.h"



EmptySpace::EmptySpace (float x, float y)
{
    pos.x = x;
    pos.y = y;
    width = GLOBAL_GRID_LENGTH;
    height = GLOBAL_GRID_LENGTH;
}


position EmptySpace::getPos()
{
    return pos;
}

void EmptySpace::display()
{
    glColor3f (1.0, 1.0, 1.);
    glBegin(GL_POLYGON);
    glVertex2f(pos.x, pos.y);
    glVertex2f(pos.x, pos.y + height);
    glVertex2f(pos.x + width, pos.y + height);
    glVertex2f(pos.x + width, pos.y);
    glEnd();
}
