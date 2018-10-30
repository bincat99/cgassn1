//
//  util.h
//  cgassn1
//
//  Created by Dahun Lee on 2018. 10. 1..
//  Copyright © 2018년 Dahun Lee. All rights reserved.
//

#ifndef util_h
#define util_h

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#include <GLUT/GLUT.h>
#else
#include <windows.h>
#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <list>
#include "ShaderUtil.h"

#define KEYBOARD_BUFFER_SIZE 256
#define GLOBAL_GRID_LENGTH 50


#define COL_LEFT (1<<0)
#define COL_UP (1<<1)
#define COL_RIGHT (1<<2)
#define COL_DOWN (1<<3)

#define BUFFER_OFFSET( offset ) ((GLvoid*)(offset))

enum Direction { LEFT, UP, RIGHT, DOWN };
enum Status { ALIVE, KILLED };
enum ItemType { ONE, TWO};

extern bool
keyboardBuffer [KEYBOARD_BUFFER_SIZE];


extern bool
specialKeyBuffer [KEYBOARD_BUFFER_SIZE];



typedef struct
{
    float x;
    float y;
}position;

extern ShaderUtil shaderUtil;

extern GLuint buffer;

extern unsigned int buf_enemy;
extern unsigned int buf_player;
extern unsigned int buf_wall;
extern unsigned int buf_empty;
extern unsigned int buf_item;
extern unsigned int buf_weapon;
extern unsigned int buf_inven;

extern unsigned int VAO_enemy;
extern unsigned int VAO_player;
extern unsigned int VAO_wall;
extern unsigned int VAO_empty;
extern unsigned int VAO_item;
extern unsigned int VAO_weapon;
extern unsigned int VAO_inven;

extern unsigned int matrix_loc;
extern glm::mat4 ctm;
extern glm::mat4 temp;

extern unsigned int
windowId;

extern bool
gameClear;

void
utilInit ();

void
myKeyboardFunc (unsigned char, int, int);

void
myKeyboardUpFunc (unsigned char, int, int);

void
mySpecialFunc (int key, int x, int y);

void
mySpecialUpFunc (int key, int x, int y);

unsigned int
CheckCollision (position , position );

unsigned int
CheckCollisionWeapon (position , position );

float
calDistance (float x1, float y1, float x2, float y2);


#endif /* util_h */


