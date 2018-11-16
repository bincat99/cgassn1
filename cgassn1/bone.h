#pragma once
#include "sys.h"

class Skeleton;

class Bone
{
public:
	std::string name;    //The bone's name as loaded by ASSIMP.

	Mesh* mesh;    //The mesh this bone is going to affect.
				   //Only one skeleton per mesh /
	VertexBuffer vBuf;
	IndexBuffer iBuf;

	aiNode* node;    //This bone's corresponding aiNode 
						 //(this is where we'll get its transformation matrix,
						 //as well as its parent and children nodes.

	Bone* parent_bone;    //A pointer to this bone's parent bone.
	glm::mat4 parent_transforms;    //This is a concatenation of all transforms
									//before this bone, from this bone's parent,
									//all the way to the skeleton's root node.
									//This is used when calculating the current
									//keyframe's transformation.

	Bone() { name = ""; id = -2; }

	Bone(Mesh* in_mesh, unsigned int in_id, std::string in_name, aiMatrix4x4 in_o_mat);
	Bone(Mesh* in_mesh, unsigned int in_id, std::string in_name, glm::mat4 in_o_mat);

	glm::mat4 GetParentTransforms();
};