#include "map.h"
#include "enemy.h"
#include "player.h"
#include "gun.h"
#include "wall.h"
#include "sys.h"
#include "util.h"
#include "texture.h"



using namespace std;


//Mesh * M_player;
//Mesh * M_gun;
//Mesh * M_enemy;
//Mesh * M_wall;


Map::Map()
{

	glClearColor(1.0, 1.0, 1.0, 0.0);
// default shader

	shaderUtil.Load("cgassn1/shaders/vs.glsl", "cgassn1/shaders/fs.glsl");
	shaderUtil.bind();
	projID = glGetUniformLocation(shaderUtil.getProgram(), "projMatrix");
	viewID = glGetUniformLocation(shaderUtil.getProgram(), "viewMatrix");
	modelID = glGetUniformLocation(shaderUtil.getProgram(), "modelMatrix");
	light_ID = glGetUniformLocation(shaderUtil.getProgram(), "light.position");
	ani = glGetUniformLocation(shaderUtil.getProgram(), "ani");


	viewPosID = glGetUniformLocation(shaderUtil.getProgram(), "viewPos");
	glUniformBlockBinding(shaderUtil.getProgram(), glGetUniformBlockIndex(shaderUtil.getProgram(), "Material"), materialUniLoc);
	texUnit = glGetUniformLocation(shaderUtil.getProgram(), "texUnit");
	shaderUtil.unbind();

	// wall shader
	shaderWallUtil.Load("cgassn1/shaders/vsWall.glsl", "cgassn1/shaders/fsWall.glsl");
	shaderWallUtil.bind();
	// Get a handle for our "MVP" uniform
	MatrixID = glGetUniformLocation(shaderWallUtil.getProgram(), "MVP");
	ViewMatrixID = glGetUniformLocation(shaderWallUtil.getProgram(), "V");
	ModelMatrixID = glGetUniformLocation(shaderWallUtil.getProgram(), "M");
	ModelView3x3MatrixID = glGetUniformLocation(shaderWallUtil.getProgram(), "MV3x3");

	// Load the texture
	DiffuseTexture = loadDDS("diffuse.DDS");
	NormalTexture = loadBMP_custom("normal.bmp");
	SpecularTexture = loadDDS("specular.DDS");

	// Get a handle for our "myTextureSampler" uniform
	DiffuseTextureID = glGetUniformLocation(shaderWallUtil.getProgram(), "DiffuseTextureSampler");
	NormalTextureID = glGetUniformLocation(shaderWallUtil.getProgram(), "NormalTextureSampler");
	SpecularTextureID = glGetUniformLocation(shaderWallUtil.getProgram(), "SpecularTextureSampler");

	// Read our .obj file

	bool res = loadOBJ("cgassn1/resources/cube.obj", vertices, uvs, normals);

	computeTangentBasis(
		vertices, uvs, normals, // input
		tangents, bitangents    // output
	);


	indexVBO_TBN(
		vertices, uvs, normals, tangents, bitangents,
		indices, indexed_vertices, indexed_uvs, indexed_normals, indexed_tangents, indexed_bitangents
	);

	// Load it into a VBO
	

	glGenBuffers(1, &vertexbufferWall);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbufferWall);
	glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvbufferWall);
	glBindBuffer(GL_ARRAY_BUFFER, uvbufferWall);
	glBufferData(GL_ARRAY_BUFFER, indexed_uvs.size() * sizeof(glm::vec2), &indexed_uvs[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normalbufferWall);
	glBindBuffer(GL_ARRAY_BUFFER, normalbufferWall);
	glBufferData(GL_ARRAY_BUFFER, indexed_normals.size() * sizeof(glm::vec3), &indexed_normals[0], GL_STATIC_DRAW);

	glGenBuffers(1, &tangentbufferWall);
	glBindBuffer(GL_ARRAY_BUFFER, tangentbufferWall);
	glBufferData(GL_ARRAY_BUFFER, indexed_tangents.size() * sizeof(glm::vec3), &indexed_tangents[0], GL_STATIC_DRAW);

	glGenBuffers(1, &bitangentbufferWall);
	glBindBuffer(GL_ARRAY_BUFFER, bitangentbufferWall);
	glBufferData(GL_ARRAY_BUFFER, indexed_bitangents.size() * sizeof(glm::vec3), &indexed_bitangents[0], GL_STATIC_DRAW);

	// Generate a buffer for the indices as well
	glGenBuffers(1, &elementbufferWall);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbufferWall);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);

	
	LightID = glGetUniformLocation(shaderWallUtil.getProgram(), "LightPosition_worldspace");

	glm::vec3 lightPos = glm::vec3(0, 300, 0);
	glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

	// Bind our diffuse texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, DiffuseTexture);
	// Set our "DiffuseTextureSampler" sampler to use Texture Unit 0
	glUniform1i(DiffuseTextureID, 0);

	// Bind our normal texture in Texture Unit 1
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, NormalTexture);
	// Set our "NormalTextureSampler" sampler to use Texture Unit 1
	glUniform1i(NormalTextureID, 1);

	// Bind our specular texture in Texture Unit 2
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, SpecularTexture);
	// Set our "SpecularTextureSampler" sampler to use Texture Unit 2
	glUniform1i(SpecularTextureID, 2);


	//test
	// Bind our diffuse texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, DiffuseTexture);
	// Set our "DiffuseTextureSampler" sampler to use Texture Unit 0
	glUniform1i(DiffuseTextureID, 0);

	// Bind our normal texture in Texture Unit 1
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, NormalTexture);
	// Set our "NormalTextureSampler" sampler to use Texture Unit 1
	glUniform1i(NormalTextureID, 1);

	// Bind our specular texture in Texture Unit 2
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, SpecularTexture);
	// Set our "SpecularTextureSampler" sampler to use Texture Unit 2
	glUniform1i(SpecularTextureID, 2);


	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbufferWall);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbufferWall);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// 3rd attribute buffer : normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalbufferWall);
	glVertexAttribPointer(
		2,                                // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// 4th attribute buffer : tangents
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, tangentbufferWall);
	glVertexAttribPointer(
		3,                                // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// 5th attribute buffer : bitangents
	glEnableVertexAttribArray(4);
	glBindBuffer(GL_ARRAY_BUFFER, bitangentbufferWall);
	glVertexAttribPointer(
		4,                                // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbufferWall);
	shaderWallUtil.unbind();

	M_enemy->init("cgassn1/resources/dummy_obj.obj");
	M_player->init("cgassn1/resources/dummy_obj.obj", false,true);
	M_gun->init("cgassn1/resources/M1911.obj", true);
	M_wall->init("cgassn1/resources/cube.obj", true);

	player = new Player();
	gun = new Gun();

	//listEnemy.push_back(new Enemy());
	//listWall.push_back(new Wall());
	gridLength = 50;//(M_wall->getScaleFactor());
	gridSize = 32;
	//printf("%f\n", gridLength);
}

void
Map::init(void)
{
	camera.init(glm::vec3(0, 45, 100), glm::vec2(0.0f, 0.0f));
	//enemy.init(glm::vec3(0, 0, 50), glm::vec2(0.0f, 0.0f));

	player->init(glm::vec3(0, 0, 100), glm::vec2(0.0f, 0.0f));
	gun->init(glm::vec3(0, 0, 80), glm::vec2(0.0f, 0.0f));
	// need to be iterative
	//wall.init(glm::vec3(-30, 0, 0), glm::vec2(0.0f, 0.0f));
	//listEnemy.front()->init(glm::vec3(0, 0, 50), glm::vec2(0.0f, 0.0f));
	//listWall.front()->init(glm::vec3(25, 0, 25), glm::vec2(0.0f, 0.0f));


	for (int x = -1; x < gridSize; x++)
	{
		listWall.push_back(new Wall(x * gridLength + 25, -25));
		listWall.push_back(new Wall(x * gridLength + 25, 32 * gridLength + 25));
	}

	for (int y = -1; y < gridSize; y++)
	{
		listWall.push_back(new Wall(-25, y * gridLength + 25));
		listWall.push_back(new Wall(32 * gridLength + 25, y * gridLength + 25));
	}
	listWall.push_back(new Wall(32 * gridLength + 25, 32 * gridLength + 25));
	for (int x = 0; x < 32; x++)
		for (int y = 0; y < 32; y++)
		{
			objMap[x][y] = EMPTY;
		}

	for (int x = 0; x < 32; x++)
	{
		objMap[x][0] = SAFE;
		objMap[0][x] = SAFE;
	}

	for (int x = 0; x < 5; x++)
		for (int y = 0; y < 5; y++)
		{
			objMap[x][y] = SAFE;
		}



	objMap[5][3] = WALL;
	objMap[6][3] = WALL;
	objMap[10][3] = WALL;
	objMap[11][3] = WALL;
	objMap[12][3] = WALL;
	objMap[14][3] = WALL;
	objMap[15][3] = WALL;
	objMap[16][3] = WALL;
	objMap[17][3] = WALL;
	objMap[19][3] = WALL;
	objMap[20][3] = WALL;
	objMap[21][3] = WALL;
	objMap[4][4] = WALL;
	objMap[7][4] = WALL;
	objMap[9][4] = WALL;
	objMap[14][4] = WALL;
	objMap[19][4] = WALL;
	objMap[22][4] = WALL;
	objMap[4][5] = WALL;
	objMap[10][5] = WALL;
	objMap[11][5] = WALL;
	objMap[14][5] = WALL;
	objMap[15][5] = WALL;
	objMap[16][5] = WALL;
	objMap[19][5] = WALL;
	objMap[22][5] = WALL;
	objMap[4][6] = WALL;
	objMap[7][6] = WALL;
	objMap[12][6] = WALL;
	objMap[14][6] = WALL;
	objMap[19][6] = WALL;
	objMap[22][6] = WALL;
	objMap[5][7] = WALL;
	objMap[6][7] = WALL;
	objMap[9][7] = WALL;
	objMap[10][7] = WALL;
	objMap[11][7] = WALL;
	objMap[14][7] = WALL;
	objMap[15][7] = WALL;
	objMap[16][7] = WALL;
	objMap[17][7] = WALL;
	objMap[19][7] = WALL;
	objMap[20][7] = WALL;
	objMap[21][7] = WALL;
	objMap[6][9] = WALL;
	objMap[9][9] = WALL;
	objMap[10][9] = WALL;
	objMap[11][9] = WALL;
	objMap[12][9] = WALL;
	objMap[15][9] = WALL;
	objMap[5][10] = WALL;
	objMap[6][10] = WALL;
	objMap[9][10] = WALL;
	objMap[14][10] = WALL;
	objMap[15][10] = WALL;
	objMap[4][11] = WALL;
	objMap[6][11] = WALL;
	objMap[9][11] = WALL;
	objMap[10][11] = WALL;
	objMap[11][11] = WALL;
	objMap[15][11] = WALL;
	objMap[4][12] = WALL;
	objMap[5][12] = WALL;
	objMap[6][12] = WALL;
	objMap[7][12] = WALL;
	objMap[12][12] = WALL;
	objMap[15][12] = WALL;
	objMap[6][13] = WALL;
	objMap[9][13] = WALL;
	objMap[10][13] = WALL;
	objMap[11][13] = WALL;
	objMap[14][13] = WALL;
	objMap[15][13] = WALL;
	objMap[16][13] = WALL;
	objMap[5][15] = WALL;
	objMap[6][15] = WALL;
	objMap[10][15] = WALL;
	objMap[11][15] = WALL;
	objMap[12][15] = WALL;
	objMap[15][15] = WALL;
	objMap[16][15] = WALL;
	objMap[17][15] = WALL;
	objMap[19][15] = WALL;
	objMap[22][15] = WALL;
	objMap[25][15] = WALL;
	objMap[4][16] = WALL;
	objMap[7][16] = WALL;
	objMap[9][16] = WALL;
	objMap[14][16] = WALL;
	objMap[19][16] = WALL;
	objMap[20][16] = WALL;
	objMap[22][16] = WALL;
	objMap[24][16] = WALL;
	objMap[25][16] = WALL;
	objMap[4][17] = WALL;
	objMap[5][17] = WALL;
	objMap[6][17] = WALL;
	objMap[7][17] = WALL;
	objMap[10][17] = WALL;
	objMap[11][17] = WALL;
	objMap[15][17] = WALL;
	objMap[16][17] = WALL;
	objMap[19][17] = WALL;
	objMap[21][17] = WALL;
	objMap[22][17] = WALL;
	objMap[25][17] = WALL;
	objMap[4][18] = WALL;
	objMap[7][18] = WALL;
	objMap[12][18] = WALL;
	objMap[17][18] = WALL;
	objMap[19][18] = WALL;
	objMap[22][18] = WALL;
	objMap[25][18] = WALL;
	objMap[4][19] = WALL;
	objMap[7][19] = WALL;
	objMap[9][19] = WALL;
	objMap[10][19] = WALL;
	objMap[11][19] = WALL;
	objMap[14][19] = WALL;
	objMap[15][19] = WALL;
	objMap[16][19] = WALL;
	objMap[19][19] = WALL;
	objMap[22][19] = WALL;
	objMap[24][19] = WALL;
	objMap[25][19] = WALL;
	objMap[26][19] = WALL;
	objMap[4][21] = WALL;
	objMap[5][21] = WALL;
	objMap[6][21] = WALL;
	objMap[7][21] = WALL;
	objMap[8][21] = WALL;
	objMap[10][21] = WALL;
	objMap[11][21] = WALL;
	objMap[12][21] = WALL;
	objMap[13][21] = WALL;
	objMap[16][21] = WALL;
	objMap[17][21] = WALL;
	objMap[20][21] = WALL;
	objMap[24][21] = WALL;
	objMap[6][22] = WALL;
	objMap[10][22] = WALL;
	objMap[15][22] = WALL;
	objMap[18][22] = WALL;
	objMap[20][22] = WALL;
	objMap[21][22] = WALL;
	objMap[23][22] = WALL;
	objMap[24][22] = WALL;
	objMap[6][23] = WALL;
	objMap[10][23] = WALL;
	objMap[11][23] = WALL;
	objMap[12][23] = WALL;
	objMap[15][23] = WALL;
	objMap[16][23] = WALL;
	objMap[17][23] = WALL;
	objMap[18][23] = WALL;
	objMap[20][23] = WALL;
	objMap[22][23] = WALL;
	objMap[24][23] = WALL;
	objMap[6][24] = WALL;
	objMap[10][24] = WALL;
	objMap[15][24] = WALL;
	objMap[18][24] = WALL;
	objMap[20][24] = WALL;
	objMap[24][24] = WALL;
	objMap[6][25] = WALL;
	objMap[10][25] = WALL;
	objMap[11][25] = WALL;
	objMap[12][25] = WALL;
	objMap[13][25] = WALL;
	objMap[15][25] = WALL;
	objMap[18][25] = WALL;
	objMap[20][25] = WALL;
	objMap[24][25] = WALL;
	objMap[4][27] = WALL;
	objMap[5][27] = WALL;
	objMap[6][27] = WALL;
	objMap[7][27] = WALL;
	objMap[9][27] = WALL;
	objMap[12][27] = WALL;
	objMap[14][27] = WALL;
	objMap[15][27] = WALL;
	objMap[16][27] = WALL;
	objMap[18][27] = WALL;
	objMap[19][27] = WALL;
	objMap[20][27] = WALL;
	objMap[21][27] = WALL;
	objMap[22][27] = WALL;
	objMap[25][27] = WALL;
	objMap[26][27] = WALL;
	objMap[4][28] = WALL;
	objMap[9][28] = WALL;
	objMap[12][28] = WALL;
	objMap[15][28] = WALL;
	objMap[20][28] = WALL;
	objMap[24][28] = WALL;
	objMap[27][28] = WALL;
	objMap[4][29] = WALL;
	objMap[5][29] = WALL;
	objMap[6][29] = WALL;
	objMap[10][29] = WALL;
	objMap[11][29] = WALL;
	objMap[15][29] = WALL;
	objMap[20][29] = WALL;
	objMap[25][29] = WALL;
	objMap[26][29] = WALL;
	objMap[4][30] = WALL;
	objMap[9][30] = WALL;
	objMap[12][30] = WALL;
	objMap[15][30] = WALL;
	objMap[20][30] = WALL;
	objMap[24][30] = WALL;
	objMap[27][30] = WALL;
	objMap[4][31] = WALL;
	objMap[5][31] = WALL;
	objMap[6][31] = WALL;
	objMap[7][31] = WALL;
	objMap[9][31] = WALL;
	objMap[12][31] = WALL;
	objMap[14][31] = WALL;
	objMap[15][31] = WALL;
	objMap[16][31] = WALL;
	objMap[20][31] = WALL;
	objMap[25][31] = WALL;
	objMap[26][31] = WALL;
	
int enemyNum = 0;
	while ( enemyNum< 35)
	{
		int x, y;
		x = rand() % 32;
		y = rand() % 32;

		if (objMap[x][y] == EMPTY)
		{
			objMap[x][y] = ENEMY;
			enemyNum++;
		}
	}

	for (int x = 0; x < 32; x++)
		for (int y = 0; y < 32; y++)
		{
			switch (objMap[x][y])
			{
			case WALL:
				listWall.push_back(new Wall(x * gridLength + 25, y * gridLength + 25));
				break;
			case ENEMY:
				listEnemy.push_back(new Enemy(x * gridLength + 25, y * gridLength + 25,
					(enum Direction)(rand() % 4)));
				break;
	/*		case ITEM:
				listItem.push_back(new Item(x * gridLength - width, height - y * gridLength,
					(enum ItemType)(rand() % 2)));
				break;*/

			default:
				break;
			}
		}

	remainingTime = CLOCKS_PER_SEC * 500;
	startTime = clock();
}

void
Map::display(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	shaderUtil.bind();
	shaderUtil.Use();



	glm::mat4 Projection = camera.toProjMatrix();
	glm::mat4 View = camera.toViewMatrix();
	glm::mat4 World = glm::mat4(1.0f);
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 mw = World * Model;

	glUniformMatrix4fv(projID, 1, GL_FALSE, &Projection[0][0]);
	glUniformMatrix4fv(viewID, 1, GL_FALSE, &View[0][0]);
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &mw[0][0]);

	glUniformMatrix4fv(ani, 1, GL_FALSE, &glm::mat4(1.0f)[0][0]);


	glUniform4fv(viewPosID, 1, &camera.getPos()[0]);
	glUniform4fv(light_ID, 1, &camera.getPos()[0]);

	std::cout << camera.getPos()[0] << " "<<camera.getPos()[1] << " "<< camera.getPos()[2] << std::endl;


	//wall.display(M_wall, camera);
	//enemy.display(M_enemy, camera);


	frame = (frame + 1) % 2;




	if (!(player->status == KILLED || gameClear))
	{
		//wall.display(M_wall, camera);
		//enemy.display(M_enemy, camera);
		player->display(M_player, camera, frame);
		gun->display(M_gun, camera, frame);


		for (std::list<Enemy*>::iterator it = listEnemy.begin(); it != listEnemy.end(); it++)
			(*it)->display(M_enemy, camera, frame);
		//for (std::list<Wall*>::iterator it = listWall.begin(); it != listWall.end(); it++)
		//	(*it)->display(M_wall, camera, frame);


		for (std::list<Bullet*>::iterator it = listBullet.begin(); it != listBullet.end(); it++)
			(*it)->display(M_wall, camera, frame);
	}
	else
	{
		player->display(M_player, camera, frame);
		gun->display(M_gun, camera, frame);
	}
	
	//shaderUtil.Delete();
	shaderUtil.unbind();


	shaderWallUtil.bind();
	shaderWallUtil.Use();



	if (!(player->status == KILLED || gameClear))
	{
		glm::vec3 lightPos = glm::vec3(player->getPos().x, player->getPos().y, player->getPos().z);
		glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);
		//wall.display(M_wall, camera);
		//enemy.display(M_enemy, camera);

		for (std::list<Wall*>::iterator it = listWall.begin(); it != listWall.end(); it++)

			(*it)->display(M_wall, camera, frame);

	}
	//shaderWallUtil.Delete();
	shaderWallUtil.unbind();
	//Wall
	//shaderWallUtil.Use();
	//Wall



}

