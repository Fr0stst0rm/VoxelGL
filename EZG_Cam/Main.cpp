
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include "Defines.h"
#include "Input.h"

#include "Player.h"

#include "Voxel.h"
#include "LoadedLevel.h"

#include "Level1.h"

#include "LodObject.h"
#include "Spline.h"

using namespace std;

int window;

int const win_width = 1920;
int const win_height = 1080;

int xRotationOffset = -1;
int yRotationOffset = -1;
int zRotationOffset = -1;

//Setup input flags
KeyPressedFlags keyFlags;

shared_ptr<Player> playerCam;
shared_ptr<Spline> camSpline;

//shared_ptr<LodObject> lodTest;

void display();
void exitMain();
void hideConsole();
void timer(int value);
void init(int width, int height);
void resize(int width, int height);
void checkInput();
void specialKeyPressed(int key, int x, int y);
void keyPressed(unsigned char key, int x, int y);
void specialKeyUp(int key, int x, int y);
void keyUp(unsigned char key, int x, int y);
void mouseMoved(int x, int y);
void mouseDragged(int x, int y);
void mouseClicked(int button, int state, int x, int y);
void setCam(Vector3f pos, Vector3f rot);
float findSpawnHeight(float x, float z);

int main(int argc, char** argv)
{
	//hideConsole();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
	glutInitWindowSize(win_width, win_height);
	glutInitWindowPosition(0, 0);
	window = glutCreateWindow("VoxelTest");

	glutDisplayFunc(&display);
	glutReshapeFunc(&resize);

	// Change to key check in display func
	glutKeyboardFunc(&keyPressed);
	glutKeyboardUpFunc(&keyUp);
	glutSpecialFunc(&specialKeyPressed);
	glutSpecialUpFunc(&specialKeyUp);
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
	playerCam = make_shared<Player>();

	//lodTest = make_shared<LodObject>();
	//lodTest->m_pos.y = 4;

	camSpline = make_shared<Spline>();
	//camSpline->

	//Load Level

	LoadedLevel::loadLevel(Level1::map, Level1::width, Level1::height, Level1::depth);

	//Config spawn

	playerCam->m_pos.y = findSpawnHeight(playerCam->m_pos.x, playerCam->m_pos.z);
	playerCam->m_walkingSpeed = 0.2f;

	cout << "Finished loading\n";
}

void display()
{
	// Input
	checkInput();

	// Graphics
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	setCam(playerCam->m_pos, playerCam->m_rot);

	//LOD Test
	//float distance = (lodTest->m_pos - player->m_pos).length();
	//cout << "LodDistance: " << distance << "\n";
	//lodTest->draw(distance);

	//Draw Spline
	camSpline->setLineWidth(5.0f);
	camSpline->setColor(1, 0, 0, 1);
	camSpline->drawSpline();


	//Draw level


	Voxel* voxel;

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
					float order = (Vector3f(x, y, z) - Vector3f(playerCam->m_pos.x + LoadedLevel::m_centerOffsetX, playerCam->m_pos.y, playerCam->m_pos.z + LoadedLevel::m_centerOffsetZ)).length();
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

void checkInput() {

	if (keyFlags.esc) {
		exitMain();
	}
	if (keyFlags.w || keyFlags.up) {
		playerCam->m_pos.z -= playerCam->getLookingDir().z * playerCam->m_walkingSpeed;
		playerCam->m_pos.x += playerCam->getLookingDir().x * playerCam->m_walkingSpeed;
	}
	if (keyFlags.s || keyFlags.down) {
		playerCam->m_pos.z += playerCam->getLookingDir().z * playerCam->m_walkingSpeed;
		playerCam->m_pos.x -= playerCam->getLookingDir().x * playerCam->m_walkingSpeed;
	}
	if (keyFlags.a || keyFlags.left) {
		playerCam->m_pos.z -= playerCam->getLookingDir().x * playerCam->m_walkingSpeed;
		playerCam->m_pos.x -= playerCam->getLookingDir().z * playerCam->m_walkingSpeed;
	}
	if (keyFlags.d || keyFlags.right) {
		playerCam->m_pos.z += playerCam->getLookingDir().x * playerCam->m_walkingSpeed;
		playerCam->m_pos.x += playerCam->getLookingDir().z * playerCam->m_walkingSpeed;
	}
	if (keyFlags.q) {
		playerCam->m_pos.y -= playerCam->m_walkingSpeed;
	}
	if (keyFlags.e) {
		playerCam->m_pos.y += playerCam->m_walkingSpeed;
	}
	if (keyFlags.c) {
		camSpline->clearSplinePoints();
	}
	if (keyFlags.space) {
		camSpline->addSplinePoint(playerCam->m_pos.x, playerCam->m_pos.y, playerCam->m_pos.z);
	}

}

void specialKeyPressed(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		keyFlags.up = true;
		break;
	case GLUT_KEY_DOWN:
		keyFlags.down = true;
		break;
	case GLUT_KEY_LEFT:
		keyFlags.left = true;
		break;
	case GLUT_KEY_RIGHT:
		keyFlags.right = true;
		break;
	}
}

