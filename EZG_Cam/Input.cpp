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
	if (keyPressedFlags.c) {
		(keyPressedFlags.c != lastKeyState.c) ? keyChangedFlags.c = true : keyChangedFlags.c = false;
	}
	else {
		(keyPressedFlags.c != lastKeyState.c) ? keyChangedFlags.c = true : keyChangedFlags.c = false;

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
