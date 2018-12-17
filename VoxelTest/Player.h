#ifndef PLAYER_H
#define PLAYER_H 

#include "Defines.h"

struct Position {
	float x = 0;
	float y = 0;
	float z = 0;
};

class Player
{
public:
	Player();
	Player(float x, float y, float z);
	~Player();

	Position m_pos;

	float m_walkingSpeed = 0.05f;

protected:

private:

};

#endif // !PLAYER_H
