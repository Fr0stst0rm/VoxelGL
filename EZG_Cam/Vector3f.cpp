#include "Vector3f.h"

Vector3f::Vector3f() : x(0), y(0), z(0)
{
}

Vector3f::Vector3f(float x, float y, float z) : x(x), y(y), z(z)
{
}

Vector3f::Vector3f(Point p) : Vector3f(p.x, p.y, p.z)
{
}

Vector3f::Vector3f(const Vector3f& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
}

Vector3f::Vector3f(const Vector3f const& from, const Vector3f& to) : Vector3f(to - from)
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
	float x_ = y * other.z - z * other.y;
	float y_ = z * other.x - x * other.z;
	float z_ = x * other.y - y * other.x;

	return Vector3f(x_, y_, z_);
}

Vector3f Vector3f::operator+(const Vector3f& other) const
{
	return Vector3f(x + other.x, y + other.y, z + other.z);
}

Vector3f Vector3f::operator-() const
{
	return Vector3f(-x, -y, -z);
}

Vector3f Vector3f::operator-(const Vector3f& other) const
{
	return Vector3f(x - other.x, y - other.y, z - other.z);
}

Vector3f Vector3f::operator*(const Vector3f& other) const
{
	return Vector3f(x * other.x, y * other.y, z * other.z);
}

Vector3f Vector3f::operator/(const Vector3f& other) const
{
	return Vector3f(x / other.x, y / other.y, z / other.z);
}

float Vector3f::distance(Vector3f other)
{
	return sqrtf(pow(this->x - other.x, 2) + pow(this->y - other.y, 2) + pow(this->z - other.z, 2));
}

Vector3f operator*(float scalar, const Vector3f& vec3f)
{
	return Vector3f(scalar * vec3f.x, scalar * vec3f.y, scalar * vec3f.z);
}

Vector3f operator*(const Vector3f& vec3f, float scalar)
{
	return scalar * vec3f;
}

Vector3f QuatToDegrees(glm::quat q)
{
	Vector3f angles;

	// roll (x-axis rotation)
	double sinr_cosp = +2.0 * (q.w * q.x + q.y * q.z);
	double cosr_cosp = +1.0 - 2.0 * (q.x * q.x + q.y * q.y);
	angles.x = atan2(sinr_cosp, cosr_cosp);

	// pitch (y-axis rotation)
	double sinp = +2.0 * (q.w * q.y - q.z * q.x);
	if (fabs(sinp) >= 1)
		angles.y = copysign(M_PI / 2, sinp); // use 90 degrees if out of range
	else
		angles.y = asin(sinp);

	// yaw (z-axis rotation)
	double siny_cosp = +2.0 * (q.w * q.z + q.x * q.y);
	double cosy_cosp = +1.0 - 2.0 * (q.y * q.y + q.z * q.z);
	angles.z = atan2(siny_cosp, cosy_cosp);

	angles.x = glm::degrees(angles.x);
	angles.y = glm::degrees(angles.y);
	angles.z = glm::degrees(angles.z);

	return angles;
}