#include "map.h"
#include "enemy.h"
#include "player.h"
#include "gun.h"
#include "wall.h"
#include "sys.h"


GLuint vertexbuffer;
GLuint uvbuffer;
GLuint MatrixID;
using namespace std;
Camera camera;

//Mesh * M_player;
//Mesh * M_gun;
//Mesh * M_enemy;
//Mesh * M_wall;

Mesh* M_enemy = new Mesh();
Mesh* M_gun = new Mesh();
Mesh* M_player = new Mesh();
Mesh* M_wall = new Mesh();

Map::Map()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	shaderUtil.Load("cgassn1/shaders/vs.shader", "cgassn1/shaders/fs.shader");
	MatrixID = glGetUniformLocation(shaderUtil.getProgram(), "MVP");

	M_enemy->init("cgassn1/resources/Skeleton.obj");
	M_player->init("cgassn1/resources/dummy_obj.obj");
	M_gun->init("cgassn1/resources/M1911.obj");
	M_wall->init("cgassn1/resources/cube.obj");

	player = new Player();
	gun = new Gun();
	enemyVect = new vector<Enemy*>();
	enemyVect->push_back(new Enemy());
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
	enemyVect->front()->init(glm::vec3(0, 0, 50), glm::vec2(0.0f, 0.0f));
}

void
Map::display(void)
{
	shaderUtil.Use();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 Projection = camera.toProjMatrix();
	glm::mat4 View = camera.toViewMatrix();
	glm::mat4 World = glm::mat4(1.0f);
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 mvp = Projection * View * World * Model;

	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

	glBegin(GL_LINES);
	glVertex3f(.0f, .0f, .0f);
	glVertex3f(10000.0f, .0f, .0f);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(.0f, .0f, .0f);
	glVertex3f(0.0f, 100.0f, .0f);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(.0f, .0f, .0f);
	glVertex3f(0.0f, .0f, 50.0f);
	glEnd();

	//wall.display(M_wall, camera);
	//enemy.display(M_enemy, camera);
	player->display(M_player, camera);
	gun->display(M_gun, camera);
	enemyVect->front()->display(M_enemy, camera);
	
	shaderUtil.Delete();
}

void
Map::reshape(int w, int h)
{

}
void
Map::moveObjects()
{
	camera.update(1.0);

	glm::vec3 tmp = camera.getPos();
	tmp.y -= 45.0f;
	player->setPos(tmp);
	tmp.z -= 20.f;
	gun->setPos(tmp);

	glm::vec2 rot = camera.getRot();
	player->setDir(rot);
	gun->setDir(rot);

	//enemy.moveRandom();
	//printf("%f, %f\n", player.getPos().y, enemy.getPos().y);
	//	printf("%f\n", glm::distance(player.getPos(), enemy.getPos()));

	//gun.update();
	//if (mouseBuffer[GLUT_LEFT_BUTTON])
	//{

	//}
}
