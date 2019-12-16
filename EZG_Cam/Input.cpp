#include "Input.h"

KeyFlags keyPressedFlags;
KeyFlags keyChangedFlags;
KeyFlags lastKeyState;

void updateInput() {
	if (keyPressedFlags.w) {
		(keyPressedFlags.w != lastKeyState.w) ? keyChangedFlags.w = true : keyChangedFlags.w = false;
	}
	else {
		(keyPressedFlags.w != lastKeyState.w) ? keyChangedFlags.w = true : keyChangedFlags.w = false;

	}
	if (keyPressedFlags.s) {
		(keyPressedFlags.s != lastKeyState.s) ? keyChangedFlags.s = true : keyChangedFlags.s = false;
	}
	else {
		(keyPressedFlags.s != lastKeyState.s) ? keyChangedFlags.s = true : keyChangedFlags.s = false;

	}
	if (keyPressedFlags.a) {
		(keyPressedFlags.a != lastKeyState.a) ? keyChangedFlags.a = true : keyChangedFlags.a = false;
	}
	else {
		(keyPressedFlags.a != lastKeyState.a) ? keyChangedFlags.a = true : keyChangedFlags.a = false;

	}
	if (keyPressedFlags.d) {
		(keyPressedFlags.d != lastKeyState.d) ? keyChangedFlags.d = true : keyChangedFlags.d = false;
	}
	else {
		(keyPressedFlags.d != lastKeyState.d) ? keyChangedFlags.d = true : keyChangedFlags.d = false;

	}
	if (keyPressedFlags.q) {
		(keyPressedFlags.q != lastKeyState.q) ? keyChangedFlags.q = true : keyChangedFlags.q = false;
	}
	else {
		(keyPressedFlags.q != lastKeyState.q) ? keyChangedFlags.q = true : keyChangedFlags.q = false;

	}
	if (keyPressedFlags.e) {
		(keyPressedFlags.e != lastKeyState.e) ? keyChangedFlags.e = true : keyChangedFlags.e = false;
	}
	else {
		(keyPressedFlags.e != lastKeyState.e) ? keyChangedFlags.e = true : keyChangedFlags.e = false;
	}
	if (keyPressedFlags.l) {
		(keyPressedFlags.l != lastKeyState.l) ? keyChangedFlags.l = true : keyChangedFlags.l = false;
	}
	else {
		(keyPressedFlags.l != lastKeyState.l) ? keyChangedFlags.l = true : keyChangedFlags.l = false;
	}
	if (keyPressedFlags.t) {
		(keyPressedFlags.t != lastKeyState.t) ? keyChangedFlags.t = true : keyChangedFlags.t = false;
	}
	else {
		(keyPressedFlags.t != lastKeyState.t) ? keyChangedFlags.t = true : keyChangedFlags.t = false;
	}
	if (keyPressedFlags.c) {
		(keyPressedFlags.c != lastKeyState.c) ? keyChangedFlags.c = true : keyChangedFlags.c = false;
	}
	else {
		(keyPressedFlags.c != lastKeyState.c) ? keyChangedFlags.c = true : keyChangedFlags.c = false;

	}
	if (keyPressedFlags.f) {
		(keyPressedFlags.f != lastKeyState.f) ? keyChangedFlags.f = true : keyChangedFlags.f = false;
	}
	else {
		(keyPressedFlags.f != lastKeyState.f) ? keyChangedFlags.f = true : keyChangedFlags.f = false;

	}
	if (keyPressedFlags.v) {
		(keyPressedFlags.v != lastKeyState.v) ? keyChangedFlags.v = true : keyChangedFlags.v = false;
	}
	else {
		(keyPressedFlags.v != lastKeyState.v) ? keyChangedFlags.v = true : keyChangedFlags.v = false;

	}
	if (keyPressedFlags.b) {
		(keyPressedFlags.b != lastKeyState.b) ? keyChangedFlags.b = true : keyChangedFlags.b = false;
	}
	else {
		(keyPressedFlags.b != lastKeyState.b) ? keyChangedFlags.b = true : keyChangedFlags.b = false;

	}
	if (keyPressedFlags.n) {
		(keyPressedFlags.n != lastKeyState.n) ? keyChangedFlags.n = true : keyChangedFlags.n = false;
	}
	else {
		(keyPressedFlags.n != lastKeyState.n) ? keyChangedFlags.n = true : keyChangedFlags.n = false;

	}
	if (keyPressedFlags.m) {
		(keyPressedFlags.m != lastKeyState.m) ? keyChangedFlags.m = true : keyChangedFlags.m = false;
	}
	else {
		(keyPressedFlags.m != lastKeyState.m) ? keyChangedFlags.m = true : keyChangedFlags.m = false;

	}
	if (keyPressedFlags.up) {
		(keyPressedFlags.up != lastKeyState.up) ? keyChangedFlags.up = true : keyChangedFlags.up = false;
	}
	else {
		(keyPressedFlags.up != lastKeyState.up) ? keyChangedFlags.up = true : keyChangedFlags.up = false;
	}
	if (keyPressedFlags.down) {
		(keyPressedFlags.down != lastKeyState.down) ? keyChangedFlags.down = true : keyChangedFlags.down = false;
	}
	else {
		(keyPressedFlags.down != lastKeyState.down) ? keyChangedFlags.down = true : keyChangedFlags.down = false;

	}
	if (keyPressedFlags.left) {
		(keyPressedFlags.left != lastKeyState.left) ? keyChangedFlags.left = true : keyChangedFlags.left = false;
	}
	else {
		(keyPressedFlags.left != lastKeyState.left) ? keyChangedFlags.left = true : keyChangedFlags.left = false;

	}
	if (keyPressedFlags.right) {
		(keyPressedFlags.right != lastKeyState.right) ? keyChangedFlags.right = true : keyChangedFlags.right = false;
	}
	else {
		(keyPressedFlags.right != lastKeyState.right) ? keyChangedFlags.right = true : keyChangedFlags.right = false;

	}
	if (keyPressedFlags.esc) {
		(keyPressedFlags.esc != lastKeyState.esc) ? keyChangedFlags.esc = true : keyChangedFlags.esc = false;
	}
	else {
		(keyPressedFlags.esc != lastKeyState.esc) ? keyChangedFlags.esc = true : keyChangedFlags.esc = false;

	}
	if (keyPressedFlags.space) {
		(keyPressedFlags.space != lastKeyState.space) ? keyChangedFlags.space = true : keyChangedFlags.space = false;
	}
	else {
		(keyPressedFlags.space != lastKeyState.space) ? keyChangedFlags.space = true : keyChangedFlags.space = false;

	}

	lastKeyState = keyPressedFlags;
}


