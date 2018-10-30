//
//  main.cpp
//  cgassn1
//
//  Created by Dahun Lee on 2018. 10. 1..
//  Copyright © 2018년 Dahun Lee. All rights reserved.
//


#include <iostream>

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

#include "game.h"
#include "util.h"


using namespace std;


typedef struct rect{ float x;
    float y; float width; float height;
} rect;
rect rectangle;


Game * game;

void
init (void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glShadeModel (GL_FLAT);
	shaderUtil.Load("cgassn1/shaders/vs.shader", "cgassn1/shaders/fs.shader");
    
    game->init ();
}

void
display (void)
{


	matrix_loc = glGetUniformLocation(shaderUtil.getProgram(), "transform");


	shaderUtil.Use();
	glClear(GL_COLOR_BUFFER_BIT);
	game->display();
	glutSwapBuffers();
	shaderUtil.Delete();
    
}

void
reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	/*
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();

    //gluOrtho2D(0, 1000, 0, 1000);
    gluOrtho2D(0, 800, 0, 800);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();*/

}
void
moveObjects()
{
	game->moveObjects();
    glutPostRedisplay();
}


int
main (int argc, char * argv[])
{
    utilInit ();
    
    glutInit (& argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(200, 150);
    glutInitWindowSize(800, 800);
    windowId = glutCreateWindow("assn2");
    //    glutDisplayFunc(renderScene);
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

	game = new Game();

	glewInit();
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(moveObjects);
    glutKeyboardFunc (myKeyboardFunc);
    glutKeyboardUpFunc (myKeyboardUpFunc);
    glutSpecialFunc(mySpecialFunc);
    glutSpecialUpFunc(mySpecialUpFunc);
    glutMainLoop();
}
