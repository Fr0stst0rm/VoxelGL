
#ifndef CUBE_H
#define CUBE_H 

#include "Object3d.h"
#include "Defines.h"
#include "VoxelTypes.h" //TODO del after voxel class is created

enum Side {
	top = 0,
	bottom = 1,
	left = 2,
	right = 3,
	front = 4,
	back = 5
};

struct RenderedSettings {
	uint8_t top : 1, bottom : 1, left : 1, right : 1, front : 1, back : 1, glow : 1;
};

class Cube : public Object3D
{
public:
	Cube();
	//Cube(float size);
	~Cube();

	// Cube sides to be rendered
	bool isTopRendered();
	bool isBottomRendered();
	bool isLeftRendered();
	bool isRightRendered();
	bool isFrontRendered();
	bool isBackRendered();

	void setTopRendered(bool b);
	void setBottomRendered(bool b);
	void setLeftRendered(bool b);
	void setRightRendered(bool b);
	void setFrontRendered(bool b);
	void setBackRendered(bool b);
	

protected:

	void createMesh();

	virtual GLuint getTexture();

private:
	void drawCube();

	uint16_t cubeID;

	RenderedSettings m_renderedSides;

};

#endif // !CUBE_H
