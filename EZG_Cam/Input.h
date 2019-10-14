#ifndef INPUT_H
#define INPUT_H

struct KeyFlags
{
	bool w : 1;
	bool a : 1;
	bool s : 1;
	bool d : 1;
	bool q : 1;
	bool e : 1;
	bool c : 1;
	bool l : 1;
	bool t : 1;
	bool f : 1;
	bool space : 1;
	bool esc : 1;
	bool up : 1;
	bool down : 1;
	bool left : 1;
	bool right : 1;
};

extern KeyFlags keyPressedFlags;
extern KeyFlags keyChangedFlags;
extern KeyFlags lastKeyState;

void updateInput();

#endif // !INPUT_H
