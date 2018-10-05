//
//  item.cpp
//  cgassn1
//
//  Created by Dahun Lee on 2018. 10. 4..
//  Copyright © 2018년 Dahun Lee. All rights reserved.
//

#include "util.h"
#include "item.h"


Item::Item (float x, float y, enum ItemType type_)
{
    pos.x = x;
    pos.y = y;
    width = GLOBAL_GRID_LENGTH;
    height = GLOBAL_GRID_LENGTH;
    type = type_;


	bl[0] = new BmpLoader("item0.bmp");
	bl[1] = new BmpLoader("item1.bmp");

}

position Item::getPos ()
{
    return pos;
}

void Item::display()
{

	glEnable(GL_TEXTURE_2D);
	LoadTexture(type);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0, 0.0); // Need to check
	glVertex2f(pos.x, pos.y);
	glTexCoord2f(0.0, 1.0);
	glVertex2f(pos.x, pos.y + height);

	glTexCoord2f(1.0, 1.0);
	glVertex2f(pos.x + width, pos.y + height);


	glTexCoord2f(1.0, 0.0);
	glVertex2f(pos.x + width, pos.y);
	glEnd();
}

void Item::LoadTexture(unsigned int idx)
{
	BmpLoader * tmp = bl[idx];

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, tmp->iWidth, tmp->iHeight, GL_RGB, GL_UNSIGNED_BYTE, tmp->textureData);
}

Item::~Item ()
{
    //printf ("used!\n");
}
