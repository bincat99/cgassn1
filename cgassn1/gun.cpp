#include "gun.h"
#include "util.h"



void Gun::init(const glm::vec3& pos, const glm::vec2& dir)
{
	this->setPos(pos);
	this->setDir(dir);
}


void Gun::update(void)
{

}

void Gun::display(Mesh& mesh, Camera& camera)
{

	glm::mat4 Projection = camera.toProjMatrix();
	glm::mat4 View = camera.toViewMatrix();
	glm::mat4 Model = glm::mat4(1.0f);

	
	float rotX = 0.0f;
	float rotY = 20.0f;
	float rotZ = 0.0f;
	
	Model *= glm::rotate(glm::mat4(1.0f), glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f))*
		glm::rotate(glm::mat4(1.0f), glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f))*
		glm::rotate(glm::mat4(1.0f), glm::radians(rotZ), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 mvp = Projection * View * Model;

	

	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
	glEnableVertexAttribArray(0);

	mesh.getVertexBuffer()->bind();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	mesh.getVertexBuffer()->unbind();



	mesh.getIndexBuffer()->bind();

	glDrawElements(GL_LINE_STRIP, mesh.getIndexBuffer()->size(), GL_UNSIGNED_INT, 0);

	mesh.getIndexBuffer()->unbind();

	mvp = Projection * View * glm::mat4(1.0f);
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
	glEnableVertexAttribArray(0);
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
