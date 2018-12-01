#include "wall.h"
#include "util.h"


Wall::Wall()
{

}

Wall::Wall(float x, float y)
{
	glm::vec3 pos = glm::vec3(x, 0, y);
	glm::vec2 dir = glm::vec2(0, 0);

	setPos(pos);
	setDir(dir);
}

void Wall::init(const glm::vec3& pos, const glm::vec2& dir)
{
	this->setPos(pos);
	this->setDir(dir);
}


void Wall::update(void)
{

}

void Wall::display(Mesh* mesh, Camera& camera, int frame)
{
	glm::mat4 Projection = camera.toProjMatrix();
	glm::mat4 View = camera.toViewMatrix();
	float scaleFactor = mesh->getScaleFactor();
	glm::mat4 World = glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, pos.z));
	glm::mat4 Model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 1 * scaleFactor, 0))*glm::scale(glm::mat4(1.0f), glm::vec3(scaleFactor, scaleFactor, scaleFactor));

	glm::mat4 mw = World * Model;

	glUniformMatrix4fv(projID, 1, GL_FALSE, &Projection[0][0]);
	glUniformMatrix4fv(viewID, 1, GL_FALSE, &View[0][0]);
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &mw[0][0]);

	mesh->render(frame);
}



glm::vec3 Wall::getPos()

{

	return this->pos;

}



void Wall::setPos(const glm::vec3& pos)

{

	this->pos = pos;

}



glm::vec2 Wall::getDir()

{

	return this->dir;

}



void Wall::setDir(const glm::vec2& dir)
{
	this->dir = dir;
}
