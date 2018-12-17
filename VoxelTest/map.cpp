#include "map.h"

Map::Map() : x(0), y(0), z(0)
{
}

Map::~Map()
{
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {

			delete walls[xyToIndex(x, y, width)];
			delete pickupCubes[xyToIndex(x, y, width)];
			delete portals[xyToIndex(x, y, width)];
		}
	}

	delete walls;
	delete pickupCubes;
	delete portals;
}

char Map::getHeight()
{
	return height;
}

char Map::getWidth()
{
	return width;
}

void Map::loadMap(char width, char height, char * map)
{
	this->height = height;
	this->width = width;

	int wallCount = 0;

	walls = new Wall *[width*height];
	pickupCubes = new PickupCube *[width*height];
	portals = new Portal *[width*height];

	Portal * portal1 = NULL;
	Portal * portal2 = NULL;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {

			walls[xyToIndex(x, y, width)] = NULL;
			pickupCubes[xyToIndex(x, y, width)] = NULL;
			portals[xyToIndex(x, y, width)] = NULL;

			switch (map[xyToIndex(x, y, width)]) {
			case WALL:
				walls[xyToIndex(x, y, width)] = new Wall();
				walls[xyToIndex(x, y, width)]->setPos(x + this->x, (height - 1) - (y + this->y), this->z);
				walls[xyToIndex(x, y, width)]->setTexture("wall.tga");
				break;
			case PILL:
				pickupCubes[xyToIndex(x, y, width)] = new PickupCube();
				pickupCubes[xyToIndex(x, y, width)]->setPos(x + this->x, (height - 1) - (y + this->y), this->z);
				break;
			case PORTAL:
				portals[xyToIndex(x, y, width)] = new Portal(x, (height - 1) - y);

				if (portal1 == NULL) {
					portal1 = portals[xyToIndex(x, y, width)];
				}
				else if (portal2 == NULL) {
					portal2 = portals[xyToIndex(x, y, width)];
				}

				if ((portal1 != NULL) && (portal2 != NULL)) {
					portal1->counterpart = portal2;
					portal2->counterpart = portal1;

					portal1 = NULL;
					portal2 = NULL;
				}

				break;
			}

		}
	}

	this->map = map;
}

bool Map::checkNextDir(int x, int y, Direction dir)
{
	int tempX = x;
	int tempY = y;

	switch (dir) {
	case NORTH:
		tempY++;
		break;
	case EAST:
		tempX--;
		break;
	case SOUTH:
		tempY--;
		break;
	case WEST:
		tempX++;
		break;
	}

	if ((tempX >= 0) && (tempX < width) && (tempY >= 0) && (tempY < height)) {
		//std::cout << "X: " << tempX << " Y: " << tempY << " => " << (int)(map[xyToIndex(tempX, (height - 1) - tempY, width)]) << "\n";
		if (map[xyToIndex(tempX, (height - 1) - tempY, width)] != WALL) {
			return true;
		}
	}

	return false;
}

void Map::draw()
{
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			switch (map[xyToIndex(x, y, width)]) {
			case WALL:
				walls[xyToIndex(x, y, width)]->setScale(size);
				walls[xyToIndex(x, y, width)]->setPos(x + this->x, (height - 1) - (y + this->y), this->z);
				walls[xyToIndex(x, y, width)]->draw();
				break;
			case PILL:
				if (pickupCubes[xyToIndex(x, y, width)] != NULL) {
					pickupCubes[xyToIndex(x, y, width)]->setPos(x + this->x, (height - 1) - (y + this->y), this->z);
					pickupCubes[xyToIndex(x, y, width)]->draw();
				}
				break;
			case PORTAL:
				break;
			}
		}
	}
}

void Map::setPos(float x, float y, float z)
{
	this->x = x;
	this->y = -y;
	this->z = z;
}

bool Map::finished()
{
	for (int i = 0; i < (width * height); i++) {
		if (pickupCubes[i] != NULL) {
			return false;
		}
	}
	return true;
}

float Map::getZoom()
{
	return z;
}

Portal * Map::getPortal(int x, int y)
{
	return portals[xyToIndex(x, (height - 1) - y, width)];
}

PickupCube * Map::eatPill(int x, int y)
{
	PickupCube * p = pickupCubes[xyToIndex(x, (height - 1) - y, width)];
	map[xyToIndex(x, (height - 1) - y, width)] = 0;
	pickupCubes[xyToIndex(x, (height - 1) - y, width)] = NULL;
	return p;
}

