//
//  wall.h
//  cgassn1
//
//  Created by Dahun Lee on 2018. 10. 1..
//  Copyright © 2018년 Dahun Lee. All rights reserved.
//

#ifndef wall_h
#define wall_h

#include "object.h"

class Wall : virtual public GameObject
{
    position pos;
    float width;
    float height;
    
    
    
public:
    Wall (float x, float y);
    position getPos();
    void display ();
};




#endif /* wall_h */
