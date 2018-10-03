
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
    status = ALIVE;
    weapon = new Weapon(x, y, dir, w, h, 0.0, 0.0);
}

void Player::display(void) {
    if (status == ALIVE)
    {
        glColor3f(0.0, 0.0, 0.0);
        weapon->display();
        glBegin(GL_LINE_LOOP);
        glVertex2f(x, y);
        glVertex2f(x, y + h);
        glVertex2f(x + w, y + h);
        glVertex2f(x + w, y);
        glEnd();
    }
    
}

void Player::move(void) {
    int i = 0;
    
    weapon->move();
    for (i = 0; i < KEYBOARD_BUFFER_SIZE; i++)
    {
        if (keyboardBuffer[i])
        {
            if (i == 'a')
            {
                x -= speed;
                dir = LEFT;
            }
            
            if (i == 's')
            {
                y -= speed;
                dir = DOWN;
            }
            
            
            if (i == 'd')
            {
                x += speed;
                dir = RIGHT;
            }
            
            
            if (i == 'w')
            {
                y += speed;
                dir = UP;
            }
            
            
        }
        
        if (specialKeyBuffer[i])
        {
            if (i == GLUT_KEY_LEFT)
            {
                dir = LEFT;
            }
            x -= speed;
            
            if (i == GLUT_KEY_UP)
            {
                y += speed;
                dir = UP;
            }
            
            if (i == GLUT_KEY_RIGHT)
            {
                x += speed;
                dir = RIGHT;
            }
            
            if (i == GLUT_KEY_DOWN)
            {
                y -= speed;
                dir = DOWN;
            }
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
    int i = 0;
    for (i = 0; i < KEYBOARD_BUFFER_SIZE; i++)
    {
        if (keyboardBuffer[i])
        {
            if (i == 'k')
            {
                weapon = new Weapon(x, y, dir, w / 5, h / 5, speed * 2, speed * 50);
            }
        }
    }
}

float Player::getXcord ()
{
    return x;
}

float Player::getYcord ()
{
    return y;
}


Player::~Player()
{
}
