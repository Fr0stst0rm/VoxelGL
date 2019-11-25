#include "VoxelTypes.h"

RGBAL colorTable[] = {
	{0,0,0,0,0},
	{1,1,1,1,0}, // {0,0,0,1,0},
	{0,0,0,1,0},
	{0,1,0,1,0},
	{0,1,0,0.5f,0},
	{1,0,0,0.5f,0},
	{0,0,1,0.5f,0},
	{1,1,1,1,1},
	{1,0,0,1,1},
	{0,1,0,1,1},
	{0,0,1,1,1},
	{1,1,0,1,1},
};


namespace VoxelTypes
{
	GLuint getTexture(VoxelType type)
	{
		return TextureManager::getTexture(type);
	}

	GLuint getNormalMap(VoxelType type)
	{
		return TextureManager::getNormalMap(type);
	}

	RGBAL getColor(VoxelType type)
	{
		return colorTable[type];
	}

	bool isTransparent(VoxelType type)
	{
		return (colorTable[type].alpha < 1) ? true : false;
	}

	bool isShining(VoxelType type)
	{
		return (colorTable[type].light > 0) ? true : false;;
	}

	bool hasTexture(VoxelType type)
	{
		return TextureManager::containsTexture(type);
	}

}