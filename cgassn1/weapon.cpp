#include "weapon.h"
#include "util.h"
#include <stdio.h>
Weapon::Weapon(float x_, float y_, enum Direction dir_, float w_, float h_, float speed_, float range_)
{

    dir = dir_;
    w = w_;
    h = h_;
    pos.x = x_;
    pos.y = y_;
    speed = speed_;
    range = range_;
    status = ALIVE;
}

void Weapon::display(void)
{
    if (status == ALIVE)
    {

		float colors[4] = { 0.0, 0.0, 0.0, 1.0 };
		float points[8] = {
			pos.x, pos.y,
			pos.x, pos.y + h,
			pos.x + w, pos.y + h,
			pos.x + w, pos.y
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
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);

		glVertex2f(pos.x, pos.y);
		glVertex2f(pos.x, pos.y + h);

		glVertex2f(pos.x + w, pos.y + h);
		glVertex2f(pos.x + w, pos.y);
		glEnd();
		*/

    }
}

void Weapon::move(void)
{
    if (status == ALIVE)
    {
        if (range > 0)
        {
            switch ((enum Direction) dir)
            {
                case UP:
                    if (!isWall[1])
                    {
                        pos.y += speed;
                        range -= speed;
                    }
                    else
                    {
                        status = KILLED;
                    }
                    break;
                case DOWN:
                    if (!isWall[3])
                    {
                        pos.y -= speed;
                        range -= speed;
                    }
                    else
                    {
                        status = KILLED;
                    }
                    break;
                case LEFT:
                    if (!isWall[0])
                    {
                        pos.x -= speed;
                        range -= speed;
                    }
                    else
                    {
                        status = KILLED;
                    }
                    break;
                case RIGHT:
                    if (!isWall[2])
                    {
                        pos.x += speed;
                        range -= speed;
                    }
                    else
                    {
                        status = KILLED;
                    }
                    break;
            }
        }
        else
        {
            status = KILLED;
        }
    }
}

void Weapon::killed()
{
    status = KILLED;
}

void Weapon::checkWall(bool isWall_[4])
{
    isWall[0] = isWall_[0];
    isWall[1] = isWall_[1];
    isWall[2] = isWall_[2];
    isWall[3] = isWall_[3];
}

enum Status Weapon::getStatus ()
{
    return status;
}


Weapon::~Weapon()
{
}

position Weapon::getPos()
{
    return pos;
}
