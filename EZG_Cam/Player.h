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
	glm::quat m_keyRot;

	float m_walkingSpeed = 1.0f;
	float m_rotationSpeed = 0.5f;

	Vector3f getLookingDir();

protected:

private:

};

#endif // !PLAYER_H
