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
#include "player.h"
#include "emptySpace.h"
#include "item.h"
#include "enemy.h"
#include <list>



class Map
{
    float width;
    float height;
    float gridLength;

    std::list<GameObject*> listObject;
    std::list<Wall*> listWall;
    std::list<EmptySpace*> listEmpty;
    std::list<Enemy*> listEnemy;
    //public Map () = 0;
   
public:
    Map ();
    Map (float, float , float);
    void mapInit ();
    void display ();
    void checkWall (Player *);
    void moveEnemy (position);
};

#endif /* map_h */
