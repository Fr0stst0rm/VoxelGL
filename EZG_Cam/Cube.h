
#ifndef CUBE_H
#define CUBE_H 

#include "Object3d.h"
#include "Defines.h"

enum Side {
	top = 0,
	bottom = 1,
	left = 2,
	right = 3,
	front = 4,
	back = 5
};

struct RenderedSettings {
	uint8_t top : 1, bottom : 1, left : 1, right : 1, front : 1, back : 1, glow : 1, transparent : 1;
};

class Cube : public Object3D
{
public:	
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

	bool isTransparent();
	bool isGlowing();
	

protected:

	Cube();
	//Cube(float size);

	void createMesh();

	RenderedSettings m_settings;

private:

	void createCubeMesh();
	

};

#endif // !CUBE_H
