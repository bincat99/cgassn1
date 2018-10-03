//
//  emptySpace.h
//  cgassn1
//
//  Created by Dahun Lee on 2018. 10. 1..
//  Copyright © 2018년 Dahun Lee. All rights reserved.
//

#ifndef emptySpace_h
#define emptySpace_h

#include "object.h"
#include "util.h"

class EmptySpace : virtual public GameObject
{
    position pos;
public:
    position getPos();
    void display ();
};

#endif /* emptySpace_h */
