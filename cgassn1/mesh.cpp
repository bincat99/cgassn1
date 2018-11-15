#include "sys.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


void Mesh::init(std::string path, bool isStatic)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path.c_str(),
			aiProcess_Triangulate 
		|	aiProcess_FlipUVs 
		|	aiProcess_GenSmoothNormals 
		|	aiProcess_CalcTangentSpace 
		//|	aiProcess_JoinIdenticalVertices
	);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}

	aiNode* root = scene->mRootNode;

	uint32_t numMesh = root->mNumMeshes;
	uint32_t numChild = root->mNumChildren;

	const aiNode* child = root->mChildren[root->mNumChildren - 1];
	//recursiveNodeProcess(root);
	
	
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normals;
	std::vector<uint32_t> indexes;

	
	for (int i = 0; i < scene->mNumMeshes; i++)
	{	
		aiMesh* mesh = scene->mMeshes[i];
		for (int j = 0; j < mesh->mNumVertices; j++)
		{
			glm::vec3 v;
			v.x = mesh->mVertices[j].x;
			v.y = mesh->mVertices[j].y;
			v.z = mesh->mVertices[j].z;

			vertices.push_back(v);

		/*	glm::vec3 vn;
			if (mesh->mNormals != NULL)
			{
				vn.x = mesh->mNormals[j].x;
				vn.y = mesh->mNormals[j].y;
				vn.z = mesh->mNormals[j].z;
				normals.push_back(vn);
			}

			glm::vec2 vt;
			vt.x = mesh->mTextureCoords[0][j].x;
			vt.y = mesh->mTextureCoords[0][j].y;
			texCoords.push_back(vt);*/
		}

		//VertexBuffer* vb = new VertexBuffer();
		//vb->addAll(vertices);
		//vBufs.push_back(vb);
		
		if (mesh->HasFaces()) {
			for (uint32_t j = 0; j < mesh->mNumFaces; j++)
			{
				aiFace face = mesh->mFaces[j];
				for (uint32_t k = 0; k < face.mNumIndices; k++)
				{
					indexes.push_back(face.mIndices[k]);
				}
			}
		}
	}
	
	//aiMesh* mesh = scene->mMeshes[child->mMeshes[child->mNumMeshes - 1]];
	//for (uint32_t i = 0; i < mesh->mNumVertices; i++)
	//{
	//	// Vertices
	//	glm::vec3 v;
	//	v.x = mesh->mVertices[i].x;
	//	v.y = mesh->mVertices[i].z;
	//	v.z = mesh->mVertices[i].y;
	//	vertices.push_back(v);
	//
	//	// Normals
	//	glm::vec3 vn;
	//	if (mesh->mNormals != NULL) {
	//		vn.x = mesh->mNormals[i].x;
	//		vn.y = mesh->mNormals[i].z;
	//		vn.z = mesh->mNormals[i].y;
	//		normals.push_back(vn);
	//	}
	//	// TexCoords
	//	glm::vec2 vt;
	//	vt.x = mesh->mTextureCoords[0][i].x;
	//	vt.y = mesh->mTextureCoords[0][i].y;
	//	texCoords.push_back(vt);
	//}


	////std::vector<uint32_t> indexes;

	//for (uint32_t i = 0; i < mesh->mNumFaces; i++)
	//{
	//	aiFace face = mesh->mFaces[i];
	//	for (uint32_t j = 0; j < face.mNumIndices; j++)
	//	{
	//		indexes.push_back(face.mIndices[j]);
	//	}
	//}
	printf("mesh size: %lld\n", scene->mNumMeshes );
	printf("vertice size: %lld\n", vertices.size());
	// Vertex Buffer
	vBuf.addAll(vertices);
	vBuf.create();
	vBuf.upload();

	// TexCoord Buffer
	tBuf.addAll(texCoords);
	tBuf.create();
	tBuf.upload();

	// Normal Buffer
	nBuf.addAll(normals);
	nBuf.create();
	nBuf.upload();

	// Index Buffer
	iBuf.addAll(indexes);
	iBuf.create();
	iBuf.upload();
}

void Mesh::release()
{
	iBuf.release();
	nBuf.release();
	tBuf.release();
	vBuf.release();
}

VertexBuffer* Mesh::getVertexBuffer()
{
	return &this->vBuf;
}

VertexBuffer* Mesh::getTexCoordBuffer()
{
	return &this->tBuf;
}

VertexBuffer* Mesh::getNormalBuffer()
{
	return &this->nBuf;
}

IndexBuffer* Mesh::getIndexBuffer()
{
	return &this->iBuf;
}

void Mesh::recursiveNodeProcess(aiNode * node)
{
	ai_nodes.push_back(node);

	for (int i = 0; i < node->mNumChildren; i++)
	{
		recursiveNodeProcess(node->mChildren[i]);
	}
}