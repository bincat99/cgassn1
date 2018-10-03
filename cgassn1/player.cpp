//
//  player.cpp
//  cgassn1
//
//  Created by WonJong Jang on 2018. 10. 2..
//  Copyright © 2018년 Dahun Lee. All rights reserved.
//

#include "player.h"

Player::Player(Position pos_, Direction dir_, Size size_, float speed_, Weapon* weapon_) {
	pos.set(pos_.x(), pos.y());
	dir = dir_;
	size.set(size_.w(), size_.h());
	speed = speed_;
	weapon = weapon_;
	isWall = {false, false, false, false};
}

void Player::move(unsigned char key) {
	switch (key)
	{
	case 'a':
		if(!isWall[2]){
			pos.set(pos.x()-speed, pos.y());
			dir = LEFT;
		}
		break;

	case 's':
		if(!isWall[1]) {
			pos.set(pos.x(), pos.y() - speed);
			dir = DOWN;
		}
		break;

	case 'd':
		if(!isWall[3]) {
			pos.set(pos.x() + speed, pos.y());
			dir = RIGHT;
		}
		break;

	case 'w':
		if(!isWall[0]) {
			pos.set(pos.x(), pos.y() + speed);
			dir = UP;
		}
		break;
	}
	glutPostRedisplay();
}

void Player::shoot() {
	Size bullet_size = Size(0.5, 0.5);
	float bullet_speed = 0.01;
	float bullet_range = 0.3;
	Weapon bullet = Weapon(pos, dir, bullet_size,  bullet_speed, bullet_range);
	bullet.move();
	bullet.display();
}

void Player::useItem(unsigned char key) {
	if (key == 'i') {
		// use item
	}
}

void Player::display() {
	if(Status == ALIVE) {
		// DISPLAY
	}
	else {
		// DO NOT THING
	}

}


// Basic GET/SET method
Position Player::getPos() {
	return pos;
}

Direction Player::getDir() {
	return dir;
}

Size Player::getSize() {
	return size;
}

float Player::getSpeed() {
	return speed;
}


Weapon* Player::getWeapon() {
	return weapon;
}

Status Player::getStatus() {
	return Status;
}

void Player::setPos(Position pos_) {
	pos = pos_;
}

void Player::setDir(Direction dir_) {
	dir = dir_;
}

void Player::setSize(Size size_) {
	size = size_;
}

void Player::setSpeed(float speed_) {
	speed = speed_;
}

void Player::setWeapon(Weapon* weapon_) {
	weapon = weapon_;
}

void Player::checkWall(bool dirWall[4]) {
	isWall[0] = dirWall[0];
	isWall[1] = dirWall[1];
	isWall[2] = dirWall[2];
	isWall[3] = dirWall[3];
}

void Player::killed() {
	Status = KILLED;
}

Player::~Player() {
}