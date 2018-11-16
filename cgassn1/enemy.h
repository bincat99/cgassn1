#pragma once
#include "sys.h"

class Enemy
{
private:
	glm::vec3 pos;
	glm::vec2 dir;


	float walkSpeed = 1.0f;

public:

	void init(const glm::vec3& pos, const glm::vec2& rot);

	void update();
	void display(Mesh*, Camera&);

	glm::vec3 getPos();

	void setPos(const glm::vec3& pos);

	glm::vec2 getDir();

	void setDir(const glm::vec2& dir);

};