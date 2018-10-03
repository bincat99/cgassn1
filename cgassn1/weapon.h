
//
//  weapon.h
//  cgassn1
//
//  Created by WonJong Jang on 2018. 10. 2..
//  Copyright © 2018년 Dahun Lee. All rights reserved.
//

#ifndef weapon_h
#define weapon_h

#include "util.h"

class Weapon{
private :
	Position pos;
	Direction dir;
	Size size;
	float speed;  // pos~speed 는 object로부터 상속.
	float range;

public :
	Weapon(Position pos, Direction dir, Size size, float speed, float range);
	~Weapon();

	void move(void); // 상속
	void display(void); // 상속
    
};

#endif /* weapon_h */
