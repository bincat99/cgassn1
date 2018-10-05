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

	bl[0] = new BmpLoader("brick.bmp");
}

position Wall::getPos()
{
    return pos;
}

void Wall::display()
{
//    glEnable(GL_TEXTURE_2D);
//    LoadTexture(0);
//    glColor3f(1.0, 1.0, 1.0);
//    glBegin(GL_QUADS);
//
//    glTexCoord2f(0.0, 0.0); // Need to check
//    glVertex2f(pos.x, pos.y);
//    glTexCoord2f(0.0, 1.0);
//    glVertex2f(pos.x, pos.y + height);
//
//    glTexCoord2f(1.0, 1.0);
//    glVertex2f(pos.x + width, pos.y + height);
//
//
//    glTexCoord2f(1.0, 0.0);
//    glVertex2f(pos.x + width, pos.y);
//    glEnd();
    glColor3f (0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(pos.x, pos.y);
    glVertex2f(pos.x, pos.y + height);
    glVertex2f(pos.x + width, pos.y + height);
    glVertex2f(pos.x + width, pos.y);
    glEnd();
}

void
Wall::LoadTexture(unsigned int idx)
{
	BmpLoader * tmp = bl[idx];

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, tmp->iWidth, tmp->iHeight, GL_RGB, GL_UNSIGNED_BYTE, tmp->textureData);
}
