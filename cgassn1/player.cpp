
#include "player.h"
#include "util.h"
#include <stdio.h>
#include <time.h>

#include <list>
#include <iostream>
Player::Player(float x_, float y_, enum Direction dir_, float w_, float h_, float speed_)
{
    
    pos.x = x_;
    pos.y = y_;
    dir = dir_;
    w = w_;
    h = h_;
#ifdef __APPLE__
    speed = speed_ * 10;
    bangDelay = 100000;
    itemDelay = 100000;
#else
    speed = speed_ * 10;
    bangDelay = 200;
    itemDelay = 1000;
#endif
    
    lastItemUse = 0;
    speedDefault = speed;
    status = ALIVE;
    weapon = NULL;
    
    lastbang = 0;
    stimpackDuration = 0;
    accelDuration = 0;
    
    sprite = 0;


	float colors[16] = { 0.0, 0.0, 0.0, 1.0,0.0, 0.0, 0.0, 1.0,0.0, 0.0, 0.0, 1.0,0.0, 0.0, 0.0, 1.0 };
	float points[8] = {
		0, 0,
		0, h,
		w, h,
		w, 0
	};

	glGenVertexArrays(1, &VAO_player);
	glBindVertexArray(VAO_player);

	// Create a buffer
	glGenBuffers(1, &buffer);

	// Bind the buffer to vertx attributes
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	// Init buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0,
		sizeof(points), points);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(points),
		sizeof(colors), colors);


	unsigned int loc = glGetAttribLocation(shaderUtil.getProgram(), "position");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	unsigned int loc2 = glGetAttribLocation(shaderUtil.getProgram(), "color_in");
	glEnableVertexAttribArray(loc2);
	glVertexAttribPointer(loc2, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points)));
	glBindVertexArray(0);


	 float icolors[16] = { (float)0xc0 / 0xff, 1.0, (float)0xee / 0xff, 1.0,(float)0xc0 / 0xff, 1.0, (float)0xee / 0xff, 1.0,(float)0xc0 / 0xff, 1.0, (float)0xee / 0xff, 1.0,(float)0xc0 / 0xff, 1.0, (float)0xee / 0xff, 1.0 };
	 float ipoints[8] = {
		0, 0,
		0, 0 + h,
		0 + w , 0 + h,
		0 + w, 0
	};

	 glGenVertexArrays(1, &VAO_inven);
	 glBindVertexArray(VAO_inven);
	// Create a buffer
	 glGenBuffers(1, &buffer);

	// Bind the buffer to vertx attributes
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	// Init buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(ipoints) + sizeof(icolors), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0,
		sizeof(ipoints), ipoints);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(ipoints),
		sizeof(icolors), icolors);


	unsigned int loc3 = glGetAttribLocation(shaderUtil.getProgram(), "position");
	glEnableVertexAttribArray(loc3);
	glVertexAttribPointer(loc3, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	unsigned int loc4 = glGetAttribLocation(shaderUtil.getProgram(), "color_in");
	glEnableVertexAttribArray(loc4);
	glVertexAttribPointer(loc4, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(ipoints)));
	glBindVertexArray(0);
}

void Player::display(void)
{
    for (std::list<Weapon*>::iterator it = listWeapon.begin(); it != listWeapon.end(); it++)
    {
        glColor3f(1.0, .0, .0);
        (*it)->display();
        
    }
    if (status == ALIVE)
    {
        sprite = (sprite + 1) % 3;



		ctm = temp;
		ctm = glm::transpose(glm::translate(glm::transpose(ctm), glm::vec3(pos.x, pos.y, 0)));
		glBindVertexArray(VAO_player);
		glUniformMatrix4fv(matrix_loc, 1, GL_TRUE, value_ptr(ctm));
		glDrawArrays(GL_QUADS, 0, 4);
		glBindVertexArray(0);
		/*
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_QUADS);
        
        glVertex2f(pos.x, pos.y);
        glVertex2f(pos.x, pos.y + h);
        
        glVertex2f(pos.x + w, pos.y + h);
        
        
        glVertex2f(pos.x + w, pos.y);
        glEnd();
		*/
        
        
        /* item box */
        float itemX, itemY;
        itemX = pos.x + 700.0 -w;
        itemY = pos.y - 800.0 ;

        
        std::list<Item*>::iterator it = listItem.begin();
        int idx = 0;
        while (it != listItem.end ())
        {
            (*it)->displayBox(itemX,itemY, idx);
            it++;
            idx++;
        }
        
        for (; idx < 6; idx++)
        {
            float ItemX = itemX + (idx % 3) * w;
            float ItemY = itemY + (idx / 3) * h;


			ctm = temp;
			ctm = glm::transpose(glm::translate(glm::transpose(ctm), glm::vec3((int)ItemX, (int)ItemY, 0)));
			glBindVertexArray(VAO_inven);
			glUniformMatrix4fv(matrix_loc, 1, GL_TRUE, value_ptr(ctm));
			glDrawArrays(GL_QUADS, 0, 4);
			glBindVertexArray(0);


			/*
            glColor3f ((float)0xc0/0xff, 1.0, (float)0xee/0xff);
            glBegin(GL_POLYGON);
            glVertex2f(ItemX, ItemY);
            glVertex2f(ItemX, ItemY + h);
            glVertex2f(ItemX + w, ItemY + h);
            glVertex2f(ItemX + w, ItemY);
            glEnd();
			*/
			
        }
        
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
                {
                    
                    bang();
                }
                
            }
            
            if (i == 'j')
            {
                if (clock() - lastItemUse > itemDelay)
                {
                    
                    useItem();
                }
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
    if (dir == LEFT || dir == RIGHT)
    {
        listWeapon.push_back(new Weapon(pos.x, pos.y + GLOBAL_GRID_LENGTH / 4, dir, w, h / 2, speed * 2, speed * 150));
    }
    
    else
    {
        listWeapon.push_back(new Weapon(pos.x + GLOBAL_GRID_LENGTH / 4, pos.y, dir, w / 2, h, speed * 2, speed * 150));
    }
    
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
#ifdef __APPLE__
            bangDelay = 2000;
#else
            bangDelay = 200;
#endif
        }
    }
    
    if (accelDuration != 0)
    {
        if (clock() > accelDuration)
        {
            accelDuration = 0;
            speed = speedDefault;
        }
    }
}

bool
Player::useItem(void)
{
    if (listItem.empty() == false)
    {
        lastItemUse = clock ();
        // Do something with Item.
        
        switch ((listItem.front())->getType()) {
            case ONE:
                if (stimpackDuration != 0)
                    return false;
#ifdef __APPLE__
                bangDelay = 10000;
                stimpackDuration = 1000000 + clock();
#else
                bangDelay = 100;
                stimpackDuration = 1000 + clock();
#endif
                break;
                
            case TWO:
                if (accelDuration != 0)
                    return false;
                speed = speed * 3;
#ifdef __APPLE__
                accelDuration = 1000000 + clock();
#else
                accelDuration = 1000 + clock();
#endif
                break;
        }
        
        listItem.pop_front();
        return true;
    }
    else {
        return false;
    }
}
unsigned long
Player::getItemNum ()
{
    return listItem.size();
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
            it = listWeapon.erase(it);
            
            delete tmp;
        }
        else it++;
    }
}



enum Status
Player::getStatus ()
{
    return status;
}

Player::~Player()
{
}
