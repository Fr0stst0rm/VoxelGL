#ifndef INPUT_H
#define INPUT_H

struct KeyPressedFlags
{
	bool w : 1;
	bool a : 1;
	bool s : 1;
	bool d : 1;
	bool q : 1;
	bool e : 1;
	bool c : 1;
	bool space : 1;
	bool esc : 1;
	bool up : 1;
	bool down : 1;
	bool left : 1;
	bool right : 1;
};

#endif // !INPUT_H
