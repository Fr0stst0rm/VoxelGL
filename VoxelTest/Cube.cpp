#include "Cube.h"

Cube::Cube()
{
}

Cube::Cube(float size)
{
	this->size = size;
}

Cube::~Cube()
{
}

void Cube::createMesh() {
	drawCube();
}


void Cube::drawCube()
{
	glBegin(GL_QUADS);

	if (front) {
		// front face
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
	}
	
	if (back) {
		// back face
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
	}

	if (top) {
		// top face
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
	}

	if (bottom) {
		// bottom face
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
	}

	if (left) {
		// left face
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
	}

	if (right) {
		// right face
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
	}

	glEnd();
}