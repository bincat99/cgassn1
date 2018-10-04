
#include "player.h"
#include "util.h"
#include <stdio.h>
#include <list>
Player::Player(float x_, float y_, enum Direction dir_, float w_, float h_, float speed_)
{
    pos.x = x_;
    pos.y = y_;
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

void Player::display(void)
{
    if (status == ALIVE)
    {
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(pos.x, pos.y);
        glVertex2f(pos.x, pos.y + h);
        glVertex2f(pos.x + w, pos.y + h);
        glVertex2f(pos.x + w, pos.y);
        glEnd();
    }
    glColor3f(0.0, 0.0, 0.0);
    
    for (std::list<Weapon*>::iterator it = listWeapon.begin(); it != listWeapon.end(); it++)
    {
        (*it)->display();
    }
}

void Player::move(void)
{
    int i = 0;
    
    
    for (i = 0; i < KEYBOARD_BUFFER_SIZE; i++)
    {
        if (keyboardBuffer[i])
        {
            if (i == 'a')
            {
                if (!isWall[0])
                {
                    pos.x -= speed;
                    dir = LEFT;
                }
            }
            
            if (i == 's')
            {
                if (!isWall[3])
                {
                    pos.y -= speed;
                    dir = DOWN;
                }
            }
            
            
            if (i == 'd')
            {
                if (!isWall[2])
                {
                    pos.x += speed;
                    dir = RIGHT;
                }
            }
            
            
            if (i == 'w')
            {
                if (!isWall[1])
                {
                    pos.y += speed;
                    dir = UP;
                }
            }
            
            if (i == 'k')
            {
                bang();
            }
            
        }
        
        if (specialKeyBuffer[i])
        {
            if (i == GLUT_KEY_LEFT)
            {
                if (!isWall[0]) {
                    dir = LEFT;
                    pos.x -= speed;
                }
                
            }
            
            if (i == GLUT_KEY_UP)
            {
                if (!isWall[1]) {
                    pos.y += speed;
                    dir = UP;
                }
            }
            
            if (i == GLUT_KEY_RIGHT)
            {
                if (!isWall[2]) {
                    pos.x += speed;
                    dir = RIGHT;
                }
            }
            
            if (i == GLUT_KEY_DOWN)
            {
                if (!isWall[3]) {
                    pos.y -= speed;
                    dir = DOWN;
                }
            }
        }
    }
    
    
    std::list<Weapon*>::iterator it = listWeapon.begin();
    
    while (it != listWeapon.end ())
    {
        
        if ((*it)->getStatus() == ALIVE)
            (*it)->move();
        it++;
        
    }
    
}



void Player::bang(void)
{
    listWeapon.push_back(new Weapon(pos.x+GLOBAL_GRID_LENGTH/2, pos.y+GLOBAL_GRID_LENGTH/2, dir, w / 5, h / 5, speed * 2, speed * 30));
}



position Player::getPos ()
{
    return pos;
}
void Player::killed(void)
{
    status = KILLED;
}

void Player::checkWall(bool isWall_[4])
{
    isWall[LEFT] = isWall_[0];
    isWall[UP] = isWall_[1];
    isWall[RIGHT] = isWall_[2];
    isWall[DOWN] = isWall_[3];
}


void Player::cleanWall ()
{
    isWall[LEFT] = false;
    isWall[UP] = false;
    isWall[RIGHT] = false;
    isWall[DOWN] = false;
}

void
Player::addItem(Item* item_)
{
    listItem.push_back(item_);
}

bool
Player::useItem(void)
{
    if (listItem.front() != NULL)
    {
        // Do something with Item.
        listItem.pop_front();
        return true;
    }
    else {
        return false;
    }
}

std::list<Weapon*>
Player::getWeaponList (void)
{
    return listWeapon;
}

void
Player::checkWeapon ()
{
    std::list<Weapon*>::iterator it = listWeapon.begin();
    
    while (it != listWeapon.end ())
    {
        
        if ((*it)->getStatus() == KILLED)
        {
            Weapon * tmp = NULL;
            tmp = *it;
            listWeapon.erase(it);
            it ++;
            delete tmp;
        }
        else it++;
    }
}

Player::~Player()
{
}
