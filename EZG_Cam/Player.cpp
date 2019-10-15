#include "Player.h"

Player::Player()
{
	m_pos = Vector3f();
}

Player::Player(float x, float y, float z)
{
	m_pos = Vector3f(x,y,z);
}

Player::Player(Vector3f pos, Vector3f rot) : m_pos(pos), m_rot(rot)
{
}

Player::~Player()
{
}

Vector3f Player::getLookingDir()
{
	float y = glm::degrees(glm::eulerAngles(m_keyRot).y);
	float z = cosf(y / 180 * M_PI);
	float x = sinf(y / 180 * M_PI);

	//cout << "X: " << x << " Z: " << z << "\n";

	return Vector3f(x,0,z);
}
