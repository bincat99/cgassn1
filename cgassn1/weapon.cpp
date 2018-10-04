#include "weapon.h"
#include "util.h"
#include <stdio.h>
Weapon::Weapon(float x_, float y_, enum Direction dir_, float w_, float h_, float speed_, float range_)
{
	x = x_;
	y = y_;
	dir = dir_;
	w = w_;
	h = h_;
	speed = speed_;
	range = range_;
	status = ALIVE;
}

void Weapon::display(void)
{
	if (status == ALIVE)
	{
		glBegin(GL_LINE_LOOP);
		glVertex2f(x, y);
		glVertex2f(x, y + h);
		glVertex2f(x + w, y + h);
		glVertex2f(x + w, y);
		glEnd();
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
					y += speed;
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
					y -= speed;
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
					x -= speed;
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
					x += speed;
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

