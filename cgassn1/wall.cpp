#include "wall.h"
#include "util.h"



void Wall::init(const glm::vec3& pos, const glm::vec2& dir)
{
	this->setPos(pos);
	this->setDir(dir);
}


void Wall::update(void)
{

}

void Wall::display(Mesh& mesh, Camera& camera)
{

	glm::mat4 Projection = camera.toProjMatrix();
	glm::mat4 View = camera.toViewMatrix();
	glm::mat4 Model = glm::mat4(1.0f);

	glm::mat4 mvp = Projection * View * Model;

	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
	glEnableVertexAttribArray(0);

	mesh.getVertexBuffer()->bind();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	mesh.getVertexBuffer()->unbind();



	mesh.getIndexBuffer()->bind();

	glDrawElements(GL_LINE_STRIP, mesh.getIndexBuffer()->size(), GL_UNSIGNED_INT, 0);

	mesh.getIndexBuffer()->unbind();
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