void
Map::reshape(int w, int h)
{

}
void
Map::moveObjects()
{

	checkWall();
	player->update();
	

	glm::vec3 tmp = player->getPos();
	
	gun->setPos(tmp);

	glm::vec2 rot = player->getDir();
	float yrad = glm::radians(rot.y);
	
	gun->setDir(rot);
	gun->update();
	if (camera.mode == FPS)
	{
		tmp.y += 45.0f;
		camera.setPos(glm::vec3(tmp.x + 5.f * glm::sin(yrad),tmp.y,tmp.z- 5.0f*glm::cos(yrad)));
		camera.setRot(rot);
	}
	else if (camera.mode == TPS)
	{
		tmp.y += 120.f;
		tmp.x -= 80.f * glm::sin(yrad);
		tmp.z += 80.f * glm::cos(yrad);
		camera.setPos(tmp);
		rot.x += 30.f;
		camera.setRot(rot);
	}



	camera.update(1.0);
	
	// check bullet routine
	for (std::list<Bullet*>::iterator it = listBullet.begin(); it != listBullet.end(); it++)
	{
		if ((*it)->status == ALIVE)
		{
			(*it)->update();
			printf("%f\n", glm::distance((*it)->getPos(), listEnemy.front()->getPos()));
		}
	}

	std::list<Bullet*>::iterator it = listBullet.begin();

	while (it != listBullet.end())
	{

		if ((*it)->status == KILLED)
		{
			Bullet * tmp = NULL;
			tmp = *it;
			it = listBullet.erase(it);

			delete tmp;
		}
		else it++;
	}


	if (mouseBuffer[GLUT_LEFT_BUTTON] && gun->canShoot())
	{
		listBullet.push_back(new Bullet (player->getPos(), player->getDir(), player->viewDir));
		gun->bang();
	}

	moveEnemy();
	checkWallBullet();
	checkWallEnemy();
	checkEnemyKill();
	checkPlayerKill();

	if (player->status == KILLED || gameClear)
	{

			if (keyboardBuffer['q'])
			{

				glutDestroyWindow(windowId);
				exit(0);
			}

			if (keyboardBuffer['r'])
			{

				gameReset();
			
			}

	}

}

