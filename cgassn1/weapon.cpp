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

	bl[LEFT] = new BmpLoader("featherl.bmp");

	bl[UP] = new BmpLoader("featheru.bmp");

	bl[RIGHT] = new BmpLoader("featherr.bmp");

	bl[DOWN] = new BmpLoader("featherd.bmp");
}

void Weapon::display(void)
{
    if (status == ALIVE)
    {
		glEnable(GL_TEXTURE_2D);
		LoadTexture(dir + sprite);
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);

		glTexCoord2f(0.0, 0.0); // Need to check
		glVertex2f(pos.x, pos.y);
		glTexCoord2f(0.0, 1.0);
		glVertex2f(pos.x, pos.y + h);

		glTexCoord2f(1.0, 1.0);
		glVertex2f(pos.x + w, pos.y + h);


		glTexCoord2f(1.0, 0.0);
		glVertex2f(pos.x + w, pos.y);
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


void
Weapon::LoadTexture(unsigned int idx)
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