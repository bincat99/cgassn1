//
//  player.h
//  cgassn1
//
//  Created by Dahun Lee on 2018. 10. 1..
//  Copyright © 2018년 Dahun Lee. All rights reserved.
//

#ifndef player_h
#define player_h

enum Direction { LEFT,UP,RIGHT,DOWN};
enum Status { ALIVE, KILLED };


class Player{

private:
	float x, y;
	enum Direction dir;
	float w, h;
	float speed;
	//Weapon* Weapon;
	enum Status status;

public :
	Player(float, float, enum Direction, float, float, float);
	void display(void);
	void move(void);

	~Player();
	

};

#endif /* player_h */
