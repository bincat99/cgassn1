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

void Enemy::move() {
	if (status == ALIVE) {
		int Idir = rand() % 4;

		switch (Idir) {
		case 0: // Left Up Right Down
			dir = LEFT;
			x -= speed;
			break;
		case 1:
			dir = UP;
			y += speed;
			break;
		case 2:
			dir = RIGHT;
			x += speed;
			break;
		case 3:
			dir = DOWN;
			y -= speed;
			break;
		}
	}
}

void Enemy::killed() {
	status = KILLED;
}

Enemy::~Enemy() {
}
