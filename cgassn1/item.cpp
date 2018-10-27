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

	float colors[4] = { 0.0, 0.0, 1.0, 1.0 };
	float points[8] = {
		pos.x, pos.y,
		pos.x, pos.y + height,
		pos.x + width, pos.y + height,
		pos.x + width, pos.y
	};

	// Create a buffer
	glGenBuffers(1, &buffer);

	// Bind the buffer to vertx attributes
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	// Init buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0,
		sizeof(points), points);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(points),
		sizeof(colors), colors);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	unsigned int loc = glGetAttribLocation(shaderUtil.getProgram(), "position");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	unsigned int loc2 = glGetAttribLocation(shaderUtil.getProgram(), "color_in");
	glEnableVertexAttribArray(loc2);
	glVertexAttribPointer(loc2, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points)));


	glBindVertexArray(VAO);
	glDrawArrays(GL_QUADS, 0, 4);

	/*
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_QUADS);

	glVertex2f(pos.x, pos.y);

	glVertex2f(pos.x, pos.y + height);

	glVertex2f(pos.x + width, pos.y + height);


	glVertex2f(pos.x + width, pos.y);
	glEnd();
	*/

}

void Item::displayBox(float x, float y, int idx)
{
    
    float ItemX;
    float ItemY;
    
    ItemX = x + (idx % 3) * width;
    ItemY = y + (idx / 3) * height;


	float colors[4] = { 0.0, 0.0, 1.0, 1.0 };
	float points[8] = {
		ItemX, ItemY,
		ItemX, ItemY + height,
		ItemX + width, ItemY + height,
		ItemX + width, ItemY
	};

	// Create a buffer
	glGenBuffers(1, &buffer);

	// Bind the buffer to vertx attributes
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	// Init buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0,
		sizeof(points), points);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(points),
		sizeof(colors), colors);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	unsigned int loc = glGetAttribLocation(shaderUtil.getProgram(), "position");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	unsigned int loc2 = glGetAttribLocation(shaderUtil.getProgram(), "color_in");
	glEnableVertexAttribArray(loc2);
	glVertexAttribPointer(loc2, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points)));


	glBindVertexArray(VAO);
	glDrawArrays(GL_QUADS, 0, 4);

	/*
    glColor3f(0.0, 0.0, 1.0);
    
    glBegin(GL_QUADS);
    

    glVertex2f(ItemX, ItemY);

    glVertex2f(ItemX, ItemY + height);
    
    glVertex2f(ItemX + width, ItemY + height);
    
    glVertex2f(ItemX + width, ItemY);
    glEnd();
	*/
}

enum ItemType Item::getType ()
{
    return type;
}

Item::~Item ()
{
}
