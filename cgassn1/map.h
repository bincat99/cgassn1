//
//  map.h
//  cgassn1
//
//  Created by Dahun Lee on 2018. 10. 1..
//  Copyright © 2018년 Dahun Lee. All rights reserved.
//

#ifndef map_h
#define map_h

#include "util.h"
#include "object.h"
#include "wall.h"
#include <list>



class Map{
    float width;
    float height;
    float gridLength;

    std::list<GameObject*> listObject;
    std::list<Wall*> listWall;
    //public Map () = 0;
   
public:
    Map ();
    Map (float, float , float);
    void mapInit ();
    void display ();
};

#endif /* map_h */
