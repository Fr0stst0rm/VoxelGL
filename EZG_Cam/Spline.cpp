#include "Spline.h"

Spline::Spline() : m_Spline(true)
{
	m_ControlPoints = new std::vector<Point>();
	m_SplinePoints = new std::vector<Point>();

	m_CamRot = new std::vector<glm::vec3>;
	m_CamRotQuat = new std::vector<glm::quat>;

	addPoint({ 0.0f, 2.0f, 4.0f });
	addPoint({ 0.0f, 2.0f, 3.0f });
	addPoint({ 0.0f, 2.0f, 2.0f });
	addPoint({ 0.0f, 2.0f, 1.0f });
	addPoint({ 0.0f, 2.0f, 0.0f });

	m_CamRotQuat->push_back(glm::quat(glm::vec3(glm::radians(10.0f), 0.0f, glm::radians(10.0f))));
	m_CamRotQuat->push_back(glm::quat(glm::vec3(glm::radians(20.0f), 0.0f, glm::radians(100.0f))));
	m_CamRotQuat->push_back(glm::quat(glm::vec3(glm::radians(30.0f), 0.0f, glm::radians(190.0f))));
	m_CamRotQuat->push_back(glm::quat(glm::vec3(glm::radians(40.0f), 0.0f, glm::radians(280.0f))));

	/*
	addPoint({ 0.0f, 2.0f, 4.0f });
	addPoint({ 0.5f, 2.5f, 3.0f });
	addPoint({ 0.0f, 3.0f, 2.0f });
	addPoint({ -0.5f, 3.5f, 1.0f });
	addPoint({ 0.0f, 4.0f, 0.0f });
	addPoint({ 0.5f, 4.5f, -1.0f });
	addPoint({ 0.0f, 5.0f, -2.0f });
	addPoint({ -0.5f, 5.5f, -3.0f });
	addPoint({ 0.0f, 6.0f, -4.0f });
	addPoint({ 0.5f, 6.5f, -5.0f });
	addPoint({ 0.0f, 7.0f, -6.0f });

	addPoint({ 2.5f, 6.0f, -2.5f });
	addPoint({ 5.0f, 5.0f, -1.0f });
	addPoint({ 5.0f, 6.0f, -0.0f });
	addPoint({ 5.0f, 5.0f, 1.0f });
	addPoint({ 5.0f, 6.0f, 2.0f });
	addPoint({ 5.0f, 5.0f, 3.0f });
	addPoint({ 5.0f, 6.0f, 4.0f });
	addPoint({ 5.0f, 5.0f, 5.0f });
	addPoint({ 5.0f, 6.0f, 6.0f });

	m_CamRot->push_back(glm::vec3(0.0f, 0.0f, 5.0f));
	m_CamRotQuat->push_back(glm::quat(glm::vec3(0.0f, 0.0f, 0.0f)));

	m_CamRot->push_back(glm::vec3(0.0f, 0.0f, 3.0f));
	m_CamRotQuat->push_back(glm::quat(glm::vec3(0.0f, 0.5f, 0.0f)));

	m_CamRot->push_back(glm::vec3(-2.0f, -2.0f, 3.0f));
	m_CamRotQuat->push_back(glm::quat(glm::vec3(0.5f, 0.2f, 0.0f)));

	m_CamRot->push_back(glm::vec3(-3.0f, -2.0f, 0.0f));
	m_CamRotQuat->push_back(glm::quat(glm::vec3(1.0f, -0.9f, 0.0f)));

	m_CamRot->push_back(glm::vec3(-2.0f, -1.0f, -3.0f));
	m_CamRotQuat->push_back(glm::quat(glm::vec3(0.5f, -2.3f, 0.0f)));

	m_CamRot->push_back(glm::vec3(0.0f, 0.0f, -5.0f));
	m_CamRotQuat->push_back(glm::quat(glm::vec3(0.0f, -0.9f, 0.0f)));

	m_CamRot->push_back(glm::vec3(1.0f, 0.0f, -7.0f));
	m_CamRotQuat->push_back(glm::quat(glm::vec3(0.0f, -0.5f, 0.0f)));

	m_CamRot->push_back(glm::vec3(0.0f, 0.0f, -9.0f));
	m_CamRotQuat->push_back(glm::quat(glm::vec3(0.0f, 0.1f, 0.0f)));

	m_CamRot->push_back(glm::vec3(0.0f, 0.0f, -10.5f));
	m_CamRotQuat->push_back(glm::quat(glm::vec3(0.0f, 0.0f, 0.0f)));

	m_CamRot->push_back(glm::vec3(0.0f, 0.0f, -12.0f));
	m_CamRotQuat->push_back(glm::quat(glm::vec3(0.0f, 0.0f, 0.0f)));

	m_CamRot->push_back(glm::vec3(0.0f, 0.0f, -13.5f));
	m_CamRotQuat->push_back(glm::quat(glm::vec3(0.0f, 0.0f, 0.0f)));

	m_CamRot->push_back(glm::vec3(0.0f, 0.0f, -15.0f));
	m_CamRotQuat->push_back(glm::quat(glm::vec3(0.0f, 0.0f, 0.0f)));

	m_CamRot->push_back(glm::vec3(0.0f, 0.0f, -16.5f));
	m_CamRotQuat->push_back(glm::quat(glm::vec3(0.0f, 0.0f, 0.0f)));

	m_CamRot->push_back(glm::vec3(0.0f, 0.0f, -18.0f));
	m_CamRotQuat->push_back(glm::quat(glm::vec3(0.0f, -0.05f, 0.0f)));

	m_CamRot->push_back(glm::vec3(1.0f, 0.0f, -19.0f));
	m_CamRotQuat->push_back(glm::quat(glm::vec3(0.0f, 0.5f, 0.0f)));

	m_CamRot->push_back(glm::vec3(2.0f, 0.0f, -20.0f));
	m_CamRotQuat->push_back(glm::quat(glm::vec3(0.0f, 1.0f, 0.0f)));

	m_CamRot->push_back(glm::vec3(2.0f, 0.0f, -21.0f));
	m_CamRotQuat->push_back(glm::quat(glm::vec3(0.0f, 1.0f, 0.0f)));

	m_CamRot->push_back(glm::vec3(2.0f, 0.0f, -22.0f));
	m_CamRotQuat->push_back(glm::quat(glm::vec3(0.0f, 1.1f, 0.0f)));

	m_CamRot->push_back(glm::vec3(2.0f, 0.0f, -23.0f));
	m_CamRotQuat->push_back(glm::quat(glm::vec3(0.0f, 1.2f, 0.0f)));

	m_CamRot->push_back(glm::vec3(2.0f, 0.0f, -24.0f));
	m_CamRotQuat->push_back(glm::quat(glm::vec3(0.0f, 1.3f, 0.0f)));
	*/

	recalcSpline();
}

