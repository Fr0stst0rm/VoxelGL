#ifndef PLAYER_H
#define PLAYER_H 

#include "Defines.h"
#include "Vector3f.h"

class Player
{
public:
	Player();
	Player(float x, float y, float z);
	Player(Vector3f pos, Vector3f rot);

	~Player();

	Vector3f m_pos;
	Vector3f m_rot;

	float m_walkingSpeed = 0.05f;
	float m_rotationSpeed = 0.5f;

	Vector3f getLookingDir();

protected:

private:

};

#endif // !PLAYER_H
