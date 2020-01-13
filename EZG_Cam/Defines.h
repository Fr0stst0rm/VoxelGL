
#ifndef DEFINES_H
#define DEFINES_H

#include <Windows.h>
#include <memory>

//#include <GL/glut.h> 
#include <GL/gl.h>  
#include <GL/glu.h>  
#include <GL/freeglut.h>

#include <stddef.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "MathDefines.h"

#include "Shader.h"


#include "Logger.h"
#include "Point.h"

#define XYZ_TO_ARRAY_INDEX(X,Y,Z, WIDTH, DEPTH) (((X) + ((Z) * (WIDTH))) + ((y) * (WIDTH) * (DEPTH)))

struct RGBAL {
	float red = 1;
	float green = 1;
	float blue = 1;
	float alpha = 1;
	float light = 1;
};

glm::vec3 PointToVec3(const Point& p);
Point Vec3ToPoint(const glm::vec3& v);

#endif // !DEFINES_H
