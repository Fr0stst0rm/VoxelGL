#ifndef PLAYER_H
#define PLAYER_H 

#include "Defines.h"
#include "Camera.h"
#include "Vector3f.h"

class Player : public Camera
{
public:
	Player();
	Player(float x, float y, float z);

	~Player();

	glm::vec3 getPos();
	void setPos(glm::vec3 pos);
	
	void setMovementSpeed(float speed);
	void setRotationSpeed(float speed);

	glm::vec3 getViewPos();

	float m_movementSpeed;
	glm::quat m_quatRot;
	
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
protected:

private:
	
	glm::vec3 m_pos;
	float m_height = 2.0f;

};

#endif // !PLAYER_H