void Map::checkWall()
{
	int fx, fy, bx, by;
	glm::vec3 tmp = player->getPos();
	fx = pos2idx(tmp.x);
	fy = pos2idx(tmp.z);
	bx = fx;
	by = fy;

	float colDistance = 34.0f;
	float dist = 0;
	switch (player->viewDir)
	{
	case UP:
		fy -= 1;
		by += 1;
		break;
	case DOWN:
		fy += 1;
		by -= 1;
		break;
	case LEFT:
		fx -= 1;
		bx += 1;
		break;
	case RIGHT:
		fx += 1;
		bx -= 1;
		break;
	}

	glm::vec3 tmpDist;
	if (fx == -1 || fx == 32 || fy == -1 || fy == 32 ||objMap[fx][fy] == WALL)
	{
		switch (player->viewDir)
		{
		case UP:
		case DOWN:
			tmpDist = glm::vec3(tmp.x, 0, idx2pos(fy));
			break;
	
		case LEFT:
		case RIGHT:
			tmpDist = glm::vec3(idx2pos(fx), 0, tmp.z);
			break;
		}
	}

	if (colDistance >= glm::distance(tmpDist, tmp))
	{
		player->canGo = false;
	}

	else player->canGo = true;
	
	//printf("%f\n", glm::distance(tmpDist, tmp));
}

