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
#endif
using namespace std;
void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

int main(int argc, char * argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(320, 320);
    glutCreateWindow("Hello OpenGL");
    glutDisplayFunc(renderScene);
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
#ifndef __APPLE__
    glewInit();
#endif
    glutMainLoop();
}
