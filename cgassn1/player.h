#pragma once
#include "sys.h"

class Player
{
private:
	glm::vec3 pos;
	glm::vec2 dir;
	
	float walkSpeed = 1.0f;

	clock_t rotDelay;
	clock_t lastRot;

public:
	std::string name;
	enum Direction viewDir;
	bool canGo;
	void init(const glm::vec3& pos, const glm::vec2& rot);

	void update();
	void display(Mesh*, Camera&);

	glm::vec3 getPos();

	void setPos(const glm::vec3& pos);

	glm::vec2 getDir();

	void setDir(const glm::vec2& dir);

};