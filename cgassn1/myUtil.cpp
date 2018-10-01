//
//  myUtil.cpp
//  cgassn1
//
//  Created by Dahun Lee on 2018. 10. 1..
//  Copyright © 2018년 Dahun Lee. All rights reserved.
//

#include "myUtil.h"

bool
keyboardBuffer [KEYBOARD_BUFFER_SIZE];

void
myUtilInit ()
{
    int i;

    for (i=0 ; i < KEYBOARD_BUFFER_SIZE ; i++)
    {
        keyboardBuffer[i] = 0;
    }
}
//
void
myKeyboardFunc (unsigned char key, int x, int y)
{
    keyboardBuffer[key] = 1;
}

void
myKeyboardUpFunc (unsigned char key, int x, int y)
{
    keyboardBuffer[key] = 0;
}
