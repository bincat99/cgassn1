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
#include "BmpLoader.h"



class Player : virtual public GameObject
{

private:
	enum Direction dir;
	float w, h;
	float speed;
    float speedDefault;
	Weapon* weapon;
	enum Status status;
    position pos;
    
    clock_t lastbang;
    clock_t bangDelay;
    clock_t stimpackDuration;
    
    clock_t lastItemUse;
    clock_t itemDelay;
    
    clock_t accelDuration;

	int sprite;

	unsigned int textureID;

	bool isWall[4] = {false, false, false, false,};
	std::list<Item*> listItem;
    std::list<Weapon*> listWeapon;
    
    BmpLoader * bl[12];

public :
	Player(float, float, enum Direction, float, float, float);
	void display(void);
	void move(void);
	void bang(void);

    enum Status getStatus ();
    
    position getPos (void);

	void killed(void);
	void checkWall(bool isWall_[4]);
   
    void checkWeapon ();

    void cleanWall ();

	void addItem(Item*);
	bool useItem(void);
    void checkItemDuration ();
    
    unsigned long getItemNum ();

    std::list<Weapon*> getWeaponList ();

	void LoadTexture(unsigned int);
	~Player();

};

#endif /* player_h */
