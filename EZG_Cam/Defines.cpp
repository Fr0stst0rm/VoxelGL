#include "Defines.h"

glm::vec3 PointToVec3(const Point& p)
{
	return glm::vec3(p.x,p.y,p.z);
}

Point Vec3ToPoint(const glm::vec3& v)
{
	return Point(v.x,v.y,v.z);
}
