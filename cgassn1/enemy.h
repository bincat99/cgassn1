//
//  enemy.h
//  cgassn1
//
//  Created by Dahun Lee on 2018. 10. 1..
//  Copyright © 2018년 Dahun Lee. All rights reserved.
//

#ifndef enemy_h
#define enemy_h

class Enemy
{
private:
	Position pos;
	Direction dir; 
	Size size;
	float speed;  // pos~speed 는 object로부터 상속.
	Status status;

	bool isWall[4];

public:
	Enemy(Position, Direction, Size, float, Status)
	void move(void);
	void display(void);


	// GET/SET method
	Position getPos();
	Direction getDir();
	Size getSize();
	float getSpeed();
	Status getStatus();

	void setPos(Position);
	void setDir(Direction);
	void setSize(Size);
	void setSpeed(float);

	void checkWall(bool*);
	void killed();

	~Enemy();
};

#endif /* enemy_h */
