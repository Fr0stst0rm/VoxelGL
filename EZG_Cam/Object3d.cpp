#include <GL/glew.h>
#include "Object3d.h"

Object3D::Object3D() : m_shader(nullptr), m_model(glm::mat4(1.0f))
{
}

Object3D::~Object3D()
{
}

void Object3D::setShader(Shader* s)
{
	m_shader = s;
}

void Object3D::drawColor(float x, float y, float z, RGBAL color)
{
	drawColor(x, y, z, 1, color.red, color.green, color.blue, color.alpha);
}

void Object3D::drawColor(float x, float y, float z, float size, RGBAL color)
{
	drawColor(x, y, z, size, color.red, color.green, color.blue, color.alpha);
}

void Object3D::drawColor(float x, float y, float z, float r, float g, float b, float a)
{
	drawColor(x, y, z, 1, r, g, b, a);
}

void Object3D::drawColor(float x, float y, float z, float size, float r, float g, float b, float a)
{
	if (m_shader) {
		m_shader->setVec3("objectColor", r, g, b);
	}
	else {
		glColor4f(r, g, b, a);
	}
	draw(x, y, z, size);

}

void Object3D::drawTexture(float x, float y, float z, GLuint texture)
{
	drawTexture(x, y, z, 1, texture);
}

void Object3D::drawTexture(float x, float y, float z, float size, GLuint texture)
{
	drawTexture(x, y, z, 1, texture, 1, 1, 1, 1);
}

void Object3D::drawTexture(float x, float y, float z, float size, GLuint texture, RGBAL rgba) {
	drawTexture(x, y, z, size, texture, rgba.red, rgba.green, rgba.blue, rgba.alpha);
}

void Object3D::drawTexture(float x, float y, float z, float size, GLuint texture, float r, float g, float b, float a)
{
	//glEnable(GL_TEXTURE_2D);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, texture);

	drawColor(x, y, z, size, r, g, b, 1);

	//glDisable(GL_TEXTURE_2D);
}

void Object3D::draw()
{
	draw(0, 0, 0, 1);
}

void Object3D::draw(float x, float y, float z)
{
	draw(x, y, z, 1);
}

void Object3D::draw(float x, float y, float z, float size)
{
	glPushMatrix();
	if (m_shader) {
		m_model = glm::mat4(1.0f);
		m_model = glm::translate(m_model, glm::vec3(x, y, z));
		m_model = glm::scale(m_model, glm::vec3(size));
		m_shader->setMat4("model", m_model);
	}
	else {
		glTranslatef(x, y, z);
		glScalef(size, size, size);
	}

	//glPushMatrix();

	//glTranslatef(0.0f, 0.0f, 0.0f);
	//glRotatef(rotationZ, 0.0f, 0.0f, 1.0f);

	createMesh();

	//glPopMatrix();

	//glPopMatrix();


}