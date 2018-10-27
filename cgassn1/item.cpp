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



}

position Item::getPos ()
{
    return pos;
}

void Item::display()
{


	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_QUADS);

	glVertex2f(pos.x, pos.y);

	glVertex2f(pos.x, pos.y + height);

	glVertex2f(pos.x + width, pos.y + height);


	glVertex2f(pos.x + width, pos.y);
	glEnd();

}

void Item::displayBox(float x, float y, int idx)
{
    
    float ItemX;
    float ItemY;
    
    ItemX = x + (idx % 3) * width;
    ItemY = y + (idx / 3) * height;

    glColor3f(0.0, 0.0, 1.0);
    
    glBegin(GL_QUADS);
    

    glVertex2f(ItemX, ItemY);

    glVertex2f(ItemX, ItemY + height);
    
    glVertex2f(ItemX + width, ItemY + height);
    
    glVertex2f(ItemX + width, ItemY);
    glEnd();
}

enum ItemType Item::getType ()
{
    return type;
}

Item::~Item ()
{
}
