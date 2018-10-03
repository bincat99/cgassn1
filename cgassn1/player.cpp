#include "player.h"

Player::Player(float x_, float y_, enum Direction dir_, float w_, float h_, float speed_/*, Weapon* weapon_*/) {
	x = x_;
	y = y_;
	dir = dir_;
	w = w_;
	h = h_;
	speed = speed_;
	//weapon = weapon_;

}

Player::~Player() {
}