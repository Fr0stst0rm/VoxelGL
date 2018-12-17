
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "Defines.h"

#include "Player.h"

#include "Cube.h"
#include "Level1.h"

using namespace std;

int window;

int const win_width = 1920;
int const win_height = 1080;

shared_ptr<Player> player;

shared_ptr<Cube> test_cube;

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
	//glutFullScreen();
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

	//Create game object here
	player = make_shared<Player>();

	test_cube = make_shared<Cube>();
}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//Move player
	glTranslatef(player->m_pos.x, player->m_pos.y, player->m_pos.z);
	//TODO Rotate

	//Draw objects here
	test_cube->drawTexture(0,0,0);

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
		player->m_pos.z += player->m_walkingSpeed;
		break;
	case 's':
		player->m_pos.z -= player->m_walkingSpeed;
		break;
	case 'a':
		player->m_pos.x += player->m_walkingSpeed;
		break;
	case 'd':
		player->m_pos.x -= player->m_walkingSpeed;
		break;
	}
}

void mouseClicked(int button, int state, int x, int y)
{
	cout << "Click: " << button << " " << state  << " " << x  << " " << y << "\n";
}

void mouseDragged(int x, int y)
{
	cout << "Drag x: " << x << " y: " << y << "\n";
}

void mouseMoved(int x, int y)
{
	cout << "Move x: " << x << " y: " << y << "\n";
}