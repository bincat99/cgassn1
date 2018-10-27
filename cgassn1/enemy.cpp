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
}

void Enemy::display()
{
    if (status == ALIVE) {
		sprite = (sprite + 1) % 4;

		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_QUADS);

		glVertex2f(pos.x, pos.y);

		glVertex2f(pos.x, pos.y + h);

		glVertex2f(pos.x + w, pos.y + h);

		glVertex2f(pos.x + w, pos.y);
		glEnd();

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

