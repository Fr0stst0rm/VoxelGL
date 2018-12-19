#include "Object3d.h"

Object3D::Object3D()
{
}

Object3D::~Object3D()
{
}

void Object3D::drawColor(float x, float y, float z, RGBA color)
{
	drawColor(x, y, z, 1, color.red, color.green, color.blue, color.alpha);
}

void Object3D::drawColor(float x, float y, float z, float size, RGBA color)
{
	drawColor(x, y, z, size, color.red, color.green, color.blue, color.alpha);
}

void Object3D::drawColor(float x, float y, float z, float r, float g, float b, float a)
{
	drawColor(x, y, z, 1, r, g, b, a);
}

void Object3D::drawColor(float x, float y, float z, float size, float r, float g, float b, float a)
{

	glColor4f(r, g, b,a);
	draw(x, y, z, size);

}

void Object3D::drawTexture(float x, float y, float z, GLuint texture)
{
	drawTexture(x, y, z, 1, texture);
}

void Object3D::drawTexture(float x, float y, float z, float size, GLuint texture)
{
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, texture);

	draw(x, y, z, size);

	glDisable(GL_TEXTURE_2D);
}

void Object3D::draw(float x, float y, float z)
{
	draw(x, y, z, 1);
}

void Object3D::draw(float x, float y, float z, float size)
{
	glPushMatrix();
	glTranslatef(x, y, z);

	glScalef(size, size, size);

	glPushMatrix();

	glTranslatef(0.0f, 0.0f, 0.0f);
	//glRotatef(rotationZ, 0.0f, 0.0f, 1.0f);

	createMesh();

	glPopMatrix();

	glPopMatrix();


}