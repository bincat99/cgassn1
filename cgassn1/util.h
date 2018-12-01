//
//  util.h
//  cgassn1
//
//  Created by Dahun Lee on 2018. 10. 1..
//  Copyright © 2018??Dahun Lee. All rights reserved.
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
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <time.h>
#include <list>
#include "ShaderUtil.h"
#include "sys.h"



#include <iostream>


#define KEYBOARD_BUFFER_SIZE 256
#define GLOBAL_GRID_LENGTH 50
#define MOUSE_BUFFER_SIZE 3

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

extern bool
mouseBuffer[MOUSE_BUFFER_SIZE];

extern unsigned mouseBefore;

typedef struct
{
    float x;
    float y;
}position;

// This is for a shader uniform block
struct MyMaterial {

	float diffuse[4];
	float ambient[4];
	float specular[4];
	float emissive[4];
	float shininess;
	int texCount;
};

extern ShaderUtil shaderUtil;


extern GLuint projID;
extern GLuint viewID;
extern GLuint modelID;
extern GLuint materialUniLoc;
extern GLuint texUnit;

extern GLuint ani;


extern
std::map<std::string, GLuint> textureIdMap;

extern GLuint vertexbuffer;
extern GLuint uvbuffer;

extern ShaderUtil shaderWallUtil;
extern GLuint wallProgramID;
extern GLuint MatrixID;
extern GLuint ViewMatrixID;
extern GLuint ModelMatrixID;
extern GLuint ModelView3x3MatrixID;

extern GLuint DiffuseTexture;
extern GLuint NormalTexture;
extern GLuint SpecularTexture;

extern GLuint DiffuseTextureID;
extern GLuint NormalTextureID;
extern GLuint SpecularTextureID;

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

void
myMouseFunc(int, int, int, int);

void
myMouseUpFunc(int, int, int, int);

unsigned int
CheckCollision (position , position );

unsigned int
CheckCollisionWeapon (position , position );

float
calDistance (float x1, float y1, float x2, float y2);

void
renderbitmap(float x, float y,float z, void*font, char* string);


int
pos2idx(float);

float
idx2pos(int);

std::vector<std::string> split_string(std::string str);


void set_float4(float f[4], float a, float b, float c, float d);

void color4_to_float4(const aiColor4D *c, float f[4]);

#endif /* util_h */


