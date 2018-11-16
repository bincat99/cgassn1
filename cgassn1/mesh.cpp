#include "sys.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


Mesh::Mesh() {

}

void Mesh::init(std::string path, bool isStatic)
{
	Assimp::Importer importer;
	const aiScene* sc = importer.ReadFile(path.c_str(),
			aiProcess_Triangulate 
		|	aiProcess_FlipUVs 
		|	aiProcess_GenSmoothNormals 
		|	aiProcess_CalcTangentSpace 
		//|	aiProcess_JoinIdenticalVertices
	);

	if (!sc || sc->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !sc->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}
	aiVector3D scene_min, scene_max, scene_center;
	get_bounding_box(sc, &scene_min, &scene_max);
	float tmp;
	tmp = scene_max.x - scene_min.x;
	tmp = scene_max.y - scene_min.y > tmp ? scene_max.y - scene_min.y : tmp;
	tmp = scene_max.z - scene_min.z > tmp ? scene_max.z - scene_min.z : tmp;
	scaleFactor = 50.f / tmp;

	recursiveNodeProcess(sc->mRootNode);

	struct MyMesh aMesh;
	GLuint buffer;
	// For each mesh
	for (unsigned int n = 0; n < sc->mNumMeshes; ++n)
	{
		const aiMesh* mesh = sc->mMeshes[n];

		// create array with faces
		// have to convert from Assimp format to array
		unsigned int *faceArray;
		faceArray = (unsigned int *)malloc(sizeof(unsigned int) * mesh->mNumFaces * 3);
		unsigned int faceIndex = 0;

		for (unsigned int t = 0; t < mesh->mNumFaces; ++t) {
			const aiFace* face = &mesh->mFaces[t];

			memcpy(&faceArray[faceIndex], face->mIndices, 3 * sizeof(unsigned int));
			faceIndex += 3;
		}
		aMesh.numFaces = sc->mMeshes[n]->mNumFaces;

		// generate Vertex Array for mesh
		glGenVertexArrays(1, &(aMesh.vao));
		glBindVertexArray(aMesh.vao);

		// buffer for faces
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh->mNumFaces * 3, faceArray, GL_STATIC_DRAW);

		// buffer for vertex positions
		if (mesh->HasPositions()) {
			glGenBuffers(1, &buffer);
			glBindBuffer(GL_ARRAY_BUFFER, buffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * mesh->mNumVertices, mesh->mVertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);
		}

		// unbind buffers
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		myMeshes.push_back(aMesh);
	}

}

void Mesh::render()
{
	for (unsigned int i = 0; i < ai_nodes.size(); i++) {
		// draw all meshes assigned to this node
		for (unsigned int n = 0; n < ai_nodes[i]->mNumMeshes; ++n) {
			// bind texture
			glBindTexture(GL_TEXTURE_2D, myMeshes[ai_nodes[i]->mMeshes[n]].texIndex);
			// bind VAO
			glBindVertexArray(myMeshes[ai_nodes[i]->mMeshes[n]].vao);
			// draw
			glDrawElements(GL_LINE_STRIP, myMeshes[ai_nodes[i]->mMeshes[n]].numFaces * 3, GL_UNSIGNED_INT, 0);

		}
		
	}
}


void Mesh::recursiveNodeProcess(aiNode * node)
{
	aiNode * nnode = (aiNode*)malloc(sizeof(aiNode));
	memcpy(nnode, node, sizeof(aiNode));
	nnode->mMeshes = (unsigned*)malloc(sizeof(unsigned)*node->mNumMeshes);
	memcpy(nnode->mMeshes, node->mMeshes, sizeof(unsigned)*node->mNumMeshes);
	ai_nodes.push_back(nnode);

	for (int i = 0; i < node->mNumChildren; i++)
	{
		recursiveNodeProcess(node->mChildren[i]);
	}
}


#define aisgl_min(x,y) (x<y?x:y)
#define aisgl_max(x,y) (y>x?y:x)

void Mesh::get_bounding_box_for_node(const aiScene* scene, const aiNode* nd,
	aiVector3D* min,
	aiVector3D* max)

{
	aiMatrix4x4 prev;
	unsigned int n = 0, t;

	for (; n < nd->mNumMeshes; ++n) {
		const aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];
		for (t = 0; t < mesh->mNumVertices; ++t) {

			aiVector3D tmp = mesh->mVertices[t];

			min->x = aisgl_min(min->x, tmp.x);
			min->y = aisgl_min(min->y, tmp.y);
			min->z = aisgl_min(min->z, tmp.z);

			max->x = aisgl_max(max->x, tmp.x);
			max->y = aisgl_max(max->y, tmp.y);
			max->z = aisgl_max(max->z, tmp.z);
		}
	}

	for (n = 0; n < nd->mNumChildren; ++n) {
		get_bounding_box_for_node(scene, nd->mChildren[n], min, max);
	}
}


void Mesh::get_bounding_box(const aiScene* scene, aiVector3D* min, aiVector3D* max)
{

	min->x = min->y = min->z = 1e10f;
	max->x = max->y = max->z = -1e10f;
	get_bounding_box_for_node(scene, scene->mRootNode, min, max);
}

float Mesh::getScaleFactor(void) {
	return scaleFactor;
}