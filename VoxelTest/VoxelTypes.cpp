#include "VoxelTypes.h"

GLuint getTexture(VoxelType type)
{
	return TextureManager::getTexture(type);
}
