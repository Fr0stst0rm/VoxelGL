#include "Object3d.h"

Object3D::Object3D()
{
}

Object3D::~Object3D()
{
}

void Object3D::setTexture(std::string path)
{
	GLsizei w, h;
	tgaInfo *info = 0;
	int mode;

	info = tgaLoad((char *)path.c_str());

	if (info->status != TGA_OK) {
		fprintf(stderr, "error loading texture image: %d\n", info->status);

		return;
	}
	if (info->width != info->height) {
		fprintf(stderr, "Image size %d x %d is not rectangular, giving up.\n",
			info->width, info->height);
		return;
	}

	mode = info->pixelDepth / 8;  // will be 3 for rgb, 4 for rgba
	glGenTextures(1, &GetTexture());

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	// Upload the texture bitmap. 
	w = info->width;
	h = info->height;

	GLint format = (mode == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format,
		GL_UNSIGNED_BYTE, info->imageData);

	tgaDestroy(info);
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
	glRotatef(rotationZ, 0.0f, 0.0f, 1.0f);
		
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
	glBindTexture(GL_TEXTURE_2D, texture);

	draw(x, y, z, size);

	glDisable(GL_TEXTURE_2D);
}

void Object3D::getTexture() {

}