Spline::~Spline()
{
	m_ControlPoints->clear();
	delete m_ControlPoints;

	m_SplinePoints->clear();
	delete m_SplinePoints;

	m_CamRot->clear();
	delete m_CamRot;

	m_CamRotQuat->clear();
	delete m_CamRotQuat;
}

void Spline::setRendered(bool b)
{
	//TODO
}

void Spline::addPoint(float x, float y, float z)
{
	addPoint({ x,y,z });
}

void Spline::addPoint(Point p) {
	addPoint(p, { 0.0f,0.0f,0.0f });
}

void Spline::addPoint(Point p, Vector3f r)
{
	/*TODO Debug
	if (m_ControlPoints->size() < 1) {
		m_SplinePoints->push_back(p);
	}
	else {
		Point p0 = p;
		Point p1 = p;
		if (m_ControlPoints->size() == 1) {
			p0 = *(m_ControlPoints->end() - 1);
			p1 = p0;
		}
		else {
			p0 = *(m_ControlPoints->end() - 2);
			p1 = *(m_ControlPoints->end() - 1);
		}
			std::vector<Point> splineSeg = calcSplineSeg(p0, p1, p, p);
			m_SplinePoints->insert(m_SplinePoints->end(), splineSeg.begin(), splineSeg.end());
	}
	*/

	m_ControlPoints->push_back(p);
	cout << "Points " << m_ControlPoints->size() << "\n";

	m_CamRotQuat->push_back(glm::quat(glm::vec3(r.x, r.y, r.z)));

	//TODO Remove
	recalcSpline();

}

