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
#include "item.h"


class Player : virtual public GameObject
{

private:
	float x, y;
	enum Direction dir;
	float w, h;
	float speed;
	Weapon* weapon;
	enum Status status;
    position pos;

	bool isWall[4] = {false, false, false, false,};
	std::list<Item*> item_list;

public :
	Player(float, float, enum Direction, float, float, float);
	void display(void);
	void move(void);
	void bang(void);

	float getX();
	float getY();

	
    float getXcord ();
    float getYcord ();
    
    position getPos (void);

	void killed(void);
	void checkWall(bool isWall_[4]);

    void cleanWall ();

	void addItem(Item*);
	bool useItem(void);


	~Player();

};

#endif /* player_h */
