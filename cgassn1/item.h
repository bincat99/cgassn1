//
//  item.h
//  cgassn1
//
//  Created by Dahun Lee on 2018. 10. 1..
//  Copyright © 2018년 Dahun Lee. All rights reserved.
//

#ifndef item_h
#define item_h

#include "object.h"
#include "util.h"
#include "BmpLoader.h"

class Item : virtual public GameObject
{
    enum ItemType type;
    position pos;
    float width;
    float height;

	unsigned int textureID;

	BmpLoader* bl[2];

public:
    position getPos();
    void display ();
	void LoadTexture(unsigned int);
    Item (float , float , enum ItemType);
    ~Item ();
};

#endif /* item_h */