void Spline::clearPoints()
{
	m_ControlPoints->clear();
	m_SplinePoints->clear();
}

void Spline::recalcSpline()
{
	m_SplinePoints->clear();

	//cout << "Control points:\n";
	//printPoints(m_ControlPoints);

	if (m_ControlPoints->size() < 2) {
		m_SplinePoints->insert(m_SplinePoints->end(), m_ControlPoints->begin(), m_ControlPoints->end());
	}
	else {

		//Add first contol point
		m_SplinePoints->push_back(*(m_ControlPoints->begin()));

		for (int index = -1; index <= (int(m_ControlPoints->size()) - 3); index++) {

			Point p0 = *m_ControlPoints->begin();

			if (index > 0) {
				p0 = m_ControlPoints->at(index);
			}

			Point p1 = m_ControlPoints->at(index + 1);
			Point p2 = m_ControlPoints->at(index + 2);

			Point p3 = *(m_ControlPoints->end() - 1);

			if ((index + 3) < m_ControlPoints->size()) {
				p3 = m_ControlPoints->at(index + 3);
			}

			std::vector<Point> splineSeg = calcSplineSeg(p0, p1, p2, p3);

			m_SplinePoints->insert(m_SplinePoints->end(), splineSeg.begin(), splineSeg.end());

		}
	}

	//cout << "Spline points:\n";
	//printPoints(m_SplinePoints);
}

Point Spline::getStart()
{
	return *(m_SplinePoints->begin());
}

Point Spline::getEnd()
{
	return *(m_SplinePoints->end());
}

Point Spline::getByIndex(int index)
{
	return m_SplinePoints->at(index);
}

Point Spline::getByTime(float time)
{
	int index = time;
	float t = time - float(index);

	//cout << "t: " << time << "\n";

	if (index >= m_ControlPoints->size()) {
		index = m_ControlPoints->size() - 1;
		t = 1;
	}

	Point p0 = m_ControlPoints->at(0);

	if (index > 0) {
		p0 = m_ControlPoints->at(index - 1);
	}

	Point p1 = m_ControlPoints->at(index);

	Point p2 = *(m_ControlPoints->end() - 1);
	if ((index + 1) < m_ControlPoints->size()) {
		p2 = m_ControlPoints->at(index + 1);
	}

	Point p3 = *(m_ControlPoints->end() - 1);
	if ((index + 2) < m_ControlPoints->size()) {
		p3 = m_ControlPoints->at(index + 2);
	}

	float distance = Vector3f(p1).distance(p2);

	return calcSplinePoint(p0, p1, p2, p3, t);
}

int Spline::getPointCount()
{
	return m_SplinePoints->size();
}

