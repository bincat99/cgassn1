//
//  map.cpp
//  cgassn1
//
//  Created by Dahun Lee on 2018. 10. 1..
//  Copyright © 2018년 Dahun Lee. All rights reserved.
//

#include "map.h"

Map::Map()
{
    
}


void Map::mapInit()
{
    glutInitWindowPosition(200, 150);
    glutInitWindowSize(1024, 768);
    glutCreateWindow("Hello OpenGL");
    //    glutDisplayFunc(renderScene);
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
}
