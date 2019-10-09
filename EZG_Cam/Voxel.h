
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

	void draw(int x, int y, int z);

	void drawTransparent(int x, int y, int z);

	bool isTransparent();

	VoxelType m_type;

protected:
	

private:

	
};

#endif // !VOXEL_H
