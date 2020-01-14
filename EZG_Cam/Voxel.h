
#ifndef VOXEL_H
#define VOXEL_H 

#include "Defines.h"
#include "Cube.h"
#include "VoxelTypes.h" //TODO del after voxel class is created
#include "Vector3f.h"



struct SortingHelper
{
	Vector3f position;
	float sortingVal;
};

class Voxel : public Cube
{
public:
	Voxel(VoxelType type);
	~Voxel();

	void draw();
	void draw(int x, int y, int z);

	void drawTransparent(int x, int y, int z);

	bool isTransparent();
	bool isShining();

	VoxelType m_type;

	static const float VOXEL_SIZE;

protected:
private:

	
};

#endif // !VOXEL_H
