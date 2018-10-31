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

	float colors[16] = { 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0 };
	float points[8] = {
		0, 0,
		0, 0 + h,
		0 + w, 0 + h,
		0 + w, 0
	};

	glGenVertexArrays(1, &VAO_weapon);
	glBindVertexArray(VAO_weapon);

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

void Weapon::display(void)
{
    if (status == ALIVE)
    {

		view = temp;
		view = glm::transpose(glm::translate(glm::transpose(view), glm::vec3(pos.x, pos.y, 0)));
		model = glm::mat4(1.0f);
		glBindVertexArray(VAO_weapon);
		glUniformMatrix4fv(matrix_loc, 1, GL_TRUE, value_ptr(view));
		glUniformMatrix4fv(matrix_loc2, 1, GL_TRUE, value_ptr(model));
		glDrawArrays(GL_QUADS, 0, 4);
		glBindVertexArray(0);


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