void specialKeyPressed(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		keyPressedFlags.up = true;
		break;
	case GLUT_KEY_DOWN:
		keyPressedFlags.down = true;
		break;
	case GLUT_KEY_LEFT:
		keyPressedFlags.left = true;
		break;
	case GLUT_KEY_RIGHT:
		keyPressedFlags.right = true;
		break;
	}
}

void keyPressed(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		keyPressedFlags.esc = true;
		break;
	case 'w':
		keyPressedFlags.w = true;
		break;
	case 's':
		keyPressedFlags.s = true;
		break;
	case 'a':
		keyPressedFlags.a = true;
		break;
	case 'd':
		keyPressedFlags.d = true;
		break;
	case 'q':
		keyPressedFlags.q = true;
		break;
	case 'e':
		keyPressedFlags.e = true;
		break;
	case 'l':
		keyPressedFlags.l = true;
		break;
	case 't':
		keyPressedFlags.t = true;
		break;
	case 'c':
		keyPressedFlags.c = true;
		break;
	case 'f':
		keyPressedFlags.f = true;
		break;
	case 'v':
		keyPressedFlags.v = true;
		break;
	case 'b':
		keyPressedFlags.b = true;
		break;
	case 'n':
		keyPressedFlags.n = true;
		break;
	case 'm':
		keyPressedFlags.m = true;
		break;
	case ' ':
		keyPressedFlags.space = true;
		break;
	}
}
void specialKeyUp(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_UP:
		keyPressedFlags.up = false;
		break;
	case GLUT_KEY_DOWN:
		keyPressedFlags.down = false;
		break;
	case GLUT_KEY_LEFT:
		keyPressedFlags.left = false;
		break;
	case GLUT_KEY_RIGHT:
		keyPressedFlags.right = false;
		break;
	}
}

void keyUp(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		keyPressedFlags.esc = false;
		break;
	case 'w':
		keyPressedFlags.w = false;
		break;
	case 's':
		keyPressedFlags.s = false;
		break;
	case 'a':
		keyPressedFlags.a = false;
		break;
	case 'd':
		keyPressedFlags.d = false;
		break;
	case 'q':
		keyPressedFlags.q = false;
		break;
	case 'e':
		keyPressedFlags.e = false;
		break;
	case 'l':
		keyPressedFlags.l = false;
		break;
	case 't':
		keyPressedFlags.t = false;
		break;
	case 'c':
		keyPressedFlags.c = false;
		break;
	case 'f':
		keyPressedFlags.f = false;
		break;
	case 'v':
		keyPressedFlags.v = false;
		break;
	case 'b':
		keyPressedFlags.b = false;
		break;
	case 'n':
		keyPressedFlags.n = false;
		break;
	case 'm':
		keyPressedFlags.m = false;
		break;
	case ' ':
		keyPressedFlags.space = false;
		break;
	}
}