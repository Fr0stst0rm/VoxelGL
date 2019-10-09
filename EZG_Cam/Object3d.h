#pragma once


#ifndef _OBJECT_3D_H
#define _OBJECT_3D_H

#include <Windows.h>
#include <GL/glut.h> 
#include <GL/gl.h>  
#include <GL/glu.h>
#include <GL/freeglut.h>

#include <iostream>
#include <string>
#include <math.h>

#include "Tga.h"
#include "Defines.h"

/* some math.h files don't define pi...*/
#ifndef M_PI
#define M_PI 3.141592653
#endif

#define RAD(x) (((x)*M_PI)/180.)

class Object3D
{
public:

	virtual ~Object3D();

	//Function called by the glut display loop

	void drawColor(float x, float y, float z, RGBA color);
	void drawColor(float x, float y, float z, float r, float g, float b, float a);
	void drawColor(float x, float y, float z, float size, RGBA color);
	void drawColor(float x, float y, float z, float size, float r, float g, float b, float a);

	void drawTexture(float x, float y, float z, GLuint texture);
	void drawTexture(float x, float y, float z, float size, GLuint texture);


protected:
	Object3D();

	// virtual function to override, to create the 3D mash
	virtual void createMesh() = 0;

	void draw(float x, float y, float z);
	void draw(float x, float y, float z, float size);

private:


};

#endif // !_OBJECT_3D_H
