#include "manpac.h"

ManPac::ManPac(int x, int y, Map * map) : map(map)
{
	currentX = x;
	currentY = y;

	oldX = x;
	oldY = y;

	nextX = 0;
	nextY = 0;

	setPos(x, y, map->getZoom());
}

void ManPac::moveToNextTile(Direction dir)
{

	if (map->checkNextDir(currentX, currentY, dir)) {
		if (!isMoving) {
			switch (dir) {
			case NORTH:
				nextY = 1;
				break;
			case EAST:
				nextX = -1;
				break;
			case SOUTH:
				nextY = -1;
				break;
			case WEST:
				nextX = 1;
				break;
			}
			oldX = currentX;
			oldY = currentY;

			std::cout << "Score: " << score << "\n";

			isMoving = true;
		}
	}
}

void ManPac::createMesh()
{
	glColor3f(1.0f, 1.0f, 0.0f);

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0f, 0.0f, 0.0f); // center point
	int numberOfSegments = 100;
	GLfloat angle;

	if (mouthMover >= 0) {
		for (int i = mouthMover; i <= numberOfSegments - mouthMover; i++) {

			angle = i * 2.0f * M_PI / numberOfSegments;
			glVertex2f(cos(angle) * manPacRadius, sin(angle) * manPacRadius);
		}

		if (mouthMover == 0) {
			mouthMover = -15;
		}
		else {
			mouthMover--;
		}

	}
	else {
		for (int i = mouthMover; i <= numberOfSegments + mouthMover; i++) {

			angle = i * 2.0f * M_PI / numberOfSegments;
			glVertex2f(cos(angle) * manPacRadius, sin(angle) * manPacRadius);
		}

		if (mouthMover == -1) {
			mouthMover = 15;
		}
		else {
			mouthMover++;
		}
	}

	glEnd();
}

void ManPac::handlePill()
{
	PickupCube * p;
	if ((p = map->eatPill(currentX, currentY)) != NULL) {
		score += p->scorePoints;
		delete p;
	}
}

void ManPac::checkPortal()
{
	Portal * p;
	if ((p = map->getPortal(currentX, currentY)) != NULL) {
		if ((p = p->counterpart) != NULL) {
			currentX = p->x;
			currentY = p->y;
			oldX = currentX;
			oldY = currentY;

			std::cout << "Setting to X: " << currentX << " Y: " << currentY << "\n";

			setPos(currentX, currentY, map->getZoom());
		}
	}
}

void ManPac::setPos(float x, float y, float z)
{
	Object3D::setPos(-(map->getWidth() / 2.0f) + (float)(x) * 1.0f + offset, -(map->getHeight() / 2.0f) + (float)(y) * 1.0f + offset, z);
}

void ManPac::resetPos()
{
	setPos(currentX, currentY,map->getZoom());
}

void ManPac::moveToNextPos()
{
	if (isMoving) {

		if (nextX > 0) {

			if (currentX < (oldX + nextX)) {
				currentX += movementSpeed;
			}
			else {
				currentX = oldX + nextX;
			}
		}
		else if (nextX < 0) {
			if (currentX > (oldX + nextX)) {
				currentX -= movementSpeed;
			}
			else {
				currentX = oldX + nextX;
			}
		}


		if (nextY > 0) {

			if (currentY < (oldY + nextY)) {
				currentY += movementSpeed;
			}
			else {
				currentY = oldY + nextY;
			}
		}
		else if (nextY < 0) {
			if (currentY > (oldY + nextY)) {
				currentY -= movementSpeed;
			}
			else {
				currentY = oldY + nextY;
			}
		}

		setPos(currentX, currentY, map->getZoom());

		// Wenn neues Tile erreicht ist auf Portal & Pill prüfen
		if ((currentX == (oldX + nextX)) && (currentY == (oldY + nextY))) {
			nextX = 0;
			nextY = 0;
			oldX = currentX;
			oldY = currentY;

			handlePill();

			checkPortal();

			std::cout << "X:" << currentX << " Y:" << currentY << "\n";
			isMoving = false;
		}
	}
}
