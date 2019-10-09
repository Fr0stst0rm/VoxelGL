#pragma once

#ifndef LOADED_LEVEL_H
#define LOADED_LEVEL_H

#include "VoxelTypes.h"
#include "Voxel.h"
#include "Vector3f.h"

class  LoadedLevel {
public:
	static uint32_t m_width;
	static uint32_t m_height;
	static uint32_t m_depth;

	static int32_t m_centerOffsetX;
	static int32_t m_centerOffsetZ;

	static Voxel * getVoxelCentered(int32_t x, int32_t y, int32_t z);
	static Voxel * getVoxel(uint32_t x, uint32_t y, uint32_t z);
	static Voxel * getVoxel(Vector3f & pos);

	static void loadLevel(uint8_t * map, uint32_t width, uint32_t height, uint32_t depth);

	~LoadedLevel();

private: 
	static Voxel ** m_map;
};

#endif // !LOADED_LEVEL_H