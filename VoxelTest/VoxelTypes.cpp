#include "VoxelTypes.h"

RGBA colorTable[] = {
	{0,0,0,0},
	{0,0,0,1},
	{0,0,0,1},
	{0,1,0,1},
	{0,1,0,0.5f},
	{1,0,0,0.5f},
	{0,0,1,0.5f}
};


namespace VoxelTypes
{
	GLuint getTexture(VoxelType type)
	{
		return TextureManager::getTexture(type);
	}

	RGBA getColor(VoxelType type)
	{
		return colorTable[type];
	}

	bool isTransparent(VoxelType type)
	{
		return (colorTable[type].alpha < 1) ? true : false;
	}

	bool hasTexture(VoxelType type)
	{
		return TextureManager::containsTexture(type);
	}

}