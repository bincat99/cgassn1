//
//  player.h
//  cgassn1
//
//  Created by Dahun Lee on 2018. 10. 1..
//  Copyright © 2018년 Dahun Lee. All rights reserved.
//

#ifndef player_h
#define player_h


#include "util.h"
#include "weapon.h"
#include "object.h"



class Player : virtual public Object{

private:
	float x, y;
	enum Direction dir;
	float w, h;
	float speed;
	Weapon* weapon;
	enum Status status;

public :
	Player(float, float, enum Direction, float, float, float);
	void display(void);
	void move(void);
	void bang(void);

	float getX();
	float getY();

	~Player();
	
    float getXcord ();
    float getYcord ();

	void killed(void);
};

#endif /* player_h */
