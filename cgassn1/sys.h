#pragma once

#include <stdio.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <limits>

//#include <SDL/SDL.h>
// <SDL/SDL_ttf.h>

//#include <freeimage/FreeImage.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>


#include <GL/glew.h>
#include <assimp/scene.h>
//#include <rapidjson/document.h>

//#include <BP/btBulletDynamicsCommon.h>

//#include <LUA/lua.hpp>


// Vertex Buffer
class VertexBuffer
{
private:
	uint32_t id;
	std::vector<float> list;
	bool isStatic;
public:
	
	void add(float x);
	void add(float x, float y);
	void add(const glm::vec2& v);
	void add(float x, float y, float z);
	void add(const glm::vec3& v);
	void add(float x, float y, float z, float w);
	void add(const glm::vec4& v);
	void add(const glm::mat4& m);
	void addAll(std::vector<float>& v);
	void addAll(std::vector<glm::vec2>& v);
	void addAll(std::vector<glm::vec3>& v);
	void addAll(std::vector<glm::vec4>& v);
	void addAll(std::vector<glm::mat4>& m);
	void clear();
	void create(bool isStatic = false);
	void upload();
	void bind();
	void unbind();
	void release();
	uint32_t size();
};


// Index Buffer
class IndexBuffer
{
private:
	uint32_t id;
	std::vector<uint32_t> list;
public:
	void add(uint32_t x);
	void add(uint32_t x, uint32_t y);
	void add(uint32_t x, uint32_t y, uint32_t z);
	void add(uint32_t x, uint32_t y, uint32_t z, uint32_t w);
	void addAll(std::vector<uint32_t>& v);
	void addAll(std::vector<glm::ivec2>& v);
	void addAll(std::vector<glm::ivec3>& v);
	void addAll(std::vector<glm::ivec4>& v);
	void clear();
	void create();
	void upload();
	void bind();
	void unbind();
	void release();
	uint32_t size();
};

struct MyMesh {

	GLuint vao;
	GLuint texIndex;
	GLuint uniformBlockIndex;
	int numFaces;
};

class Mesh
{
private:
	std::vector<struct MyMesh> myMeshes;

	std::vector<aiNode*> ai_nodes;

	std::vector<glm::mat4> saved_matrices0;
	std::vector<glm::mat4> saved_matrices1;
	std::vector<glm::mat4> saved_matrices2;
	std::vector<glm::mat4> saved_matrices3;

	std::vector<float *> matrixStack;
	float current_matrix[16];

	float scaleFactor;

	int type;

	bool isStatic;
	unsigned int sprite = 0;
	unsigned int fps = 0;
public:

	Mesh();
	void init(std::string path, bool isStatic = false);
	void Mesh::render();
	//void render(ProgramWrapperMain& prog);

	void get_bounding_box(const aiScene* scene, aiVector3D* min, aiVector3D* max);
	void get_bounding_box_for_node(const aiScene* scene, const aiNode* nd,
		aiVector3D* min,
		aiVector3D* max);
	float getScaleFactor(void);
	void recursiveNodeProcess(aiNode *);
	void pushMatrix();
	void popMatrix();
	void saveMatrix(int);
};

enum MODE
{
	FPS,
	TPS
};
class Camera

{

private:

	glm::vec3 pos;

	glm::vec2 rot;

	float fov = 45.0f;

	float rotSpeed = 32.0f;

	float walkSpeed = 1.0f;

	clock_t modeDelay;
	clock_t lastConvert;

public:
	enum MODE mode;

	void init(const glm::vec3& pos, const glm::vec2& rot);
	void update(float delta);

	glm::mat4 toViewMatrix();

	glm::mat4 toProjMatrix();



	glm::vec3 getPos();

	void setPos(const glm::vec3& pos);



	glm::vec2 getRot();

	void setRot(const glm::vec2& rot);



	float getFOV();

	void setFOV(float fov);



	float getRotSpeed();

	void setRotSpeed(float rotSpeed);

	void convertMode();

};