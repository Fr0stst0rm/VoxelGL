#pragma once

#ifndef _MAN_PAC_H
#define _MAN_PAC_H

#include "object3d.h"
#include "map.h"

class ManPac : public Object3D
{
public:
	ManPac(int x, int y, Map * map);

	//ManPac geht 1 Tile in die angegebene Richtung
	void moveToNextTile(Direction dir);

	float movementSpeed = 0.075f;

	bool isMoving = false;

	void moveToNextPos();

	float offset = 0.45f;

	void setPos(float x, float y, float z);

	int score = 0;

	void resetPos();

protected:

	void createMesh();

private:
	int mouthMover = 15;

	GLfloat manPacRadius = 0.4f;

	Map * map = NULL;

	float nextX = 0;
	float nextY = 0;

	float currentX = 0;
	float currentY = 0;

	float oldX = 0;
	float oldY = 0;

	Direction currentDir = NORTH;

	void checkPortal();
	void handlePill();

};


#endif // !_MAN_PAC_H
