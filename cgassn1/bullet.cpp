#include "bullet.h"
#include "util.h"


Bullet::Bullet(const glm::vec3& pos, const glm::vec2& dir)
{
	this->setPos(pos);
	this->setDir(dir);

}

void Bullet::init(const glm::vec3& pos, const glm::vec2& dir)
{
	this->setPos(pos);
	this->setDir(dir);
}


void Bullet::update()
{
	float yrad = glm::radians(dir.y);

	float sp = this->walkSpeed;
	pos.x += sp * glm::sin(yrad);
	pos.z -= sp * glm::cos(yrad);
}


void Bullet::display(Mesh* mesh, Camera& camera)
{
	float yrad = glm::radians(dir.y);

	glm::mat4 Projection = camera.toProjMatrix();
	glm::mat4 View = camera.toViewMatrix();
	float scaleFactor = mesh->getScaleFactor();
	glm::mat4 World = glm::translate(glm::mat4(1.0f), glm::vec3(pos.x + 30.f * glm::sin(yrad), pos.y+40, pos.z - 30.0f*glm::cos(yrad)));
	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(scaleFactor/10, scaleFactor/10, scaleFactor/10));

	glm::mat4 mvp = Projection * View * World * Model;

	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
	mesh->render();
}



glm::vec3 Bullet::getPos()

{
	return this->pos;
}



void Bullet::setPos(const glm::vec3& pos)

{
	this->pos = pos;
}



glm::vec2 Bullet::getDir()

{

	return this->dir;

}



void Bullet::setDir(const glm::vec2& dir)
{
	this->dir = dir;
}

