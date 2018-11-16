#include "player.h"
#include "util.h"



void Player::init(const glm::vec3& pos, const glm::vec2& dir)
{
	this->setPos(pos);
	this->setDir(dir);
}


void Player::update(void)
{

}


void Player::display(Mesh* mesh, Camera& camera)
{
	glm::mat4 Projection = camera.toProjMatrix();
	glm::mat4 View = camera.toViewMatrix();
	float scaleFactor = mesh->getScaleFactor();
	glm::mat4 World = glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, pos.z));
	glm::mat4 Model =	glm::rotate(glm::mat4(1.0f), glm::radians(- camera.getRot().y), glm::vec3(0.0f, 1.0f, 0.0f))
						* glm::scale(glm::mat4(1.0f), glm::vec3(scaleFactor, scaleFactor, scaleFactor));

	glm::mat4 mvp = Projection * View * World * Model;

	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
	mesh->render();
}


glm::vec3 Player::getPos()

{

	return this->pos;

}



void Player::setPos(const glm::vec3& pos)

{

	this->pos = pos;

}



glm::vec2 Player::getDir()

{

	return this->dir;

}



void Player::setDir(const glm::vec2& dir)
{
	this->dir = dir;
}
