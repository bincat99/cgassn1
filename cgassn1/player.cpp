
#include "player.h"
#include "util.h"

Player::Player(float x_, float y_, enum Direction dir_, float w_, float h_, float speed_) {
	x = x_;
	y = y_;
	dir = dir_;
	w = w_;
	h = h_;
#ifdef __APPLE__
    speed = speed_ * 10;
#else
	speed = speed_;
#endif
	//weapon = weapon_;

}

void Player::display(void) {
  
    glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x, y);
	glVertex2f(x, y + h);
	glVertex2f(x + w, y +h);
	glVertex2f(x + w, y);
	glEnd();
}

void Player::move(void) {
	int i = 0;
	for (i = 0; i < KEYBOARD_BUFFER_SIZE; i++)
	{
		if (keyboardBuffer[i])
		{
			if (i == 'a')
				x -= speed;

			if (i == 's')
				y -= speed;


			if (i == 'd')
				x += speed;


			if (i == 'w')
				y += speed;


		}

		if (specialKeyBuffer[i])
		{
			if (i == GLUT_KEY_LEFT)
				x -= speed;

			if (i == GLUT_KEY_UP)
				y += speed;


			if (i == GLUT_KEY_RIGHT)
				x += speed;

			if (i == GLUT_KEY_DOWN)
				y -= speed;

		}
	}
}

Player::~Player() {
}
