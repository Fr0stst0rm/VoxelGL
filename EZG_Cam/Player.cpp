#include "Player.h"

Player::Player() : Player(0,0,0)
{
}

Player::Player(float x, float y, float z)
{
	setPos(glm::vec3(x,y,z));
}

Player::~Player()
{
}

glm::vec3 Player::getPos()
{
	return m_pos;
}

void Player::setPos(glm::vec3 pos)
{
	m_pos = pos;
	
	Position.x = pos.x;
	Position.y = pos.y + m_height; // höhe der cam
	Position.z = pos.z;
}

void Player::setMovementSpeed(float speed)
{
	m_movementSpeed = speed;
}

void Player::setRotationSpeed(float speed)
{
	MouseSensitivity = speed;
}

glm::vec3 Player::getViewPos()
{
	return Position;
}

/*
glm::vec3 Player::getLookingDir()
{
	float y = glm::degrees(glm::eulerAngles(m_quatRot).y);
	float z = cosf(y / 180 * M_PI);
	float x = sinf(y / 180 * M_PI);

	//cout << "X: " << x << " Z: " << z << "\n";

	return glm::vec3(x, 0, z);
}
*/

void Player::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = m_movementSpeed * deltaTime;
	if (direction == FORWARD)
		m_pos += Front * velocity;
	if (direction == BACKWARD)
		m_pos -= Front * velocity;
	if (direction == LEFT)
		m_pos -= Right * velocity;
	if (direction == RIGHT)
		m_pos += Right * velocity;

	setPos(m_pos);
}
