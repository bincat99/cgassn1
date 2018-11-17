#pragma once
#pragma once
#include "sys.h"

class Bullet
{
private:
	glm::vec3 pos;
	glm::vec2 dir;


	float walkSpeed = 3.0f;

public:

	Bullet(const glm::vec3& pos, const glm::vec2& rot);
	void init(const glm::vec3& pos, const glm::vec2& rot);

	void update();
	void display(Mesh*, Camera&);

	glm::vec3 getPos();

	void setPos(const glm::vec3& pos);

	glm::vec2 getDir();

	void setDir(const glm::vec2& dir);

};