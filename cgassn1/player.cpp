
#include "player.h"
#include "util.h"
#include "BmpLoader.h"
#include <stdio.h>

Player::Player(float x_, float y_, enum Direction dir_, float w_, float h_, float speed_) {
    x = x_;
    y = y_;
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

}

void Player::display(void) {
    if (status == ALIVE)
    {
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
			glVertex2f(x, y);
			glTexCoord2f(0.0, 1.0);
			glVertex2f(x, y + h);

			glTexCoord2f(1.0, 1.0);
			glVertex2f(x + w, y + h);


			glTexCoord2f(1.0, 0.0);
			glVertex2f(x + w, y);
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
			glVertex2f(x, y);
			glTexCoord2f(0.0, 1.0);
			glVertex2f(x, y + h);

			glTexCoord2f(1.0, 1.0);
			glVertex2f(x + w, y + h);


			glTexCoord2f(1.0, 0.0);
			glVertex2f(x + w, y);
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
			glVertex2f(x, y);
			glTexCoord2f(0.0, 1.0);
			glVertex2f(x, y + h);

			glTexCoord2f(1.0, 1.0);
			glVertex2f(x + w, y + h);


			glTexCoord2f(1.0, 0.0);
			glVertex2f(x + w, y);
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
			glVertex2f(x, y);
			glTexCoord2f(0.0, 1.0);
			glVertex2f(x, y + h);

			glTexCoord2f(1.0, 1.0);
			glVertex2f(x + w, y + h);


			glTexCoord2f(1.0, 0.0);
			glVertex2f(x + w, y);
			glEnd();
			break;
		}
    }
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
                    pos.x -= speed;
					dir = LEFT;
				}
            }
            
            if (i == 's')
            {
				if (!isWall[3]) {
					y -= speed;
                        pos.y -= speed;
					dir = DOWN;
				}
            }
            
            
            if (i == 'd')
            {
				if (!isWall[2]) {
					x += speed;
                        pos.x += speed;
					dir = RIGHT;
				}
            }
            
            
            if (i == 'w')
            {
				if (!isWall[1]) {
					y += speed;
                        pos.y += speed;
					dir = UP;
				}
            }
            
            if (i == 'k')
            {
                
                if (weapon == NULL){

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


position Player::getPos ()
{
    return pos;
}
void Player::killed(void) {
	status = KILLED;
}

void Player::checkWall(bool isWall_[4]) {
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

void Player::addItem(Item* item_) {
	item_list.push_back(item_);
}

bool Player::useItem(void) {
	if (item_list.front() != NULL) {
		// Do something with Item.
		item_list.pop_front();
		return true;
	}
	else {
		return false;
	}
}


void Player::LoadTexture(const char* filename) {
	BmpLoader bl(filename);

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
