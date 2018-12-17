
#ifndef _MAP_H
#define _MAP_H

#include "portal.h"
#include "pickupcube.h"
#include "wall.h"
#include <stdio.h>

// Konvertiert x, y zu arrayindex
#define xyToIndex(x,y, maxX) ( ((y) * (maxX)) + (x))

//Himmelsrichtingen 
enum Direction
{
	NORTH,
	EAST,
	SOUTH,
	WEST
};

// Mögliche Tiles
enum MapTiles
{
	PATH = 0,
	WALL = 1,
	PILL = 2,
	PORTAL = 3
};

class Map
{
public:
	Map();
	~Map();

	char getHeight();
	char getWidth();
	
	// Function to load new nevels
	void loadMap(char width,  char height, char * map);

	//Überprüft ob man in diese richtung gehen kann
	bool checkNextDir(int x, int y, Direction dir);

	//Zeichnet alle Walls
	void draw();

	void setPos(float x, float y, float z);

	// Prüfen ob alle pills im level eingesammelt wurden
	bool finished();

	float getZoom();

	Portal * getPortal(int x, int y);

	//Pill aus der Map entfernen
	PickupCube * eatPill(int x, int y);

private:
	float size = 0.5f;
	float x, y, z;

	Wall ** walls = NULL;
	PickupCube ** pickupCubes = NULL;
	Portal ** portals = NULL;

	char height = 0;
	char width = 0;

	char * map = NULL;
};

#endif // !_MAP_H