void Map::checkWallBullet()
{
	for (std::list<Bullet*>::iterator it = listBullet.begin(); it != listBullet.end(); it++)
	{
		int fx, fy, bx, by;
		glm::vec3 tmp = (*it)->getPos();
		fx = pos2idx(tmp.x);
		fy = pos2idx(tmp.z);
		bx = fx;
		by = fy;

		/*float colDistance = 17.0f;
		float dist = 0;
		switch ((*it)->viewDir)
		{
		case UP:
			fy -= 1;
			by += 1;
			break;
		case DOWN:
			fy += 1;
			by -= 1;
			break;
		case LEFT:
			fx -= 1;
			bx += 1;
			break;
		case RIGHT:
			fx += 1;
			bx -= 1;
			break;
		}

		glm::vec3 tmpDist;
		if (fx == -1 || fx == 32 || fy == -1 || fy == 32 || objMap[fx][fy] == WALL)
		{
			switch ((*it)->viewDir)
			{
			case UP:
			case DOWN:
				tmpDist = glm::vec3(tmp.x, 0, idx2pos(fy));
				break;

			case LEFT:
			case RIGHT:
				tmpDist = glm::vec3(idx2pos(fx), 0, tmp.z);
				break;
			}
		}*/

		//if (colDistance >= glm::distance(tmpDist, tmp))
		if (fx == -1 || fx == 32 || fy == -1 || fy == 32 || objMap[fx][fy] == WALL)
		{
			(*it)->status = KILLED;
		}

		
	}
}

