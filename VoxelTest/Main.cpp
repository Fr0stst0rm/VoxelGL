
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "Defines.h"

#include "Cube.h"
#include "Level1.h"

void exitMain();
void hideConsole();

using namespace std;

int window;

int const win_width = 1280;
int const win_height = 720;

shared_ptr<Cube> test_cube;

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
		break;
	case 's':
		break;
	case 'a':
		break;
	case 'd':
		break;
	}
}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//Draw objects here
	//test_cube->draw();

	glTranslatef(0, -2, -8);

	glBegin(GL_QUADS);

	// front 
	glColor3f(0, 1, 0);
	glVertex3f(-1, 0, 1);
	glVertex3f(-1, 2, 1);
	glVertex3f(1, 2, 1);
	glVertex3f(1, 0, 1);

	// back
	glColor3f(0.0f, 0.8f, 0.0f);
	glVertex3f(-1, 0, -1);
	glVertex3f(1, 0, -1);
	glVertex3f(1, 2, -1);
	glVertex3f(-1, 2, -1);

	// left 
	glColor3f(0.0f, 0.6f, 0.0f);
	glVertex3f(-1, 0, 1);
	glVertex3f(-1, 2, 1);
	glVertex3f(-1, 2, -1);
	glVertex3f(-1, 0, -1);

	// right
	glVertex3f(1, 0, 1);
	glVertex3f(1, 0, -1);
	glVertex3f(1, 2, -1);
	glVertex3f(1, 2, 1);
	glEnd();

	glutSwapBuffers();
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

	test_cube = make_shared<Cube>();
}

void timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(15, timer, 1);
}

int main(int argc, char **argv)
{
	//hideConsole();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(0, 0);
	window = glutCreateWindow("VoxelTest");

	glutDisplayFunc(&display);
	glutReshapeFunc(&resize);
	glutKeyboardFunc(&keyPressed);
	glutSpecialFunc(&specialKeyPressed);

	init(win_height, win_width);
	glutTimerFunc(15, timer, 1);
	//glutFullScreen();
	glutMainLoop();
	exitMain();
	return 0;
}

void hideConsole()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
}

void exitMain() {
		//Free memory
		exit(0);
}