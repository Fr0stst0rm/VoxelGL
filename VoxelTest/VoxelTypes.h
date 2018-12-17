#pragma once

#ifndef VOXELTYPE_H

#define VOXELTYPE_H

#include "Defines.h"

enum VoxelType {
	AIR,
	DIRT,
	GRASS,
	BEDROCK
};

GLuint getTexture(VoxelType type);

#endif // !VOXELTYPE_H