//
//  player.cpp
//  cgassn1
//
//  Created by WonJong Jang on 2018. 10. 2..
//  Copyright © 2018년 Dahun Lee. All rights reserved.
//

#include "player.h"

Player::Player(Position pos_, Direction dir_, Size size_, float speed_, Weapon* weapon_) {
	pos = pos_;
	dir = dir_;
	size = size_;
	speed = speed_;
	weapon = weapon_;
}

void Player::move(unsigned char key) {
	switch (key)
	{
	case 'a':
		pos.set(pos.x()-speed, pos.y());
		dir = LEFT;
		break;

	case 's':
		pos.set(pos.x(), pos.y() - speed);
		dir = DOWN;
		break;

	case 'd':
		pos.set(pos.x() + speed, pos.y());
		dir = RIGHT;
		break;

	case 'w':
		pos.set(pos.x(), pos.y() + speed);
		dir = UP;
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

	}
}

void Player::display() {

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


Weapon Player::getWeapon() {
	return weapon;
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

void Player::setWeapon(Weapon weapon_) {
	weapon = weapon_;
}

Player::~Player() {
}