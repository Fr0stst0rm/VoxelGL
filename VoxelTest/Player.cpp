#include "Player.h"

Player::Player()
{
	m_pos.x = 0;
	m_pos.y = 0;
	m_pos.z = 0;
}

Player::Player(float x, float y, float z)
{
	m_pos.x = x;
	m_pos.y = y;
	m_pos.z = z;
}

Player::~Player()
{
}
