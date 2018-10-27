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
#include "weapon.h"
#include "item.h"
#include "enemy.h"
#include <list>



class Map
{
    float width;
    float height;
    float gridLength;
    
    enum ObjectType objMap[32][32];

    std::list<GameObject*> listObject;
    std::list<Wall*> listWall;
    std::list<EmptySpace*> listEmpty;
    std::list<Enemy*> listEnemy;
    std::list<Item*> listItem;
    //public Map () = 0;
   
public:
    Map ();
    Map (float, float , float);
    ~Map ();
    
    void mapInit ();
    void display ();
    void checkWall (Player *);
    void checkItem (Player *);
    void checkPlayerKill (Player *);
    void checkWallEnemy ();
    void cleanWallEnemy ();
    void moveEnemy (position);
    
    void checkWallWeapon (std::list<Weapon*>);
  
    
    void checkEnemyKill (std::list<Weapon*>);
};

#endif /* map_h */
