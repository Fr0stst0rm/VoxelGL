#include "pickupcube.h"

PickupCube::PickupCube()
{

}

PickupCube::~PickupCube() 
{

}

void PickupCube::createMesh()
{
	glPushMatrix();
	glColor3f(0.9f, 0.9f, 0.9f);

	glBegin(GL_QUADS);

	if (MODE_2D) {
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.1f, -0.1f, -0.1f);
		glTexCoord2f(0.1f, 0.0f);
		glVertex3f(0.1f, -0.1f, -0.1f);
		glTexCoord2f(0.1f, 0.1f);
		glVertex3f(0.1f, 0.1f, -0.1f);
		glTexCoord2f(0.0f, 0.1f);
		glVertex3f(-0.1f, 0.1f, -0.1f);
	}
	else {
		// front face
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.1f, -0.1f, -0.1f);
		glTexCoord2f(0.1f, 0.0f);
		glVertex3f(0.1f, -0.1f, -0.1f);
		glTexCoord2f(0.1f, 0.1f);
		glVertex3f(0.1f, 0.1f, -0.1f);
		glTexCoord2f(0.0f, 0.1f);
		glVertex3f(-0.1f, 0.1f, -0.1f);

		//// top face
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-0.1f, 0.1f, -0.3f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.1f, 0.1f, -0.1f);
		glTexCoord2f(0.1f, 0.0f);
		glVertex3f(0.1f, 0.1f, -0.1f);
		glTexCoord2f(0.1f, 0.1f);
		glVertex3f(0.1f, 0.1f, -0.3f);

		//// bottom face
		glTexCoord2f(0.1f, 0.1f);
		glVertex3f(-0.1f, -0.1f, -0.3f);
		glTexCoord2f(0.0f, 0.1f);
		glVertex3f(0.1f, -0.1f, -0.3f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.1f, -0.1f, -0.1f);
		glTexCoord2f(0.1f, 0.0f);
		glVertex3f(-0.1f, -0.1f, -0.1f);

		//// right face
		glTexCoord2f(0.1f, 0.0f);
		glVertex3f(0.1f, -0.1f, -0.3f);
		glTexCoord2f(0.1f, 0.1f);
		glVertex3f(0.1f, 0.1f, -0.3f);
		glTexCoord2f(0.0f, 0.1f);
		glVertex3f(0.1f, 0.1f, -0.1f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.1f, -0.1f, -0.1f);

		//// left face
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.1f, -0.1f, -0.3f);
		glTexCoord2f(0.1f, 0.0f);
		glVertex3f(-0.1f, -0.1f, -0.1f);
		glTexCoord2f(0.1f, 0.1f);
		glVertex3f(-0.1f, 0.1f, -0.1f);
		glTexCoord2f(0.0f, 0.1f);
		glVertex3f(-0.1f, 0.1f, -0.3f);
	}

	glEnd();
	glPopMatrix();
}