void Map::checkEnemyKill()
{
	float killDistance = 25.f;
	if (listBullet.empty())
	{
		return;
	}
	//puts ("test");
	for (std::list<Bullet*>::iterator it = listBullet.begin(); it != listBullet.end(); it++)
	{

		for (std::list<Enemy*>::iterator itEnemy = listEnemy.begin(); itEnemy != listEnemy.end(); itEnemy++)
		{
			
			

			if (killDistance > glm::distance ((*it)->getPos(), (*itEnemy)->getPos()))
			{
				(*itEnemy)->status = KILLED;
				(*it)->status = KILLED;
			}
		}
	}

	std::list<Enemy*>::iterator itEnemy = listEnemy.begin();

	while (itEnemy != listEnemy.end())
	{
		if ((*itEnemy)->status == KILLED)
		{
			Enemy *tmp = NULL;
			tmp = *itEnemy;

			itEnemy = listEnemy.erase(itEnemy);

			delete tmp;
		}
		else itEnemy++;
	}

	if (listEnemy.empty())
	{
		gameClear = true;
	}
}

void Map::checkPlayerKill()
{
	std::list<Enemy*>::iterator it = listEnemy.begin();

	while (it != listEnemy.end())
	{
		if (glm::distance(player->getPos(), (*it)->getPos()) < 10.f)
		{
			player->status = KILLED;
		}
		it++;
	}
}

