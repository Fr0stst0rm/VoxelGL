
#ifndef WALL_H
#define WALL_H 

#include "object3d.h"
#include "defines.h"

class Cube : public Object3D
{
public:
	Cube();
	Cube(float size);
	~Cube();

	bool top = true;
	bool bottom = true;
	bool left = true;
	bool right = true;
	bool front = true;
	bool back = true;
	
protected:

	void createMesh();

private:
	void drawCube();

};

#endif // !WALL_H
