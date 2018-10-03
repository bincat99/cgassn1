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

class Enemy : virtual public Object
{
    float x;
    float y;
	enum Direction dir;
	float w, h;
	float speed;
	enum Status status;

public:
    Enemy (float, float, enum Direction, float, float, float);
    void display ();
	void move();

	void killed();
	~Enemy();
};

#endif /* enemy_h */
