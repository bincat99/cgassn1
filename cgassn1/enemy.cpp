#include "enemy.h"
#include "util.h"



void Enemy::init(const glm::vec3& pos, const glm::vec2& dir)
{
	this->setPos(pos);
	this->setDir(dir);
}


void Enemy::update(void)
{

}

void Enemy::display(Mesh* mesh, Camera& camera)
{

	glm::mat4 Projection = camera.toProjMatrix();
	glm::mat4 View = camera.toViewMatrix();
	float scaleFactor = mesh->getScaleFactor();
	glm::mat4 World = glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, pos.z));
	glm::mat4 Model =	glm::translate(glm::mat4(1.0f), glm::vec3(0, -2*scaleFactor, 0))
						*glm::scale(glm::mat4(1.0f),glm::vec3(scaleFactor, scaleFactor, scaleFactor));

	glm::mat4 mvp = Projection * View * World * Model;

	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
	mesh->render();
}



glm::vec3 Enemy::getPos()

{
	return this->pos;
}



void Enemy::setPos(const glm::vec3& pos)

{
	this->pos = pos;
}



glm::vec2 Enemy::getDir()
{
	return this->dir;
}

void Enemy::setDir(const glm::vec2& dir)
{
	this->dir = dir;
}

void Enemy::moveRandom()
{
	glm::vec3 tmp = pos;
	tmp.x += rand() % 3 - 1;
	tmp.z += rand() % 3 - 1;
	setPos(tmp);
}