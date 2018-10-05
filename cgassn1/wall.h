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
#include "BmpLoader.h"


class Wall : virtual public GameObject
{
    position pos;
    float width;
    float height;
    
	int sprite = 0;
	unsigned int textureID;

	BmpLoader* bl[1];

	bool is_loaded = false;
    
    
public:
    Wall (float x, float y);
    position getPos();
    void display ();
	void LoadTexture(unsigned int);
	~Wall();
};




#endif /* wall_h */
