#ifndef _LOADER_H

#define _LOADER_H



#include "GL/glew.h"

#include "glm/vec3.hpp"



class Loader

{

private:

	int numElements;

	GLuint vaoID;

	GLuint vbos[1];

public:

	Loader();

	~Loader();

	void load(glm::vec3[], int, unsigned int);

	void clean();

	void add(glm::vec3[], int);

	void genBuffers();

	GLuint getVaoId();

	int getNumElements();

};



#endif _LOADER_H