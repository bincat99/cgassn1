//
//  main.cpp
//  cgassn1
//
//  Created by Dahun Lee on 2018. 10. 1..
//  Copyright © 2018년 Dahun Lee. All rights reserved.
//

#include <iostream>

//#include "map.h"
//#include "enemy.h"
//#include "player.h"
//#include "weapon.h"
#include "game.h"


using namespace std;


int
main (int argc, char * argv[])
{
    Game *game = new Game();
    
    //glutInit (&argc, argv);
    game->init(&argc, argv);
    //    glutInitWindowPosition(100, 100);
    //    glutInitWindowSize(1024, 768);
    //    glutCreateWindow("Hello OpenGL");
    ////    glutDisplayFunc(renderScene);
    //    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    //#ifndef __APPLE__
    //    glewInit();
    //#endif
    //    init_ ();
    //    glutDisplayFunc(display);
    //    glutReshapeFunc(reshape);
    //    //glutIdleFunc(moveObjects);
    //    glutKeyboardFunc (myKeyboardFuncMain);
    //    glutMainLoop();
}
//
//typedef struct rect{ float x;
//    float y; float width; float height;
//} rect;
//rect rectangle;
//
//void
//init_ (void)
//{
//    glClearColor (0.0, 0.0, 0.0, 0.0); glShadeModel (GL_FLAT);
//    rectangle.x = 0.1; rectangle.y = 0.1; rectangle.width = 0.1; rectangle.height = 0.15;
//}
//
//void
//display (void)
//{
//    glClear(GL_COLOR_BUFFER_BIT);
//    glColor3f(1.0, 1.0, 1.0); glBegin(GL_LINE_LOOP);
//    glVertex2f(rectangle.x, rectangle.y);
//    glVertex2f(rectangle.x, rectangle.y + rectangle.width);
//    glVertex2f(rectangle.x + rectangle.height, rectangle.y + rectangle.width);
//    glVertex2f(rectangle.x + rectangle.height, rectangle.y);
//    glEnd();
//    glutSwapBuffers();
//
//}
//
//void
//reshape(int w, int h)
//{
//    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
//    glMatrixMode (GL_PROJECTION);
//    glLoadIdentity ();
//    gluOrtho2D(0, 1, 0, 1);
//    glMatrixMode (GL_MODELVIEW); glLoadIdentity();
//}
//void
//moveObjects()
//{
//    rectangle.x += 0.001; rectangle.y += 0.001;
//    glutPostRedisplay();
//}
//
//
//void
//myKeyboardFuncMain (unsigned char key, int x, int y)
//{
//    switch (key)
//    {
//        case 'a':
//             rectangle.x -= 0.005;
//            break;
//
//        case 's':
//            rectangle.y -= 0.005;
//            break;
//
//        case 'd':
//             rectangle.x += 0.005;
//            break;
//
//        case 'w':
//            rectangle.y += 0.005;
//            break;
//
//
//    }
//     glutPostRedisplay();
//}