void Map::checkWallEnemy()
{
	for (std::list<Enemy*>::iterator it = listEnemy.begin(); it != listEnemy.end(); it++)
	{
		int fx, fy, bx, by;
		glm::vec3 tmp = (*it)->getPos();
		fx = pos2idx(tmp.x);
		fy = pos2idx(tmp.z);
		bx = fx;
		by = fy;

		float colDistance = 34.0f;
		float dist = 0;
		switch ((*it)->viewDir)
		{
		case UP:
			fy -= 1;
			by += 1;
			break;
		case DOWN:
			fy += 1;
			by -= 1;
			break;
		case LEFT:
			fx -= 1;
			bx += 1;
			break;
		case RIGHT:
			fx += 1;
			bx -= 1;
			break;
		}

		glm::vec3 tmpDist;
		if (fx == -1 || fx == 32 || fy == -1 || fy == 32 || objMap[fx][fy] == WALL)
		{
			switch ((*it)->viewDir)
			{
			case UP:
			case DOWN:
				tmpDist = glm::vec3(tmp.x, 0, idx2pos(fy));
				break;

			case LEFT:
			case RIGHT:
				tmpDist = glm::vec3(idx2pos(fx), 0, tmp.z);
				break;
			}
		}

		if (colDistance >= glm::distance(tmpDist, tmp))
		{
			(*it)->canGo = false;
		}

		else (*it)->canGo = true;
	}

}


