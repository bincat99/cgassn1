#pragma once

#include "sys.h"
#include "util.h"
#include "player.h"
#include "enemy.h"
#include "gun.h"
#include "wall.h"
#include "bullet.h"



enum ObjectType
{
	EMPTY,
	WALL,
	ITEM,
	ENEMY,
	SAFE
};

class Map
{
	int gridLength;
	ObjectType objMap[32][32];
	int gridSize;

public:
	Camera camera;
	std::list<Enemy*> listEnemy;
	std::list<Wall*> listWall;
	std::list<Bullet*> listBullet;
	Player* player;
	Gun* gun;

	Map();
	void init();
	void display();
	void reshape(int, int);
	void moveObjects();
	void checkWall();
};