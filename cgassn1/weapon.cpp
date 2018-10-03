#include "weapon.h"
#include "util.h"

Weapon::Weapon(float x_, float y_, enum Direction dir_, float w_, float h_, float speed_, float range_) {
	x = x_;
	y = y_;
	dir = dir_;
	w = w_;
	h = h_;
	speed = speed_;
	range = range_;
	status = ALIVE;
}

void Weapon::display(void) {
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

void Weapon::move(void) {
	if (status == ALIVE) {
		if (range > 0) {
			switch (dir) {
			UP: y += speed;
				range -= speed;
				break;
			DOWN:
				y -= speed;
				range -= speed;
				break;
			LEFT:
				x -= speed;
				range -= speed;
				break;
			RIGHT:
				x += speed;
				range -= speed;
				break;
			}
		}
		else {
			status = KILLED;
		}
	}
}

Weapon::~Weapon() {
}