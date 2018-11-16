#include "gun.h"
#include "util.h"



void Gun::init(const glm::vec3& pos, const glm::vec2& dir)
{
	this->setPos(pos);
	this->setDir(dir);
}


void Gun::update(void)
{
	if (mouseBuffer[GLUT_LEFT_BUTTON])
	{
		printf("SHOT\n");
		//glutLeaveMainLoop();
	}
}


void Gun::display(Mesh* mesh, Camera& camera)
{

	glm::mat4 Projection = camera.toProjMatrix();
	glm::mat4 View = glm::rotate(glm::mat4(1.0f), glm::radians(-camera.getRot().y), glm::vec3(0.0f, 1.0f, 0.0f))
						*camera.toViewMatrix();
	float scaleFactor = mesh->getScaleFactor();
	glm::mat4 World = glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, pos.z));
	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(scaleFactor, scaleFactor, scaleFactor));

	glm::mat4 mvp = Projection * View * World * Model;

	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
	mesh->render();
}



glm::vec3 Gun::getPos()

{
	return this->pos;
}



void Gun::setPos(const glm::vec3& pos)

{
	this->pos = pos;
}



glm::vec2 Gun::getDir()

{

	return this->dir;

}



void Gun::setDir(const glm::vec2& dir)
{
	this->dir = dir;
}

