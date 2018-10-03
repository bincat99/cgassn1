//
//  map.cpp
//  cgassn1
//
//  Created by Dahun Lee on 2018. 10. 1..
//  Copyright © 2018년 Dahun Lee. All rights reserved.
//

#include "map.h"
#include <stdio.h>

Map::Map()
{

}

Map::Map (float w, float h, float g)
{
    width = w;
    height = h;
    gridLength = g;
}


void Map::mapInit()
{

}

void Map::display()
{
    float x, y;

    glColor3f(.0, .0, .0);
    

    for (y = 0.0; y < height; y += gridLength/100)
    {

  
        glBegin (GL_QUAD_STRIP);
        //glVertex3f(x, y, .0);
        for (x = 0.0; x < width; x += gridLength/100)
        {
            glVertex2f(x, y);
            glVertex2f(x, y + gridLength/100);
        }
        glVertex2f(width, y);
        glVertex2f(width, y+ gridLength);
        glEnd();
    }
    
}
