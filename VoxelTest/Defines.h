
#ifndef DEFINES_H
#define DEFINES_H

#include <Windows.h>
#include <memory>

#include <GL/glut.h> 
#include <GL/gl.h>  
#include <GL/glu.h>  
#include <GL/freeglut.h>

#include <stddef.h>

#include "Logger.h"

#define XYZ_TO_ARRAY_INDEX(X,Y,Z, WIDTH, DEPTH) (((X) + ((Z) * (WIDTH))) + ((y) * (WIDTH) * (DEPTH)))

struct RGBA {
	float red = 1;
	float green = 1;
	float blue = 1;
	float alpha = 1;
};

#endif // !DEFINES_H
