
#include "player.h"
#include "util.h"
#include "BmpLoader.h"
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
    speed = speed_ * 10;
#endif
    status = ALIVE;
    weapon = NULL;
    bangDelay = 20000;
    lastbang = 0;
    stimpackDuration = 0;
    
}

void Player::display(void)
{
    if (status == ALIVE)
    {
/*<<<<<<< HEAD
        glColor3f(0.0, 1.0, 0.0);
        glBegin(GL_POLYGON);
        glVertex2f(pos.x, pos.y);
        glVertex2f(pos.x, pos.y + h);
        glVertex2f(pos.x + w, pos.y + h);
        glVertex2f(pos.x + w, pos.y);
        glEnd();
    }
    glColor3f(0.0, 0.0, 0.0);
    */

		glEnable(GL_TEXTURE_2D);
		switch (dir) {
		case DOWN :
			sprite = (sprite + 1) % 3;
			switch (sprite) {
			case 0 :
				LoadTexture("down0.bmp");
				break;
			case 1 :
				LoadTexture("down1.bmp");
				break;
			case 2 :
				LoadTexture("down2.bmp");
				break;
			}

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
			break;
		case UP:
			sprite = (sprite + 1) % 3;
			switch (sprite) {
			case 0:
				LoadTexture("up0.bmp");
				break;
			case 1:
				LoadTexture("up1.bmp");
				break;
			case 2:
				LoadTexture("up2.bmp");
				break;
			}

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
			break;
		case RIGHT :
			sprite = (sprite + 1) % 3;
			switch (sprite) {
			case 0:
				LoadTexture("right0.bmp");
				break;
			case 1:
				LoadTexture("right1.bmp");
				break;
			case 2:
				LoadTexture("right2.bmp");
				break;
			}

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
			break;
		case LEFT :
			sprite = (sprite + 1) % 3;
			switch (sprite) {
			case 0:
				LoadTexture("left0.bmp");
				break;
			case 1:
				LoadTexture("left1.bmp");
				break;
			case 2:
				LoadTexture("left2.bmp");
				break;
			}

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
			break;
		}
    }
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
                if (clock() - lastbang > bangDelay)
                    bang();
            }
            
            if (i == 't')
            {
                useItem ();
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
    listWeapon.push_back(new Weapon(pos.x+GLOBAL_GRID_LENGTH/2, pos.y+GLOBAL_GRID_LENGTH/2, dir, w / 5, h / 5, speed * 2, speed * 150));
    lastbang = clock ();
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

void
Player::checkItemDuration ()
{
    if (stimpackDuration != 0)
    {
        if (clock() > stimpackDuration)
        {
            stimpackDuration = 0;
            bangDelay = 20000;
        }
    }
}

bool
Player::useItem(void)
{
    if (listItem.front() != NULL)
    {
        // Do something with Item.
        stimpackDuration = 1000000 + clock();
        bangDelay  = 10000;
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


void
Player::LoadTexture(const char* filename)
{
	BmpLoader  bl (filename);

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData);
}


Player::~Player()
{

}
