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

using namespace std;
std::vector<glm::vec3> vertices;
std::vector<glm::vec2> uvs;
std::vector<glm::vec3> normals;

GLuint vertexbuffer;
GLuint uvbuffer;
GLuint MatrixID;

static Mesh object;
static Camera camera;

void
init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	shaderUtil.Load("cgassn1/shaders/vs.shader", "cgassn1/shaders/fs.shader");
	MatrixID = glGetUniformLocation(shaderUtil.getProgram(), "MVP");

}

void
display(void)
{
	shaderUtil.Use();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::mat4 Projection = camera.toProjMatrix();


	// 카메라 매트릭스
	glm::mat4 View = camera.toViewMatrix();

	//glm::mat4 View = glm::lookAt(
	//	glm::vec3(40, 30, 30),
	//	glm::vec3(0, 0, 0),
	//	glm::vec3(0, 1, 0)
	//);

	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 mvp = Projection * View * Model;

	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
	glEnableVertexAttribArray(0);

	object.getVertexBuffer()->bind();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	object.getVertexBuffer()->unbind();



	object.getIndexBuffer()->bind();

	glDrawElements(GL_LINE_STRIP, object.getIndexBuffer()->size(), GL_UNSIGNED_INT, 0);

	object.getIndexBuffer()->unbind();

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


	object.init("cgassn1/resources/M1911.obj");
	camera.init(glm::vec3(40, 30, 100), glm::vec2(0.0f, 0.0f));


	glGenBuffers(1, &vertexbuffer);

	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);






	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(moveObjects);
	glutKeyboardFunc(myKeyboardFunc);
	glutKeyboardUpFunc(myKeyboardUpFunc);
	glutSpecialFunc(mySpecialFunc);
	glutSpecialUpFunc(mySpecialUpFunc);
	glutMainLoop();
}
