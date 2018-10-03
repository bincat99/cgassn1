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
#include <windows.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#endif

#include "game.h"
#include "util.h"
#include <stdio.h>
using namespace std;

void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

void
init_(void) {

}

static void
display (void);

static void
reshape (int, int);

void
moveObjects(void);


Game::Game()
{/*
    map = new Map();
    player = new Player();
    enemy = new Enemy ();*/
}


void
Game::init (int * argc, char ** argv)
{
    utilInit ();
    
    glutInit (argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(200, 150);
    glutInitWindowSize(1024, 768);
    glutCreateWindow("Hello OpenGL");
    //    glutDisplayFunc(renderScene);
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	/*
#ifndef __APPLE__
    glewInit();
#endif
    */
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
Game::init_ (void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glShadeModel (GL_FLAT);
	player = new Player(0.1, 0.2, UP, 0.1, 0.2, 0.005);
}

void
Game::display (void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
	player->display();
    glutSwapBuffers();
    
}

void
Game::reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluOrtho2D(0, 1, 0, 1);
    glMatrixMode (GL_MODELVIEW); glLoadIdentity();
}
void
Game::moveObjects()
{
    //rectangle.x += 0.001; rectangle.y += 0.001;
	player->move();
    glutPostRedisplay();
}
