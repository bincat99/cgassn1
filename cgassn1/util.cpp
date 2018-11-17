//
//  util.cpp
//  cgassn1
//
//  Created by Dahun Lee on 2018. 10. 1..
//  Copyright © 2018??Dahun Lee. All rights reserved.
//

#include "util.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include <cmath>


#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#include <GLUT/GLUT.h>
#else
#include <windows.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#endif


ShaderUtil shaderUtil;


GLuint MatrixID;
GLuint MatrixID2;



unsigned int
windowId;

bool
gameClear;

bool
keyboardBuffer [KEYBOARD_BUFFER_SIZE];


bool
specialKeyBuffer [KEYBOARD_BUFFER_SIZE];

void
utilInit ()
{
	srand(time(NULL));
    int i;
    
    for (i=0 ; i < KEYBOARD_BUFFER_SIZE ; i++)
    {
        keyboardBuffer[i] = false;
        specialKeyBuffer[i] = false;
    }
    gameClear = false;
}
//
void
myKeyboardFunc (unsigned char key, int x, int y)
{
    keyboardBuffer[key] = true;
}

void
myKeyboardUpFunc (unsigned char key, int x, int y)
{
    keyboardBuffer[key] = false;
}


void
mySpecialFunc (int key, int x, int y)
{
    specialKeyBuffer[key] = true;
}

void
mySpecialUpFunc (int key, int x, int y)
{
    specialKeyBuffer[key] = false;
}

unsigned int
CheckCollision (position pos1, position pos2)
{
    unsigned int ret = 0;
    
    
    // check right side
    bool CollisionX = pos1.x + GLOBAL_GRID_LENGTH >= pos2.x && pos2.x >= pos1.x;
    bool CollisionY = pos1.y + GLOBAL_GRID_LENGTH > pos2.y && pos2.y + GLOBAL_GRID_LENGTH > pos1.y;
    
    if (CollisionX && CollisionY) ret |= COL_RIGHT;
    
    // check left side
    CollisionX = pos1.x <= pos2.x + GLOBAL_GRID_LENGTH && pos2.x <= pos1.x;
    CollisionY = pos1.y + GLOBAL_GRID_LENGTH > pos2.y && pos2.y + GLOBAL_GRID_LENGTH > pos1.y;
    
    if (CollisionX && CollisionY) ret |= COL_LEFT;
    
    // check up side
    CollisionX = pos1.x + GLOBAL_GRID_LENGTH > pos2.x  && pos2.x + GLOBAL_GRID_LENGTH > pos1.x;
    CollisionY = pos1.y + GLOBAL_GRID_LENGTH >= pos2.y && pos2.y >= pos1.y;
    
    if (CollisionX && CollisionY) ret |= COL_UP;
    
    // check down side
    CollisionX = pos1.x + GLOBAL_GRID_LENGTH > pos2.x  && pos2.x + GLOBAL_GRID_LENGTH > pos1.x;
    CollisionY = pos1.y  <= pos2.y + GLOBAL_GRID_LENGTH && pos2.y <= pos1.y;
    
    if (CollisionX && CollisionY) ret |= COL_DOWN;
    
    return ret;
}

unsigned int
CheckCollisionWeapon (position pos1, position pos2)
{
    unsigned int ret = 0;
    
    
    // check right side
    bool CollisionX = pos1.x + GLOBAL_GRID_LENGTH/5 >= pos2.x && pos2.x >= pos1.x;
    bool CollisionY = pos1.y + GLOBAL_GRID_LENGTH/5 > pos2.y && pos2.y + GLOBAL_GRID_LENGTH > pos1.y;
    
    if (CollisionX && CollisionY) ret |= COL_RIGHT;
    
    // check left side
    CollisionX = pos1.x <= pos2.x + GLOBAL_GRID_LENGTH/5 && pos2.x <= pos1.x;
    CollisionY = pos1.y + GLOBAL_GRID_LENGTH/5 > pos2.y && pos2.y + GLOBAL_GRID_LENGTH > pos1.y;
    
    if (CollisionX && CollisionY) ret |= COL_LEFT;
    
    // check up side
    CollisionX = pos1.x + GLOBAL_GRID_LENGTH/5 > pos2.x  && pos2.x + GLOBAL_GRID_LENGTH > pos1.x;
    CollisionY = pos1.y + GLOBAL_GRID_LENGTH/5 >= pos2.y && pos2.y >= pos1.y;
    
    if (CollisionX && CollisionY) ret |= COL_UP;
    
    // check down side
    CollisionX = pos1.x + GLOBAL_GRID_LENGTH/5 > pos2.x  && pos2.x + GLOBAL_GRID_LENGTH > pos1.x;
    CollisionY = pos1.y  <= pos2.y + GLOBAL_GRID_LENGTH && pos2.y <= pos1.y;
    
    if (CollisionX && CollisionY) ret |= COL_DOWN;
    
    return ret;
}


float
calDistance (float x1, float y1, float x2, float y2)
{
    return (sqrt (pow(x2-x1, 2) + pow(y2-y1, 2)));
}

void
renderbitmap(float x, float y, void*font, char* string) {
	char *c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

std::vector<std::string>
split_string(std::string str) {
	using namespace std;

	string buf;
	stringstream ss(str);

	vector<string> tokens;

	while (ss >> buf)
		tokens.push_back(buf);

	return tokens;
}