//
//  enemy.cpp
//  cgassn1
//
//  Created by Dahun Lee on 2018. 10. 1..
//  Copyright © 2018년 Dahun Lee. All rights reserved.
//

#include "enemy.h"
#include "util.h"

#define abs(x) ((x) < 0 ? (-(x)): (x))

Enemy::Enemy (float x_, float y_, enum Direction dir_, float w_, float h_, float speed_)
{
    x = x_;
    y = y_;
    pos.x = x_;
    pos.y = y_;
    dir = dir_;
    w = w_;
    h = h_;
    speed = speed_;
    status = ALIVE;
    moveCount = 0;

	sprite = rand() % 3;

	float colors[16] = { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0 , 1.0, 0.0, 0.0, 0.0 , 1.0, 0.0, 0.0, 0.0 };
	float points[8] = {
		0, 0,
		0, h,
		w, h,
		w, 0
	};

	glGenVertexArrays(1, &VAO_enemy);
	glBindVertexArray(VAO_enemy);

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
void Enemy::drawSymetricParts(bool is_left, bool is_arm, int sprite, enum Direction dir) {

	int posX, posY;
	int refX, refY;
	float angle;

	if (is_arm && is_left) {
		posX = 12;
		posY = 35;
		refX = -1;
		refY = -1;
		angle = 1.0;
	}
	else if (!is_arm && is_left) {
		posX = 20;
		posY = 20;
		refX = -1;
		refY = -1;
		angle = 0.5;
	}
	else if (is_arm && !is_left) {
		posX = 38;
		posY = 35;
		refX = 1;
		refY = -1;
		angle = 1.0;
	}
	else if (!is_arm && !is_left) {
		posX = 30;
		posY = 20;
		refX = 1;
		refY = -1;
		angle = 0.5;
	}
	/********************/
	/* Draw upper Parts */
	/********************/
	view = temp;
	view = glm::transpose(glm::translate(glm::transpose(view), glm::vec3(pos.x, pos.y, 0)));

	glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), -1 * angle*refX*sprite*(3.14f / 3), glm::vec3(0.0, 0.0, 1.0));
	model = rotate * glm::transpose(glm::translate(glm::mat4(1.0f), glm::vec3(posX, posY, 0)));
	model_temp = model;
	model = glm::scale(glm::mat4(1.0f), glm::vec3(refX*0.2, refY*0.2, 1.0)) * model;


	glBindVertexArray(VAO_enemy);
	glUniformMatrix4fv(matrix_loc, 1, GL_TRUE, value_ptr(view));
	glUniformMatrix4fv(matrix_loc2, 1, GL_TRUE, value_ptr(model));
	glDrawArrays(GL_QUADS, 0, 4);
	glBindVertexArray(0);


	/********************/
	/* Draw lower Parts */
	/********************/
	view = temp;
	view = glm::transpose(glm::translate(glm::transpose(view), glm::vec3(pos.x, pos.y, 0)));

	glm::mat4 rotate2 = glm::rotate(glm::mat4(1.0f), -1 * angle*refX*sprite*(3.14f / 6), glm::vec3(0.0, 0.0, 1.0));
	model = rotate2 * glm::transpose(glm::translate(glm::mat4(1.0f), glm::vec3(0, -10, 0)))  * model_temp;
	model_temp = model;
	model = glm::scale(glm::mat4(1.0f), glm::vec3(refX*0.1, refY*0.2, 1.0)) * model;

	glBindVertexArray(VAO_enemy);
	glUniformMatrix4fv(matrix_loc, 1, GL_TRUE, value_ptr(view));
	glUniformMatrix4fv(matrix_loc2, 1, GL_TRUE, value_ptr(model));
	glDrawArrays(GL_QUADS, 0, 4);
	glBindVertexArray(0);

	/*************************/
	/* Draw the lowest Parts */
	/*************************/
	view = temp;
	view = glm::transpose(glm::translate(glm::transpose(view), glm::vec3(pos.x, pos.y, 0)));


	model = glm::transpose(glm::translate(glm::mat4(1.0f), glm::vec3(0, -10, 0)))  * model_temp;
	model_temp = model;
	model = glm::scale(glm::mat4(1.0f), glm::vec3(refX*0.2, refY*0.1, 1.0)) * model;

	glBindVertexArray(VAO_enemy);
	glUniformMatrix4fv(matrix_loc, 1, GL_TRUE, value_ptr(view));
	glUniformMatrix4fv(matrix_loc2, 1, GL_TRUE, value_ptr(model));
	glDrawArrays(GL_QUADS, 0, 4);
	glBindVertexArray(0);


}
void Enemy::display()
{
    if (status == ALIVE) {
		if (frame % 60 == 0)
			sprite = (sprite + 1) % 3;
		frame++;


		/*************/
		/* Draw Head */
		/*************/
		view = temp;
		view = glm::transpose(glm::translate(glm::transpose(view), glm::vec3(pos.x, pos.y, 0)));

		model = glm::scale(glm::mat4(1.0f), glm::vec3(0.2, 0.2, 1.0)) * glm::transpose(glm::translate(glm::mat4(1.0f), glm::vec3(20, 40, 0)));

		glBindVertexArray(VAO_enemy);
		glUniformMatrix4fv(matrix_loc, 1, GL_TRUE, value_ptr(view));
		glUniformMatrix4fv(matrix_loc2, 1, GL_TRUE, value_ptr(model));
		glDrawArrays(GL_QUADS, 0, 4);
		glBindVertexArray(0);


		/**************/
		/* Draw Torso */
		/**************/
		view = temp;
		view = glm::transpose(glm::translate(glm::transpose(view), glm::vec3(pos.x, pos.y, 0)));

		model = glm::scale(glm::mat4(1.0f), glm::vec3(0.6, 0.4, 1.0)) *glm::transpose(glm::translate(glm::mat4(1.0f), glm::vec3(10, 20, 0)));

		glBindVertexArray(VAO_enemy);
		glUniformMatrix4fv(matrix_loc, 1, GL_TRUE, value_ptr(view));
		glUniformMatrix4fv(matrix_loc2, 1, GL_TRUE, value_ptr(model));
		glDrawArrays(GL_QUADS, 0, 4);
		glBindVertexArray(0);

		drawSymetricParts(true, true, sprite, dir);
		drawSymetricParts(true, false, (sprite + 1) % 3, dir);
		drawSymetricParts(false, true, (sprite + 2) % 3, dir);
		drawSymetricParts(false, false, (sprite + 3) % 3, dir);

		/*/
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_QUADS);

		glVertex2f(pos.x, pos.y);

		glVertex2f(pos.x, pos.y + h);

		glVertex2f(pos.x + w, pos.y + h);

		glVertex2f(pos.x + w, pos.y);
		glEnd();*/

    }
}

