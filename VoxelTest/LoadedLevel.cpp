#include "LoadedLevel.h"

uint32_t LoadedLevel::m_width = 0;
uint32_t LoadedLevel::m_height = 0;
uint32_t LoadedLevel::m_depth = 0;

int32_t LoadedLevel::m_centerOffsetX = 0;
int32_t LoadedLevel::m_centerOffsetZ = 0;

Voxel ** LoadedLevel::m_map = nullptr;

void LoadedLevel::loadLevel(uint8_t * map, uint32_t width, uint32_t height, uint32_t depth)
{

	static LoadedLevel instance; // To call the destructor ???

	if (m_map != nullptr) {

		for (long long i = 0; i < (m_width*m_depth*m_height); i++) {
			delete m_map[i];
		}

		free(m_map);
	}

	m_width = width;
	m_depth = depth;
	m_height = height;

	m_centerOffsetX = (m_width / 2);
	m_centerOffsetZ = (m_depth / 2);
	
	int test = sizeof(Voxel);

	m_map = static_cast<Voxel ** >(malloc(m_width*m_depth*m_height * sizeof(Voxel)));

	for (long long i = 0; i < (m_width*m_depth*m_height); i++) {
		m_map[i] = new Voxel(static_cast<VoxelType>(map[i]));
	}

}

LoadedLevel::~LoadedLevel()
{
	if (m_map != nullptr) {

		for (long long i = 0; i < (m_width*m_depth*m_height); i++) {
			delete m_map[i];
		}

		free(m_map);
	}
}

Voxel * LoadedLevel::getVoxelCentered(int32_t x, int32_t y, int32_t z)
{
	return m_map[static_cast<uint32_t>(XYZ_TO_ARRAY_INDEX(x + m_centerOffsetX, y, z + m_centerOffsetZ, LoadedLevel::m_width, LoadedLevel::m_depth))];
}

Voxel * LoadedLevel::getVoxel(uint32_t x, uint32_t y, uint32_t z)
{
	return m_map[static_cast<uint32_t>(XYZ_TO_ARRAY_INDEX(x, y, z, LoadedLevel::m_width, LoadedLevel::m_depth))];
}

Voxel * LoadedLevel::getVoxel(Vector3f &pos)
{
	return getVoxel(pos.x,pos.y,pos.z);
}
