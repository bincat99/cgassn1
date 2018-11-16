//
//  main.cpp
//  cgassn1
//
//  Created by Dahun Lee on 2018. 10. 1..
//  Copyright © 2018??Dahun Lee. All rights reserved.
//


#include <iostream>
#include <stdlib.h>
#include <time.h>

#include <windows.h>
#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

#include "util.h"
#include "sys.h"
#include "enemy.h"
#include "player.h"
#include "gun.h"
#include "wall.h"

using namespace std;


GLuint vertexbuffer;
GLuint uvbuffer;
GLuint MatrixID;


Mesh* M_enemy = new Mesh();
Mesh* M_gun = new Mesh();
Mesh* M_player = new Mesh();
Mesh* M_wall = new Mesh();

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
	M_enemy->init("cgassn1/resources/Skeleton.obj");
	M_player->init("cgassn1/resources/dummy_obj.obj");
	M_gun->init("cgassn1/resources/M1911.obj");
	M_wall->init("cgassn1/resources/cube.obj");
	camera.init(glm::vec3(0, 45, 100), glm::vec2(0.0f, 0.0f));
	enemy.init(glm::vec3(0, 0, 50), glm::vec2(0.0f, 0.0f));
	player.init(glm::vec3(0, 0, 100), glm::vec2(0.0f, 0.0f));
	gun.init(glm::vec3(0, 0, 80), glm::vec2(0.0f, 0.0f));
	// need to be iterative
	wall.init(glm::vec3(-30, 0, 0), glm::vec2(0.0f, 0.0f));

	srand(time(NULL));
}

void
display(void)
{
	shaderUtil.Use();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glm::mat4 Projection = camera.toProjMatrix();

	glm::mat4 View = camera.toViewMatrix();

	glm::mat4 World = glm::mat4(1.0f);

	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 mvp = Projection * View * World * Model;

	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

	glBegin(GL_LINES);
	glVertex3f(.0f, .0f, .0f);
	glVertex3f(10000.0f, .0f, .0f);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(.0f, .0f, .0f);
	glVertex3f(0.0f, 100.0f, .0f);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(.0f, .0f, .0f);
	glVertex3f(0.0f, .0f, 50.0f);
	glEnd();


	wall.display(M_wall, camera);
	enemy.display(M_enemy, camera);
	player.display(M_player, camera);
	gun.display(M_gun, camera);

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

	glm::vec3 tmp = camera.getPos();
	//tmp.z += 50.f;
	tmp.y -= 45.0f;
	player.setPos(tmp);
	tmp.z -= 20.f;
	gun.setPos(tmp);

	glm::vec2 rot = camera.getRot();
	player.setDir(rot);
	gun.setDir(rot);
	glutPostRedisplay();
	//enemy.moveRandom();
	//printf("%f, %f\n", player.getPos().y, enemy.getPos().y);
	printf("%f\n", glm::distance(player.getPos(), enemy.getPos()));

	gun.update ();
	if (mouseBuffer[GLUT_LEFT_BUTTON])
	{

	}
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
	glutMouseFunc(myMouseFunc);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutMainLoop();
}
