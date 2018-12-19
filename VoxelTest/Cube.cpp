#include "Cube.h"

Cube::Cube()
{
	//Reset all render sides to true
	memset(&m_settings, 0xff, sizeof(m_settings));
	m_settings.glow = false;
	m_settings.transparent = false;
}

Cube::~Cube()
{
}

void Cube::createMesh() {
	createCubeMesh();
}

bool Cube::isTopRendered() {
	return m_settings.top;
}

bool Cube::isBottomRendered() {
	return m_settings.bottom;
}

bool Cube::isLeftRendered() {
	return m_settings.left;
}

bool Cube::isRightRendered() {
	return m_settings.right;
}

bool Cube::isFrontRendered() {
	return m_settings.front;
}

bool Cube::isBackRendered() {
	return m_settings.back;
}

void Cube::setTopRendered(bool b) {
	m_settings.top = b;
}
void Cube::setBottomRendered(bool b) {
	m_settings.bottom = b;
}

void Cube::setLeftRendered(bool b) {
	m_settings.left = b;
}

void Cube::setRightRendered(bool b) {
	m_settings.right = b;
}

void Cube::setFrontRendered(bool b) {
	m_settings.front = b;
}

void Cube::setBackRendered(bool b) {
	m_settings.back = b;
}

void Cube::createCubeMesh()
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

bool Cube::isTransparent()
{
	return m_settings.transparent;
}

bool Cube::isGlowing()
{
	return m_settings.glow;
}
