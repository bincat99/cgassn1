//
//  enemy.cpp
//  cgassn1
//
//  Created by Dahun Lee on 2018. 10. 1..
//  Copyright © 2018년 Dahun Lee. All rights reserved.
//

#include "enemy.h"

Enemy::Enemy (float x_, float y_, enum Direction dir_, float w_, float h_, float speed_)
{
	x = x_;
	y = y_;
	dir = dir_;
	w = w_;
	h = h_;
	speed = speed_;
	status = ALIVE;
}

void Enemy::display() {
	if (status == ALIVE) {
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(x, y);
		glVertex2f(x, y + h);
		glVertex2f(x + w, y + h);
		glVertex2f(x + w, y);
		glEnd();
	}
}

void Enemy::move(float player_x, float player_y) {
	if (status == ALIVE) {
		if (true) // some condition to trace player
		{
			if (player_x >= x) {
				if (!isWall[2]) {
					x += speed;
					dir = RIGHT;
				}
			}
			else {
				if (!isWall[0]) {
					x -= speed;
					dir = LEFT;
				}
			}

			if (player_y >= y) {
				if (!isWall[1]) {
					y += speed;
					dir = UP;
				}
			}
			else {
				if (!isWall[3]) {
					y -= speed;
					dir = DOWN;
				}
			}
		}
		else {
			int Idir = rand() % 4;

			switch (Idir) {
			case 0: // Left Up Right Down
				if (!isWall[0]) {
					dir = LEFT;
					x -= speed;
				}
				break;
			case 1:
				if (!isWall[1]) {
					dir = UP;
					y += speed;
				}
				break;
			case 2:
				if (!isWall[2]) {
					dir = RIGHT;
					x += speed;
				}
				break;
			case 3:
				if (!isWall[3]) {
					dir = DOWN;
					y -= speed;
				}
				break;
			}
		}
	}
}

void Enemy::checkWall(bool isWall_[4]) {
	isWall[0] = isWall_[0];
	isWall[1] = isWall_[1];
	isWall[2] = isWall_[2];
	isWall[3] = isWall_[3];
}

void Enemy::killed() {
	status = KILLED;
}

Enemy::~Enemy() {
}
