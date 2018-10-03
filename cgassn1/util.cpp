//
//  util.cpp
//  cgassn1
//
//  Created by Dahun Lee on 2018. 10. 1..
//  Copyright © 2018년 Dahun Lee. All rights reserved.
//

#include "util.h"


Position::Position() {
	x_ = 0.0;
	y_ = 0.0;
}
Position::Position(float x__, float y__) {
	x_ = x__;
	y_ = y__;
}

Position::~Position() {

}

float Position:: x() {
	return x_;
}

float Position::y() {
	return y_;
}

void Position::set(float x, float y) {
	x_ = x;
	y_ = y;
}


Size::Size() {

}

Size::Size(float w__, float h__) {
	w_ = w__;
	h_ = h__;
}

Size::~Size() {
	
}

float Size::w() {
	return w_;
}

float Size::h() {
	return h_;
}

void Size::set(float w, float h) {
	w_ = w;
	h_ = h;
}