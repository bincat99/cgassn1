#include "map.h"
#include "enemy.h"
#include "player.h"
#include "gun.h"
#include "wall.h"
#include "sys.h"
#include "util.h"




using namespace std;


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
	MatrixID2 = glGetUniformLocation(shaderUtil.getProgram(), "ani");

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
	shaderUtil.Use();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 Projection = camera.toProjMatrix();
	glm::mat4 View = camera.toViewMatrix();
	glm::mat4 World = glm::mat4(1.0f);
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 mvp = Projection * View * World * Model;

	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
	glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &glm::mat4(1.0f)[0][0]);


	displayTime();
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




	if (!(player->status == KILLED || gameClear))
	{
		//wall.display(M_wall, camera);
		//enemy.display(M_enemy, camera);
		player->display(M_player, camera);
		gun->display(M_gun, camera);


		for (std::list<Wall*>::iterator it = listWall.begin(); it != listWall.end(); it++)
			(*it)->display(M_wall, camera);

		for (std::list<Enemy*>::iterator it = listEnemy.begin(); it != listEnemy.end(); it++)
			(*it)->display(M_enemy, camera);

		for (std::list<Bullet*>::iterator it = listBullet.begin(); it != listBullet.end(); it++)
			(*it)->display(M_wall, camera);
	}
	shaderUtil.Delete();
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
