#pragma once
#include <windows.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

#include "game.h"
#include "emptySpace.h"
#include "enemy.h"
#include "item.h"
#include "map.h"
#include "object.h"
#include "player.h"
#include "wall.h"
#include "weapon.h"

 enum Direction { UP, DOWN, LEFT, RIGHT };

class Position {
private:
	float x_, y_;
public:
	float x(void);
	float y(void);
	void set(float x, float y);

	Position();
	Position(float x, float y);
	~Position();
};

class Size {
private:
	float w_, h_;
public:
	float w(void);
	float h(void);
	void set(float w, float h);

	Size();
	Size(float w, float h);
	~Size();
};

