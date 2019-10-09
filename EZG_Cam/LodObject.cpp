#include "LodObject.h"

LodObject::LodObject()
{
}

LodObject::LodObject(float size) : m_size(size)
{
}

LodObject::~LodObject()
{
}

void LodObject::draw(float distance)
{
	m_distance = distance;

	drawTexture(m_pos.x,m_pos.y,m_pos.z,m_size,TextureManager::getTexture(0));
}

void LodObject::createMesh()
{
	if (m_distance < 5) {
		createLod1Mesh();
	}
	else if (m_distance < 10) {
		createLod2Mesh();
	}
	else {
		createLod3Mesh();
	}
}

void LodObject::createLod1Mesh()
{
	glutSolidSphere(1, 60, 60);
}

void LodObject::createLod2Mesh()
{
	glutSolidSphere(1, 15, 15);
}

void LodObject::createLod3Mesh()
{
	glutSolidSphere(1, 7, 7);
}
