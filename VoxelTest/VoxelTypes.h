#pragma once

#ifndef VOXELTYPE_H

#define VOXELTYPE_H

#include "Defines.h"
#include "TextureManager.h"

enum VoxelType : uint16_t {
	AIR = 0,
	BEDROCK = 1,
	DIRT = 2,
	GRASS = 3
};

GLuint getTexture(VoxelType type);

#endif // !VOXELTYPE_H