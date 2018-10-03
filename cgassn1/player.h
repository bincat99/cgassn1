//
//  player.h
//  cgassn1
//
//  Created by WonJong Jang on 2018. 10. 1..
//  Copyright © 2018년 Dahun Lee. All rights reserved.
//

#ifndef player_h
#define player_h

#include "util.h"

class Player {
private :
	Position pos;
	Direction dir; 
	Size size;
	float speed;  // pos~speed 는 object로부터 상속.
	Weapon* weapon;
	Status status;

	bool isWall[4]; // UP DOWN LEFT RIGHT

	// Shape
	// Item list
	// weapon

public :
	Player();
	Player(Position pos, Direction dir, Size size, float speed, Weapon* weapon, Status status);

	void move(unsigned char);
	void shoot(void);

	void addItem(Item*);
	bool useItem(unsigned char);
	void display(void);

	// Basic GET/SET method
	Position getPos();
	Direction getDir();
	Size getSize();
	float getSpeed();
	Weapon* getWeapon();
	Status getStatus();

	void setPos(Position);
	void setDir(Direction);
	void setSize(Size);
	void setSpeed(float);
	void setWeapon(Weapon*);

	void checkWall(bool*);
	void killed();

	~Player();
};

#endif /* player_h */