
//
//  weapon.h
//  cgassn1
//
//  Created by Dahun Lee on 2018. 10. 1..
//  Copyright © 2018년 Dahun Lee. All rights reserved.
//

#ifndef weapon_h
#define weapon_h


class Weapon{
private :
	float x, y;
	enum Direction dir;
	float w, h;
	float speed;
	float range;
	enum Status status;

public:
	Weapon(float, float, enum Direction, float, float, float, float );
	void display(void);
	void move(void);
	~Weapon();
    
};

#endif /* weapon_h */
