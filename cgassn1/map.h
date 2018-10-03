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

class Map{
    float width;
    float height;
    float gridLength;

    //public Map () = 0;
public:
    Map ();
    Map (float, float , float );
    void mapInit ();
    void display ();
};

#endif /* map_h */