void keyPressed(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		keyFlags.esc = true;
		break;
	case 'w':
		keyFlags.w = true;
		break;
	case 's':
		keyFlags.s = true;
		break;
	case 'a':
		keyFlags.a = true;
		break;
	case 'd':
		keyFlags.d = true;
		break;
	case 'q':
		keyFlags.q = true;
		break;
	case 'e':
		keyFlags.e = true;
		break;
	case 'c':
		keyFlags.c = true;
		break;
	case ' ':
		keyFlags.space = true;
		break;
	}
}
void specialKeyUp(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_UP:
		keyFlags.up = false;
		break;
	case GLUT_KEY_DOWN:
		keyFlags.down = false;
		break;
	case GLUT_KEY_LEFT:
		keyFlags.left = false;
		break;
	case GLUT_KEY_RIGHT:
		keyFlags.right = false;
		break;
	}
}

void keyUp(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		keyFlags.esc = false;
		break;
	case 'w':
		keyFlags.w = false;
		break;
	case 's':
		keyFlags.s = false;
		break;
	case 'a':
		keyFlags.a = false;
		break;
	case 'd':
		keyFlags.d = false;
		break;
	case 'q':
		keyFlags.q = false;
		break;
	case 'e':
		keyFlags.e = false;
		break;
	case 'c':
		keyFlags.c = false;
		break;
	case ' ':
		keyFlags.space = false;
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

	if (yRotationOffset == -1) {
		yRotationOffset = x;
	}


	if (xRotationOffset == -1) {
		xRotationOffset = y;
	}
	if (zRotationOffset == -1) {
		zRotationOffset = y;
	}


	//Rotation um y achse mit mouse x value

	playerCam->m_rot.y = static_cast<int>(static_cast<float>(x - yRotationOffset) * playerCam->m_rotationSpeed) % 360;
	//cout << "y Rot: " << (player->m_rot.y - 180) << "\n";

	//Rotation um x & z achse mit mouse y value
	//TODO rotation um y achse berücksichtigen
	playerCam->m_rot.x = static_cast<int>(static_cast<float>(y - xRotationOffset) * playerCam->m_rotationSpeed) % 360;
	//player->m_rot.z = static_cast<int>(static_cast<float>(y - zRotationOffset) * player->m_rotationSpeed) % 360;

	//cout << "Move x: " << x << " y: " << y << "\n";
}

void setCam(Vector3f pos, Vector3f rot) {

	//Rotate Scene

	glRotatef(rot.x, 1.0f, 0.0f, 0.0f); //1. Pitch
	glRotatef(rot.y, 0.0f, 1.0f, 0.0f); //2. Yaw

	//Move player
	glTranslatef(-pos.x, -pos.y, -pos.z);
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