float Spline::getLineLength()
{
	float sum = 0.0f;
	for (int i = 0; i < (m_SplinePoints->size() - 1); i++) {
		sum += Vector3f(m_SplinePoints->at(i)).distance(m_SplinePoints->at(i + 1));
	}
	return sum;
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

bool Spline::toggleSplineRender()
{
	m_Spline = !m_Spline;

	return m_Spline;
}

Point Spline::calcSplinePoint(Point p0, Point p1, Point p2, Point p3, float t)
{
	Vector3f v0 = p0;
	Vector3f v1 = p1;
	Vector3f v2 = p2;
	Vector3f v3 = p3;

	Vector3f pointT = 0.5f * ((2 * v1) + (-v0 + v2) * (t)+(2 * v0 - 5 * v1 + 4 * v2 - v3) * pow(t, 2) + (-v0 + 3 * v1 - 3 * v2 + v3) * pow(t, 3));

	return { pointT.x, pointT.y, pointT.z };
}

void Spline::createMesh()
{
	glColor4f(m_Color.red, m_Color.green, m_Color.blue, m_Color.alpha);
	glLineWidth(m_LineWidth);

	glPushMatrix();
	glBegin(GL_LINE_STRIP);

	std::vector<Point>::iterator splPoint;
	if (m_Spline) {
		for (splPoint = m_SplinePoints->begin(); splPoint != m_SplinePoints->end(); ++splPoint) {
			glVertex3f(splPoint->x, splPoint->y, splPoint->z);
		}
	}
	else {
		for (splPoint = m_ControlPoints->begin(); splPoint != m_ControlPoints->end(); ++splPoint) {
			glVertex3f(splPoint->x, splPoint->y, splPoint->z);
		}
	}

	glEnd();
	glPopMatrix();

	glLineWidth(1.0f);
}

std::vector<Point> Spline::calcSplineSeg(Point p0, Point p1, Point p2, Point p3)
{
	std::vector<Point> splineSeg;

	Vector3f v1 = p1;
	Vector3f v2 = p2;

	int steps = m_ResolutionSteps * v1.distance(v2);

	for (int step = 1; step <= steps; step++) {
		float t = float(step) / float(steps);
		Point pointT = calcSplinePoint(p0, p1, p2, p3, t);

		splineSeg.push_back(pointT);
	}

	return splineSeg;
}

void Spline::printPoints(std::vector<Point>* vec)
{
	for (int index = 0; index < vec->size(); index++) {
		cout << "[" << vec->at(index).x << "," << vec->at(index).y << "," << vec->at(index).z << "]\n";
	}
}

glm::quat Spline::getCameraRotationAtTime(float time) {
	int index = time;
	float t = time - float(index);

	//cout << "t: " << time << "\n";

	if (index >= m_ControlPoints->size()) {
		index = m_ControlPoints->size() - 1;
		t = 1;
	}

	glm::quat q0 = m_CamRotQuat->at(0);

	if (index > 0) {
		q0 = m_CamRotQuat->at(index - 1);
	}

	glm::quat q1 = m_CamRotQuat->at(index);

	glm::quat q2 = *(m_CamRotQuat->end() - 1);
	if ((index + 1) < m_CamRotQuat->size()) {
		q2 = m_CamRotQuat->at(index + 1);
	}

	glm::quat q3 = *(m_CamRotQuat->end() - 1);
	if ((index + 2) < m_CamRotQuat->size()) {
		q3 = m_CamRotQuat->at(index + 2);
	}

	//float distance = Vector3f(p1).distance(p2);

	//float ratio = (cameraDistanceTravelled - distanceToPoint[i - 1]) / (distanceToPoint[i] - distanceToPoint[i - 1]);


	return squad(q0, q1, q2, q3, t);
	//return glm::slerp(q1, q2, t);
}

glm::quat Spline::squad(glm::quat q0, glm::quat q1, glm::quat q2, glm::quat q3, float t)
{
	glm::quat conj = glm::conjugate(q1);
	glm::quat a = q1 * glm::exp(-(glm::log(conj * q2) + glm::log(conj * q0)) * 0.25f);
	conj = glm::conjugate(q2);
	glm::quat b = q2 * glm::exp(-(glm::log(conj * q3) + glm::log(conj * q1)) * 0.25f);

	return slerp(slerp(q1, q2, t), slerp(a, b, t), 2 * t * (1 - t));
}
