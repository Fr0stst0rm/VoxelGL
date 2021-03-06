#include "Voxel.h"

const float Voxel::VOXEL_SIZE = 0.5f;

Voxel::Voxel(VoxelType type) : m_type(type)
{
	if (isTransparent()) {
		m_settings.transparent = true;
	}
}

Voxel::~Voxel()
{
}

void Voxel::draw() {
	Cube::draw();
}

void Voxel::draw(int x, int y, int z)
{
	if (m_type != VoxelType::AIR) {
		if (VoxelTypes::hasTexture(m_type)) {
			drawTexture(x, y, z, VOXEL_SIZE, VoxelTypes::getTexture(m_type), VoxelTypes::getNormalMap(m_type), VoxelTypes::getColor(m_type));
		}
		else {
			drawColor(x, y, z, VOXEL_SIZE, VoxelTypes::getColor(m_type));
		}
	}

}

void Voxel::drawTransparent(int x, int y, int z)
{
	if (m_type != VoxelType::AIR) {
		drawColor(x, y, z, VOXEL_SIZE, VoxelTypes::getColor(m_type));
	}
}

bool Voxel::isTransparent()
{
	return VoxelTypes::isTransparent(m_type);
}

bool Voxel::isShining()
{
	return VoxelTypes::isShining(m_type);
}
