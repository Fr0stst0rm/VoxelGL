#pragma once

#ifndef VOXELTYPES_H

#define VOXELTYPES_H

#include "Defines.h"
#include "TextureManager.h"

enum VoxelType : uint16_t {
	AIR = 0,
	BEDROCK = 1,
	DIRT = 2,
	GRASS = 3,
	GLASS_GREEN = 4,
	GLASS_RED = 5,
	GLASS_BLUE = 6
};

extern RGBA colorTable[];

namespace VoxelTypes
{
	GLuint getTexture(VoxelType type);
	RGBA getColor(VoxelType type);
	bool isTransparent(VoxelType type);
	bool hasTexture(VoxelType type);
}
#endif // !VOXELTYPES_H