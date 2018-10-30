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

	//bl[0] = new BmpLoader("brick.bmp");

	float colors[16] = { 0.0, 0.0, 0.0, 1.0 , 0.0, 0.0, 0.0, 1.0 , 0.0, 0.0, 0.0, 1.0 , 0.0, 0.0, 0.0, 1.0 };
	float points[8] = {
		0, 0,
		0, 0 + height,
		0 + width, 0 + height,
		0 + width, 0
	};

	glGenVertexArrays(1, &VAO_wall);
	glBindVertexArray(VAO_wall);

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

position Wall::getPos()
{
    return pos;
}

void Wall::display()
{

	ctm = temp;
	ctm = glm::transpose(glm::translate(glm::transpose(ctm), glm::vec3(pos.x, pos.y, 0)));
	glBindVertexArray(VAO_wall);
	glUniformMatrix4fv(matrix_loc, 1, GL_TRUE, value_ptr(ctm));
	glDrawArrays(GL_QUADS, 0, 4);
	glBindVertexArray(0);


	/*
	glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(pos.x, pos.y);
    glVertex2f(pos.x, pos.y + height);
    glVertex2f(pos.x + width, pos.y + height);
    glVertex2f(pos.x + width, pos.y);
    glEnd();
	*/
}

Wall::~Wall()
{
}

