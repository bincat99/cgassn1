//
//  item.cpp
//  cgassn1
//
//  Created by Dahun Lee on 2018. 10. 4..
//  Copyright © 2018년 Dahun Lee. All rights reserved.
//

#include "util.h"
#include "item.h"
#include <iostream>

Item::Item (float x, float y, enum ItemType type_)
{
    pos.x = x;
    pos.y = y;
    width = GLOBAL_GRID_LENGTH;
    height = GLOBAL_GRID_LENGTH;
    type = type_;



	float colors[16] = { 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0 };
	float points[8] = {
		0, 0,
		0, height,
		width, height,
		width, 0
	};

	glGenVertexArrays(1, &VAO_item);
	glBindVertexArray(VAO_item);

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

	unsigned int loc = glGetAttribLocation(shaderUtil.getProgram(), "position");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	unsigned int loc2 = glGetAttribLocation(shaderUtil.getProgram(), "color_in");
	glEnableVertexAttribArray(loc2);
	glVertexAttribPointer(loc2, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points)));
	glBindVertexArray(0);

}

position Item::getPos ()
{
    return pos;
}

void Item::display()
{

	view = temp;
	view = glm::transpose(glm::translate(glm::transpose(view), glm::vec3(pos.x, pos.y, 0)));
	model = glm::mat4(1.0f);
	glBindVertexArray(VAO_item);
	glUniformMatrix4fv(matrix_loc, 1, GL_TRUE, value_ptr(view));
	glUniformMatrix4fv(matrix_loc2, 1, GL_TRUE, value_ptr(model));
	glDrawArrays(GL_QUADS, 0, 4);
	glBindVertexArray(0);

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

	view = temp;
	view = glm::transpose(glm::translate(glm::transpose(view), glm::vec3(ItemX, ItemY, 0)));
	model = glm::mat4(1.0f);
	glBindVertexArray(VAO_item);
	glUniformMatrix4fv(matrix_loc, 1, GL_TRUE, value_ptr(view));
	glUniformMatrix4fv(matrix_loc2, 1, GL_TRUE, value_ptr(model));
	glDrawArrays(GL_QUADS, 0, 4);
	glBindVertexArray(0);

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