void Map::moveEnemy()
{
	for (std::list<Enemy*>::iterator it = listEnemy.begin(); it != listEnemy.end(); it++)
		(*it)->update(player->getPos());
}

void Map::gameReset()
{
	std::list<Enemy*>::iterator itEnemy = listEnemy.begin();

	while (itEnemy != listEnemy.end())
	{
			Enemy *tmp = NULL;
			tmp = *itEnemy;
			itEnemy = listEnemy.erase(itEnemy);
			delete tmp;
	}

	std::list<Bullet*>::iterator itBullet = listBullet.begin();

	while (itBullet != listBullet.end())
	{
		Bullet *tmp = NULL;
		tmp = *itBullet;
		itBullet = listBullet.erase(itBullet);
		delete tmp;
	}

	std::list<Wall*>::iterator itWall = listWall.begin();

	while (itWall != listWall.end())
	{
		Wall *tmp = NULL;
		tmp = *itWall;
		itWall = listWall.erase(itWall);
		delete tmp;
	}

	init();
}




void Map::checkTimeout()
{
	if (clock() > startTime + remainingTime)
		player->status = KILLED;
}

void Map::displayTime(void) {
	glColor3f(0.f, 0.f, 0.f);
	char buf[100] = { 0 };
	std::string str = "Remain Time : " + std::to_string((int)((remainingTime - clock()) / 1000));
	std::cout << remainingTime - clock() << std::endl;
	sprintf_s(buf, str.c_str());
	renderbitmap(50, 0,50, GLUT_BITMAP_TIMES_ROMAN_24, buf);
}
