
#ifndef SPLINE_H
#define SPLINE_H 

#include "Object3d.h"
#include "Defines.h"
#include "Vector3f.h"
#include <vector>
#include <math.h>
#include <glm/glm.hpp>

class Spline : public Object3D
{
public:
	Spline();
	~Spline();

	void setRendered(bool b);

	void addPoint(float x, float y, float z);
	void addPoint(Point p);
	void addPoint(Point p, glm::quat r);

	void clearPoints();

	void recalcSpline();

	Point getStart();
	Point getEnd();
	Point getByIndex(int index);
	Point getByTime(float time);

	int getPointCount();
	
	float getLineLength();

	void drawSpline();

	void setLineWidth(float lineWidth);
	void setColor(float r, float g, float b, float a );

	bool toggleSplineRender();

	Point calcSplinePoint(Point p0, Point p1, Point p2, Point p3, float t);

	glm::quat getCameraRotationAtTime(float time);


	//Resolution steps per distance unit --> Calulate point distance 
	int m_ResolutionSteps = 10;
protected:

	void createMesh();
	
	std::vector<Point>* m_ControlPoints;
	std::vector<Point>* m_SplinePoints;

	std::vector<glm::quat> * m_CamRotQuat;

	std::vector<Point> calcSplineSeg(Point p0, Point p1, Point p2, Point p3);

	glm::quat squad(glm::quat q0, glm::quat q1, glm::quat q2, glm::quat q3, float t);

	RGBAL m_Color = { 1,1,1,1 };

	float m_LineWidth = 1.0f;


	bool m_Spline;
private:
	using Object3D::drawColor;

	using Object3D::drawTexture;

	void printPoints(std::vector<Point>* vec);

};

#endif // !SPLINE_H
