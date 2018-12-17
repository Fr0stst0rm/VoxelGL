#include "Cube.h"

Cube::Cube()
{
	//Reset all render sides to true
	memset(&m_renderedSides, 0xff, sizeof(m_renderedSides));
}

Cube::~Cube()
{
}

void Cube::createMesh() {
	drawCube();
}

GLuint Cube::getTexture()
{
	return TextureManager::getTexture(0);
}

bool Cube::isTopRendered() {
	return m_renderedSides.top;
}

bool Cube::isBottomRendered() {
	return m_renderedSides.bottom;
}

bool Cube::isLeftRendered() {
	return m_renderedSides.left;
}

bool Cube::isRightRendered() {
	return m_renderedSides.right;
}

bool Cube::isFrontRendered() {
	return m_renderedSides.front;
}

bool Cube::isBackRendered() {
	return m_renderedSides.back;
}

void Cube::setTopRendered(bool b) {
	m_renderedSides.top = b;
}
void Cube::setBottomRendered(bool b) {
	m_renderedSides.bottom = b;
}

void Cube::setLeftRendered(bool b) {
	m_renderedSides.left = b;
}

void Cube::setRightRendered(bool b) {
	m_renderedSides.right = b;
}

void Cube::setFrontRendered(bool b) {
	m_renderedSides.front = b;
}

void Cube::setBackRendered(bool b) {
	m_renderedSides.back = b;
}

void Cube::drawCube()
{
	glBegin(GL_QUADS);

	if (isFrontRendered()) {
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
	
	if (isBackRendered()) {
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

	if (isTopRendered()) {
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

	if (isBottomRendered()) {
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

	if (isLeftRendered()) {
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

	if (isRightRendered()) {
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