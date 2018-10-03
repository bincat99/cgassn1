//
//  enemy.h
//  cgassn1
//
//  Created by Dahun Lee on 2018. 10. 1..
//  Copyright © 2018년 Dahun Lee. All rights reserved.
//

#ifndef enemy_h
#define enemy_h
#include "object.h"
#include "util.h"

class Enemy : virtual public GameObject
{
    unsigned int HP;
    int x;
    int y;
    
    position pos;
public:
    Enemy ();
    void display ();
    position getPos ();
};

#endif /* enemy_h */
