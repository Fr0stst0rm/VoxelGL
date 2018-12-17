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

#include "tga.h"

/* some math.h files don't define pi...*/
#ifndef M_PI
#define M_PI 3.141592653
#endif

#define RAD(x) (((x)*M_PI)/180.)

class Object3D
{
public:
	Object3D();
	virtual ~Object3D();

	void setTexture(std::string path);

	//Function called by the glut display loop
	void draw(float x, float y, float z);
	void draw(float x, float y, float z, float size);

	void drawTexture(float x, float y, float z);
	void drawTexture(float x, float y, float z, float size);


protected:
	
	// virtual function to override, to create the 3D mash
	virtual void createMesh() = 0;

	virtual GLuint getTexture();

private:
};

#endif // !_OBJECT_3D_H
