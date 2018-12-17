#pragma once

#ifndef PORTAL_H
#define PORTAL_H 

#include "defines.h"

class Portal
{
public:
	Portal(int x, int y);
	~Portal();

	int x = 0;
	int y = 0;

	Portal * counterpart = NULL;

protected:
private:
};

#endif // !PORTAL_H
