
#include "player.h"
#include "util.h"
#include <stdio.h>
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
    status = ALIVE;
    weapon = NULL;
}

void Player::display(void) {
    if (status == ALIVE)
    {
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(x, y);
        glVertex2f(x, y + h);
        glVertex2f(x + w, y + h);
        glVertex2f(x + w, y);
        glEnd();
    }
    glColor3f(0.0, 0.0, 0.0);
    if (weapon != NULL) weapon->display();
}

void Player::move(void) {
    int i = 0;
    
    
    for (i = 0; i < KEYBOARD_BUFFER_SIZE; i++)
    {
        if (keyboardBuffer[i])
        {
            if (i == 'a')
            {
				if (!isWall[0]) {
					x -= speed;
					dir = LEFT;
				}
            }
            
            if (i == 's')
            {
				if (!isWall[3]) {
					y -= speed;
					dir = DOWN;
				}
            }
            
            
            if (i == 'd')
            {
				if (!isWall[2]) {
					x += speed;
					dir = RIGHT;
				}
            }
            
            
            if (i == 'w')
            {
				if (!isWall[1]) {
					y += speed;
					dir = UP;
				}
            }
            
            if (i == 'k')
            {
                
                if (weapon == NULL){
                    printf ("Shoot!\n");
                    weapon = new Weapon(x, y, dir, w / 5, h / 5, speed * 2, speed * 500);
                }
            }
            
        }
        
        if (specialKeyBuffer[i])
        {
            if (i == GLUT_KEY_LEFT)
            {
				if (!isWall[0]) {
					dir = LEFT;
					x -= speed;
				}

            }
            
            if (i == GLUT_KEY_UP)
            {
				if (!isWall[1]) {
					y += speed;
					dir = UP;
				}
            }
            
            if (i == GLUT_KEY_RIGHT)
            {
				if (!isWall[2]) {
					x += speed;
					dir = RIGHT;
				}
            }
            
            if (i == GLUT_KEY_DOWN)
            {
				if (!isWall[3]) {
					y -= speed;
					dir = DOWN;
				}
            }
        }
    }
    
    if(weapon != NULL) {
        weapon->move();
        if (weapon->getStatus() == KILLED)
        {
            weapon->~Weapon();
            weapon = NULL;
        }
    }
}

float Player::getX() {
    return x;
}

float Player::getY() {
    return y;
}

void Player::bang(void) {


}

float Player::getXcord ()
{
    return x;
}

float Player::getYcord ()
{
    return y;
}

void Player::killed(void) {
	status = KILLED;
}

void Player::checkWall(bool isWall_[4]) {
	isWall[0] = isWall_[0];
	isWall[1] = isWall_[1];
	isWall[2] = isWall_[2];
	isWall[3] = isWall_[3];

}

Player::~Player()
{
}
