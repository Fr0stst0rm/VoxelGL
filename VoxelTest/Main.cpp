
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include "Defines.h"

#include "Player.h"

#include "Voxel.h"
#include "LoadedLevel.h"

#include "Level1.h"

#include "LodObject.h"

using namespace std;

int window;

int const win_width = 1920;
int const win_height = 1080;

int xRotationOffset = -1;
int yRotationOffset = -1;

shared_ptr<Player> player;

shared_ptr<LodObject> lodTest;

void display();
void exitMain();
void hideConsole();
void timer(int value);
void init(int width, int height);
void resize(int width, int height);
void specialKeyPressed(int key, int x, int y);
void keyPressed(unsigned char key, int x, int y);
void mouseMoved(int x, int y);
void mouseDragged(int x, int y);
void mouseClicked(int button, int state, int x, int y);
float findSpawnHeight(float x, float z);

int main(int argc, char **argv)
{
	//hideConsole();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
	glutInitWindowSize(win_width, win_height);
	glutInitWindowPosition(0, 0);
	window = glutCreateWindow("VoxelTest");

	glutDisplayFunc(&display);
	glutReshapeFunc(&resize);
	glutKeyboardFunc(&keyPressed);
	glutSpecialFunc(&specialKeyPressed);
	glutMouseFunc(&mouseClicked);
	glutMotionFunc(&mouseDragged);
	glutPassiveMotionFunc(&mouseMoved);

	init(win_width, win_height);
	glutTimerFunc(15, timer, 1);
	glutFullScreen();
	glutMainLoop();
	exitMain();
	return 0;
}

void init(int width, int height)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	resize(width, height);

	cout << "Start loading\n";

	//Create game object here
	player = make_shared<Player>();

	lodTest = make_shared<LodObject>();
	lodTest->m_pos.y = 4;

	//Load Level

	LoadedLevel::loadLevel(Level1::map, Level1::width, Level1::height, Level1::depth);

	//Config spawn

	player->m_pos.y = findSpawnHeight(player->m_pos.x, player->m_pos.z);

	cout << "Finished loading\n";
}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//Rotate Scene
	glRotatef(player->m_rot.y, 0.0f, 1.0f, 0.0f);
	glRotatef(player->m_rot.x, 1.0f, 0.0f, 0.0f);

	//Move player
	glTranslatef(-player->m_pos.x, -player->m_pos.y, -player->m_pos.z);

	//LOD Test
	float distance = (lodTest->m_pos - player->m_pos).length();
	cout << "LodDistance: " << distance << "\n";
	lodTest->draw(distance);

	//Draw level

	Voxel * voxel;

	std::vector<SortingHelper> trasparentSortingVector;

	//Draw opaque objects here
	//Draw farest z layer first
	for (uint32_t z = 0; z < LoadedLevel::m_depth; z++) {
		for (uint32_t y = 0; y < LoadedLevel::m_height; y++) {
			for (uint32_t x = 0; x < LoadedLevel::m_width; x++) {
				voxel = LoadedLevel::getVoxel(x, y, z);

				//cout << "X " << x << " Y " << y << " Z " << z << " -> Index: " << XYZ_TO_ARRAY_INDEX(x, y, z, LoadedLevel::m_width, LoadedLevel::m_depth) << " = " << LoadedLevel::m_map[XYZ_TO_ARRAY_INDEX(x, y, z, LoadedLevel::m_width, LoadedLevel::m_depth)] << "\n";
				//cout << "Size of voxel: " << sizeof(voxel) << "\n";

				if (!voxel->isTransparent()) {
					voxel->draw(static_cast<float>(x) - LoadedLevel::m_centerOffsetX, y, static_cast<float>(z) - LoadedLevel::m_centerOffsetZ);
				}
				else if (voxel->m_type != VoxelType::AIR)
				{
					float order = (Vector3f(x,y,z)-Vector3f(player->m_pos.x + LoadedLevel::m_centerOffsetX, player->m_pos.y, player->m_pos.z + LoadedLevel::m_centerOffsetZ)).length();
					//insert at right pos
					int i = 0;
					for (; i < trasparentSortingVector.size(); i++) {
						if (order < trasparentSortingVector[i].sortingVal) {
							break;
						}
					}
					SortingHelper elem = { Vector3f(x,y,z), order };
					trasparentSortingVector.insert(trasparentSortingVector.begin() + i, elem);
				}
			}
		}
	}

	//cout << "Start transparent\n";

	//Draw transparent objects here
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//Draw farest z layer first
	while (!trasparentSortingVector.empty())
	{
		voxel = LoadedLevel::getVoxel(trasparentSortingVector.back().position);
		voxel->drawTransparent(trasparentSortingVector.back().position.x - LoadedLevel::m_centerOffsetX, trasparentSortingVector.back().position.y, trasparentSortingVector.back().position.z - LoadedLevel::m_centerOffsetZ);
			
		/*
		switch (voxel->m_type) {
		case VoxelType::GLASS_GREEN:
			cout << "Green\n";
			cout << "Order: " << trasparentSortingVector.back().sortingVal << "\n";
			break;
		case VoxelType::GLASS_RED:
			cout << "Red\n";
			cout << "Order: " << trasparentSortingVector.back().sortingVal << "\n";
			break;
		case VoxelType::GLASS_BLUE:
			cout << "Blue\n";
			cout << "Order: " << trasparentSortingVector.back().sortingVal << "\n";
			break;
		}
		*/

		trasparentSortingVector.pop_back();
	}
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);

	glutSwapBuffers();
}

void timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(15, timer, 1);
}

void hideConsole()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
}

void exitMain() {
	//Free memory
	exit(0);
}


void resize(int width, int height)
{
	// prevent division by zero
	if (height == 0) { height = 1; }

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)width / (float)height, 0.1f, 500.0f);
	glMatrixMode(GL_MODELVIEW);
}

void specialKeyPressed(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		break;
	case GLUT_KEY_DOWN:
		break;
	case GLUT_KEY_LEFT:
		break;
	case GLUT_KEY_RIGHT:
		break;
	}
}

void keyPressed(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exitMain();
		break;
	case 'w':
		player->m_pos.z -= player->getLookingDir().z * player->m_walkingSpeed;
		player->m_pos.x += player->getLookingDir().x * player->m_walkingSpeed;
		break;
	case 's':
		player->m_pos.z += player->getLookingDir().z * player->m_walkingSpeed;
		player->m_pos.x -= player->getLookingDir().x * player->m_walkingSpeed;
		break;
	case 'a':
		player->m_pos.z -= player->getLookingDir().x * player->m_walkingSpeed;
		player->m_pos.x -= player->getLookingDir().z * player->m_walkingSpeed;
		break;
	case 'd':
		player->m_pos.z += player->getLookingDir().x * player->m_walkingSpeed;
		player->m_pos.x += player->getLookingDir().z * player->m_walkingSpeed;
		break;
	case 'q':
		player->m_pos.y -= player->m_walkingSpeed;
		break;
	case 'e':
		player->m_pos.y += player->m_walkingSpeed;
		break;
	}
}

void mouseClicked(int button, int state, int x, int y)
{
	cout << "Click: " << button << " " << state << " " << x << " " << y << "\n";
}

void mouseDragged(int x, int y)
{
	mouseMoved(x, y);
	cout << "Drag x: " << x << " y: " << y << "\n";
}

void mouseMoved(int x, int y)
{
	if (xRotationOffset == -1) {
		xRotationOffset = y;
	}

	if (yRotationOffset == -1) {
		yRotationOffset = x;
	}

	//Rotation um y achse mit mouse x value
	player->m_rot.y = static_cast<int>(static_cast<float>(x - yRotationOffset) * player->m_rotationSpeed) % 360;

	//cout << "Move x: " << x << " y: " << y << "\n";
}

float findSpawnHeight(float x, float z) {
	float y = 0;
	for (y = (LoadedLevel::m_height - 1); y >= 0; y--) {
		if (LoadedLevel::getVoxelCentered(x, y, z)->m_type != VoxelType::AIR) {
			break;
		}
	}

	cout << "Player start Y pos: " << (y + 1) << "\n";

	return y + 1;
}