
#ifndef SPLINE_H
#define SPLINE_H 

#include "Object3d.h"
#include "Defines.h"
#include <vector>

class Spline : public Object3D
{
public:
	Spline();
	~Spline();

	void setRendered(bool b);

	void addSplinePoint(float x, float y, float z);
	void addSplinePoint(Point p);
	void clearSplinePoints();
	   
	void drawSpline();

	void setLineWidth(float lineWidth);
	void setColor(float r, float g, float b, float a );

protected:

	void createMesh();
	
	std::vector<Point> * m_SplinePoints;

	RGBA m_Color = { 1,1,1,1 };

	float m_LineWidth = 1.0f;

	int m_Steps = 10;
private:
	using Object3D::drawColor;

	using Object3D::drawTexture;

};

#endif // !SPLINE_H