void Enemy::move(float player_x, float player_y)
{
    if (status == ALIVE)
    {
        if (calDistance(player_x, player_y, pos.x, pos.y) < 250) // some condition to trace player
        {
            if (player_x >= pos.x)
            {
                if (!isWall[2])
                {
                    pos.x += speed*2;
                    dir = RIGHT;
                }
            }
            else {
                if (!isWall[0])
                {
                    pos.x -= speed*2;
                    dir = LEFT;
                }
            }
            
            if (player_y >= pos.y)
            {
                if (!isWall[UP])
                {
                    pos.y += speed*2;
					if (abs(player_x - pos.x) < abs(player_y - pos.y)) {
						dir = UP;

					}
                }
            }
            else
            {
                if (!isWall[DOWN])
                {
                    pos.y -= speed*2;
					if (abs(player_x - pos.x) < abs(player_y - pos.y)) {
						dir = DOWN;

					}
                }
            }
        }
        else
        {
            if (moveCount == 0)
            {
                dir = (enum Direction)(rand () % 4);
                moveCount = 30;
            }
            
            switch (dir)
            {
                case 0: // Left Up Right Down
                    if (!isWall[0])
                    {
                        pos.x -= speed;
                    }
                    break;
                case 1:
                    if (!isWall[1])
                    {
                        pos.y += speed;
                    }
                    break;
                case 2:
                    if (!isWall[2])
                    {
                        pos.x += speed;
                    }
                    break;
                case 3:
                    if (!isWall[3])
                    {
                        pos.y -= speed;
                    }
                    break;
            }
            moveCount --;
        }
    }
}

void Enemy::checkWall(bool isWall_[4])
{
    isWall[0] = isWall_[0];
    isWall[1] = isWall_[1];
    isWall[2] = isWall_[2];
    isWall[3] = isWall_[3];
}

void Enemy::killed()
{
    status = KILLED;
}

enum Status Enemy::getStatus ()
{
    return status;
}
Enemy::~Enemy()
{
}

void Enemy::cleanWall ()
{
    isWall[LEFT] = false;
    isWall[UP] = false;
    isWall[RIGHT] = false;
    isWall[DOWN] = false;
}

position Enemy::getPos()
{
    return pos;
}

