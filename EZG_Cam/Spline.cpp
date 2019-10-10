#include "Spline.h"

Spline::Spline()
{
	m_SplinePoints = new std::vector<Point>();
	m_SplinePoints->push_back({ 0.0f, 0.0f, -1.0f });
	m_SplinePoints->push_back({ 0.5f, 1.0f, -1.0f });
	m_SplinePoints->push_back({ 0.0f, 2.0f, -1.0f });
	m_SplinePoints->push_back({ -0.5f, 3.0f, -1.0f });
	m_SplinePoints->push_back({ 0.0f, 4.0f, -1.0f });
	m_SplinePoints->push_back({ 0.5f, 5.0f, -1.0f });
}

Spline::~Spline()
{
	m_SplinePoints->clear();
	delete m_SplinePoints;
}

void Spline::setRendered(bool b)
{
}

void Spline::addSplinePoint(float x, float y, float z)
{
	addSplinePoint({ x,y,z });
}

void Spline::addSplinePoint(Point p)
{
	m_SplinePoints->push_back(p);
	cout << "Points " << m_SplinePoints->size() << "\n";
}

void Spline::clearSplinePoints()
{
	m_SplinePoints->clear();
}

void Spline::drawSpline()
{
	createMesh();
}

void Spline::setLineWidth(float lineWidth)
{
	m_LineWidth = lineWidth;
}

void Spline::setColor(float r, float g, float b, float a)
{
	m_Color.red = r;
	m_Color.green = g;
	m_Color.blue = b;
	m_Color.alpha = a;
}

void Spline::createMesh()
{
	glColor4f(m_Color.red, m_Color.green, m_Color.blue, m_Color.alpha);
	glLineWidth(m_LineWidth);

	glPushMatrix();
	glBegin(GL_LINE_STRIP);

	std::vector<Point>::iterator splPoint;

	for (splPoint = m_SplinePoints->begin(); splPoint != m_SplinePoints->end(); ++splPoint) {
		glVertex3f(splPoint->x, splPoint->y, splPoint->z);
	}

	glEnd();
	glPopMatrix();

	glLineWidth(1.0f);
}
