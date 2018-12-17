#include "Object3d.h"

Object3D::Object3D()
{
}

Object3D::~Object3D()
{
}

void Object3D::draw(float x, float y, float z)
{
	draw(x,y,z,1);
}

void Object3D::draw(float x, float y, float z, float size)
{
	glPushMatrix();
	glTranslatef(x, y, z);
	//glTranslatef(0, y, 0);
	//glTranslatef(0, 0, z);
	
	glScalef(size, size, 1.0f);

	glPushMatrix();

	glTranslatef(0.0f, 0.0f, 0.0f);
	//glRotatef(rotationZ, 0.0f, 0.0f, 1.0f);
	
	glColor3f(0, 1, 0); // TODO set color

	createMesh();	
	
	glPopMatrix();
	
	glPopMatrix();


}

void Object3D::drawTexture(float x, float y, float z)
{
	drawTexture(x, y, z, 1);
}

void Object3D::drawTexture(float x, float y, float z, float size)
{
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, getTexture());

	draw(x, y, z, size);

	glDisable(GL_TEXTURE_2D);
}

GLuint Object3D::getTexture() {
	return NULL;
}