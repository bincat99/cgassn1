#pragma once

#include "sys.h"
#include "util.h"
#include "player.h"
#include "enemy.h"
#include "gun.h"
#include "wall.h"




class Map
{
public:




	std::vector<Enemy*>* enemyVect;
	std::vector<Wall*>* wallVect;
	Player* player;
	Gun* gun;
	

	Map();
	void init();
	void display();
	void reshape(int, int);
	void moveObjects();
};