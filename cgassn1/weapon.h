
//
//  weapon.h
//  cgassn1
//
//  Created by Dahun Lee on 2018. 10. 1..
//  Copyright © 2018년 Dahun Lee. All rights reserved.
//

#ifndef weapon_h
#define weapon_h

#include "util.h"
#include "object.h"

class Weapon : virtual public GameObject
{
private :
	float x, y;
    position pos;
	enum Direction dir;
	float w, h;
	float speed;
	float range;
	enum Status status;

	bool isWall[4] = { false, false, false, false, };
public:
	Weapon(float, float, enum Direction, float, float, float, float );
	void display(void);
	void move(void);
	~Weapon();
	
	void killed();
    
	void checkWall(bool isWall_[4]);

    enum Status getStatus (void);
    
    position getPos();
};

#endif /* weapon_h */
