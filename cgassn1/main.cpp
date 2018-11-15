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

#include "util.h"
#include "sys.h"
#include "enemy.h"
#include "player.h"
#include "gun.h"
#include "wall.h"

using namespace std;


static Mesh M_enemy;
static Mesh M_gun;
static Mesh M_player;
static Mesh M_wall;

static Camera camera;

static Enemy enemy;
static Player player;
static Gun gun;
static Wall wall;

void
init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	shaderUtil.Load("cgassn1/shaders/vs.shader", "cgassn1/shaders/fs.shader");
	MatrixID = glGetUniformLocation(shaderUtil.getProgram(), "MVP");
	M_enemy.init("cgassn1/resources/Skeleton.obj");
	M_player.init("cgassn1/resources/dummy_obj.obj");
	M_gun.init("cgassn1/resources/M1911.obj");
	M_wall.init("cgassn1/resources/cube.obj");
	camera.init(glm::vec3(40, 30, 100), glm::vec2(0.0f, 0.0f));
	enemy.init(glm::vec3(0, 0, 0), glm::vec2(0.0f, 0.0f));
	player.init(glm::vec3(0, 0, 0), glm::vec2(0.0f, 0.0f));
	gun.init(glm::vec3(0, 0, 0), glm::vec2(0.0f, 0.0f));
	// need to be iterative
	wall.init(glm::vec3(0, 0, 0), glm::vec2(0.0f, 0.0f));

}

void
display(void)
{
	shaderUtil.Use();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	enemy.display(M_enemy, camera);
	player.display(M_player, camera);
	gun.display(M_gun, camera);
	wall.display(M_wall, camera);



	glutSwapBuffers();
	shaderUtil.Delete();

}

void
reshape(int w, int h)
{

}
void
moveObjects()
{
	camera.update(1.0);
	glutPostRedisplay();
}


int
main(int argc, char * argv[])
{
	utilInit();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(200, 150);
	glutInitWindowSize(800, 800);
	windowId = glutCreateWindow("assn3");
	//    glutDisplayFunc(renderScene);
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);


	glewInit();
	init();





	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(moveObjects);
	glutKeyboardFunc(myKeyboardFunc);
	glutKeyboardUpFunc(myKeyboardUpFunc);
	glutSpecialFunc(mySpecialFunc);
	glutSpecialUpFunc(mySpecialUpFunc);
	glutMainLoop();
}
