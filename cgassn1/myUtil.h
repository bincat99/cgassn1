//
//  myUtil.h
//  cgassn1
//
//  Created by Dahun Lee on 2018. 10. 1..
//  Copyright © 2018년 Dahun Lee. All rights reserved.
//

#ifndef myUtil_h
#define myUtil_h

#define KEYBOARD_BUFFER_SIZE 256

extern bool
keyboardBuffer [KEYBOARD_BUFFER_SIZE];


extern bool
specialKeyBuffer [KEYBOARD_BUFFER_SIZE];


void
myUtilInit ();

void
myKeyboardFunc (unsigned char, int, int);

void
myKeyboardUpFunc (unsigned char, int, int);

void
mySpecialFunc (int key, int x, int y);

void
mySpecialUpFunc (int key, int x, int y);
#endif /* myUtil_h */
