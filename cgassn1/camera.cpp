#include "sys.h"
#include "util.h"




void Camera::init(const glm::vec3& pos, const glm::vec2& rot)

{

	this->setPos(pos);

	this->setRot(rot);



	this->rotSpeed = 1.0f;

}



void Camera::update(float delta)

{
	int i = 0;

	float yrad = glm::radians(rot.y);

	float sp = this->walkSpeed;

	for (i = 0; i < KEYBOARD_BUFFER_SIZE; i++)
	{
		if (keyboardBuffer[i])
		{
			if (i == 'a')
			{
				rot.y += this->rotSpeed;
			}

			if (i == 's')
			{
				pos.x -= sp * glm::sin(yrad) * delta;
				pos.z += sp * glm::cos(yrad) * delta;
			}


			if (i == 'd')
			{
				rot.y -= this->rotSpeed;
			}


			if (i == 'w')
			{
				pos.x += sp * glm::sin(yrad) * delta;
				pos.z -= sp * glm::cos(yrad) * delta;
			}


		}
	}

}



glm::mat4 Camera::toViewMatrix()

{

	return

		glm::rotate(glm::mat4(1.0f), glm::radians(rot.x), glm::vec3(1.0f, 0.0f, 0.0f)) *

		glm::rotate(glm::mat4(1.0f), glm::radians(rot.y), glm::vec3(0.0f, 1.0f, 0.0f)) *

		glm::translate(glm::mat4(1.0f), -this->pos);

}



glm::mat4 Camera::toProjMatrix()

{

	return glm::perspective(

		glm::radians(this->fov),

		(float)800 / (float)800,

		1.0f,

		1024.0f

	);

}



glm::vec3 Camera::getPos()

{

	return this->pos;

}



void Camera::setPos(const glm::vec3& pos)

{

	this->pos = pos;

}



glm::vec2 Camera::getRot()

{

	return this->rot;

}



void Camera::setRot(const glm::vec2& rot)

{

	this->rot = rot;

}



float Camera::getFOV()

{

	return this->fov;

}



void Camera::setFOV(float fov)

{

	this->fov = fov;

}



float Camera::getRotSpeed()

{

	return this->rotSpeed;

}



void Camera::setRotSpeed(float rotSpeed)

{

	this->rotSpeed = rotSpeed;

}