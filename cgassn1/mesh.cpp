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

	recursiveNodeProcess(sc->mRootNode);

	struct MyMesh aMesh;
	GLuint buffer;
	std::cout << "scÀÇ mNumMeshes:" << sc->mNumMeshes << std::endl;
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
			std::cout << myMeshes.size() << std::endl;
			std::cout << n<< " "<< ai_nodes[i]->mNumMeshes<< " " <<ai_nodes[i]->mMeshes[n] << std::endl;
			glBindTexture(GL_TEXTURE_2D, myMeshes[ai_nodes[i]->mMeshes[n]].texIndex);
			// bind VAO
			glBindVertexArray(myMeshes[ai_nodes[i]->mMeshes[n]].vao);
			// draw
			glDrawElements(GL_TRIANGLES, myMeshes[ai_nodes[i]->mMeshes[n]].numFaces * 3, GL_UNSIGNED_INT, 0);

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