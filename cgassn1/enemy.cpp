//
//  enemy.cpp
//  cgassn1
//
//  Created by Dahun Lee on 2018. 10. 1..
//  Copyright © 2018년 Dahun Lee. All rights reserved.
//

#include "enemy.h"

Enemy::Enemy ()
{
    this->HP = 1;
    this->x = 500;
    this->y = 500;
}



position Enemy::getPos()
{
    return pos;
}

void Enemy::display()
{
    
}
