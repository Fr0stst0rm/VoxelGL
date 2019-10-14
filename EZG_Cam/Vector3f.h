
#ifndef VECTOR3F_H
#define VECTOR3F_H

#define _USE_MATH_DEFINES

#include <math.h>
#include "Defines.h"

class Vector3f {
private:

public:

	Vector3f();
	Vector3f(float x, float y, float z);
	Vector3f(Point p);
	Vector3f(const Vector3f const &from, const Vector3f &to);
	Vector3f(const Vector3f & other);

	float x;
	float y;
	float z;

	float length();

	Vector3f normalized();

	Vector3f neg();

	float dot(Vector3f other);

	Vector3f cross(Vector3f other);

	Vector3f operator+ (const Vector3f &other) const;

	Vector3f operator- () const;
	Vector3f operator- (const Vector3f &other) const;

	Vector3f operator* (const Vector3f &other) const;
	friend Vector3f operator* (float scalar, const Vector3f& vec3f);
	friend Vector3f operator* (const Vector3f& vec3f, float scalar);

	Vector3f operator/ (const Vector3f &other) const;

	float distance(Vector3f other);
};

Vector3f QuatToDegrees(glm::quat);

#endif // !VECTOR3F_H
