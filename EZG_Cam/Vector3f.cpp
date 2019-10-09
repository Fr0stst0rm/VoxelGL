#include "Vector3f.h"

Vector3f::Vector3f() : x(0), y(0), z(0)
{
}

Vector3f::Vector3f(float x, float y, float z) : x(x), y(y), z(z)
{
}

Vector3f::Vector3f(const Vector3f & other)
{
	x = other.x;
	y = other.y;
	z = other.z;
}

Vector3f::Vector3f(const Vector3f const &from, const Vector3f &to) : Vector3f(to - from)
{
}

float Vector3f::length() {
	return sqrt((x * x) + (y * y) + (z * z));
}

Vector3f Vector3f::normalized()
{
	float mag = length();

	return Vector3f(x / mag, y / mag, z / mag);
}

Vector3f Vector3f::neg()
{
	return Vector3f(-x, -y, -z);
}

float Vector3f::dot(Vector3f other)
{
	return x * other.x + y * other.y + z * other.z;
}

Vector3f Vector3f::cross(Vector3f other)
{
	float x_ = y * other.z- z * other.y;
	float y_ = z * other.x - x * other.z;
	float z_ = x * other.y- y * other.x;

	return Vector3f(x_, y_, z_);
}

Vector3f Vector3f::operator+(const Vector3f & other) const
{
	return Vector3f(x + other.x, y + other.y, z + other.z);
}

Vector3f Vector3f::operator-(const Vector3f & other) const
{
	return Vector3f(x - other.x, y - other.y, z - other.z);
}

Vector3f Vector3f::operator*(const Vector3f & other) const
{
	return Vector3f(x * other.x, y * other.y, z * other.z);
}

Vector3f Vector3f::operator/(const Vector3f & other) const
{
	return Vector3f(x / other.x, y / other.y, z / other.z);
}
