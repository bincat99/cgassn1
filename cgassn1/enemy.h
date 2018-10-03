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
class Enemy : virtual public Object
{
    unsigned int HP;
    int x;
    int y;
public:
    Enemy ();
    void display ();

};

#endif /* enemy_h */
