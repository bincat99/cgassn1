//
//  myUtil.cpp
//  cgassn1
//
//  Created by Dahun Lee on 2018. 10. 1..
//  Copyright © 2018년 Dahun Lee. All rights reserved.
//

#include "myUtil.h"
#include <stdio.h>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#include <GLUT/GLUT.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

bool
keyboardBuffer [KEYBOARD_BUFFER_SIZE];


bool
specialKeyBuffer [KEYBOARD_BUFFER_SIZE];

void
myUtilInit ()
{
    int i;
    
    for (i=0 ; i < KEYBOARD_BUFFER_SIZE ; i++)
    {
        keyboardBuffer[i] = false;
        specialKeyBuffer[i] = false;
    }
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
