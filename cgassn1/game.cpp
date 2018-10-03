//
//  game.cpp
//  cgassn1
//
//  Created by Dahun Lee on 2018. 10. 1..
//  Copyright © 2018년 Dahun Lee. All rights reserved.
//


#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#include <GLUT/GLUT.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#include "game.h"
#include "myUtil.h"
#include <stdio.h>
using namespace std;

void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

void
init_ (void);

void
display (void);

void
reshape (int, int);

void
moveObjects(void);

void
myKeyboardFuncMain (unsigned char Key, int x, int y);

Game::Game()
{
    map = new Map();
    player = new Player();
    enemy = new Enemy ();
}


void
Game::init (int * argc, char ** argv)
{
    myUtilInit ();
    
    glutInit (argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowPosition(200, 150);
    glutInitWindowSize(1024, 768);
    glutCreateWindow("Hello OpenGL");
    //    glutDisplayFunc(renderScene);
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
#ifndef __APPLE__
    glewInit();
#endif
    
    init_ ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(moveObjects);
    glutKeyboardFunc (myKeyboardFunc);
    glutKeyboardUpFunc (myKeyboardUpFunc);
    glutSpecialFunc(mySpecialFunc);
    glutSpecialUpFunc(mySpecialUpFunc);
    glutMainLoop();
    
    
}



typedef struct rect{ float x;
    float y; float width; float height;
} rect;
rect rectangle;

void
init_ (void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glShadeModel (GL_FLAT);
    rectangle.x = 0.1; rectangle.y = 0.1; rectangle.width = 0.1; rectangle.height = 0.10;
}

void
display (void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(rectangle.x, rectangle.y);
    glVertex2f(rectangle.x, rectangle.y + rectangle.width);
    glVertex2f(rectangle.x + rectangle.height, rectangle.y + rectangle.width);
    glVertex2f(rectangle.x + rectangle.height, rectangle.y);
    glEnd();
    glutSwapBuffers();
    
}

void
reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluOrtho2D(0, 1, 0, 1);
    glMatrixMode (GL_MODELVIEW); glLoadIdentity();
}
void
moveObjects()
{
    //rectangle.x += 0.001; rectangle.y += 0.001;
    int i = 0;
    for (i = 0; i < KEYBOARD_BUFFER_SIZE; i++)
    {
        if (keyboardBuffer[i])
        {
            if (i == 'a')
                rectangle.x -= 0.005;
            
            if (i == 's')
                rectangle.y -= 0.005;
            
            
            if (i == 'd')
                rectangle.x += 0.005;
            
            
            if (i == 'w')
                rectangle.y += 0.005;
            
            
        }
        
        if (specialKeyBuffer[i])
        {
            if (i == GLUT_KEY_LEFT)
                rectangle.x -= 0.005;
            
            if (i == GLUT_KEY_UP)
                rectangle.y += 0.005;
            
            
            if (i == GLUT_KEY_RIGHT)
                rectangle.x += 0.005;
            
            if (i == GLUT_KEY_DOWN)
                rectangle.y -= 0.005;
        
        }
    }
    glutPostRedisplay();
}


void
myKeyboardFuncMain (unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'a':
            rectangle.x -= 0.005;
            break;
            
        case 's':
            rectangle.y -= 0.005;
            break;
            
        case 'd':
            rectangle.x += 0.005;
            break;
            
        case 'w':
            rectangle.y += 0.005;
            break;
            
            
    }
    glutPostRedisplay();
}
