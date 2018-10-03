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
#include <GL/GL.h>
#include <GL/GLU.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#endif


#define KEYBOARD_BUFFER_SIZE 256


enum Direction { LEFT, UP, RIGHT, DOWN };
enum Status { ALIVE, KILLED };

extern bool
keyboardBuffer [KEYBOARD_BUFFER_SIZE];


extern bool
specialKeyBuffer [KEYBOARD_BUFFER_SIZE];

typedef struct
{
    float x;
    float y;
}pos;


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
#endif /* util_h */
