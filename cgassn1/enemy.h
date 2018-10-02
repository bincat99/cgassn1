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

public:
	void move(void);
    
};

#endif /* enemy_h */
