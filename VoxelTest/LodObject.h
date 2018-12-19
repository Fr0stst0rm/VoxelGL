
#ifndef LOD_OBJECT_H
#define LOD_OBJECT_H 

#include "Object3d.h"
#include "Vector3f.h"
#include "TextureManager.h"

class LodObject : public Object3D
{
public:
	LodObject();
	LodObject(float size);
	~LodObject();

	Vector3f m_pos;

	void draw(float distance);

private:
	float m_size = 1;

	float m_distance = 0;

	void createMesh();

	void createLod1Mesh();
	void createLod2Mesh();
	void createLod3Mesh();
};

#endif // !LOD_OBJECT_H
