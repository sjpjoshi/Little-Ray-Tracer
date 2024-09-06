#include "Box.hpp"

// std
#include <cmath>

LRT::Box::Box() {} // Box
LRT::Box::~Box() {} // ~Box

bool LRT::Box::testIntersections(const Ray& castRay, qbVector<double>& intersectionPoint, qbVector<double>& localNormal, qbVector<double>& localColor) {
	if(!m_isVisible)
		return false;

	// Copy the ray and apply the backwards transform.
	LRT::Ray bckRay = m_TransformMatrix.Apply(castRay, LRT::BCKTFORM);

	// Extract values of a.
	double ax = bckRay.m_Point1.GetElement(0);
	double ay = bckRay.m_Point1.GetElement(1); 
	double az = bckRay.m_Point1.GetElement(2); 

	// Extract the value of k.
	qbVector<double> k = bckRay.m_lineAB;
	k.Normalize();
	double kx = k.GetElement(0);
	double ky = k.GetElement(1);
	double kz = k.GetElement(2);

	// Test for intersections with each plane (side of the box).
	// Top and bottom.
	if (!approxEqual(kz, 0.0)) {
		t[0] = (az - 1.0) / -kz;
		t[1] = (az + 1.0) / -kz;
		u[0] = ax + kx * t[0];
		v[0] = ay + ky * t[0];
		u[1] = ax + kx * t[1];
		v[1] = ay + ky * t[1];

	} // if
	else {
		t[0] = 100e6;
		t[1] = 100e6;
		u[0] = 0.0;
		v[0] = 0.0;
		u[1] = 0.0;
		v[1] = 0.0;

	} // else

	// Left and right.
	if (!approxEqual(kx, 0.0)) {
		t[2] = (ax + 1.0) / -kx;
		t[3] = (ax - 1.0) / -kx;
		u[2] = az + kz * t[2];
		v[2] = ay + ky * t[2];
		u[3] = az + kz * t[3];
		v[3] = ay + ky * t[3];

	} // if
	else {
		t[2] = 100e6;
		t[3] = 100e6;
		u[2] = 0.0;
		v[2] = 0.0;
		u[3] = 0.0;
		v[3] = 0.0;

	} // else

	// Front and back.
	if (!approxEqual(ky, 0.0)) {
		t[4] = (ay + 1.0) / -ky;
		t[5] = (ay - 1.0) / -ky;
		u[4] = ax + kx * t[4];
		v[4] = az + kz * t[4];
		u[5] = ax + kx * t[5];
		v[5] = az + kz * t[5];

	} // if
	else {
		t[4] = 100e6;
		t[5] = 100e6;
		u[4] = 0.0;
		v[4] = 0.0;
		u[5] = 0.0;
		v[5] = 0.0;

	} // else

	// Find the index of the smallest non-negative value of t.
	double finalU = 0.0;
	double finalV = 0.0;
	double finalT = 100e6;
	int finalIndex = 0;
	bool validIntersection = false;
	for (int i = 0; i < 6; ++i) {
		if ((t[i] < finalT) && (t[i] > 0.0) && (abs(u[i]) <= 1.0) && (abs(v[i]) <= 1.0)) {
			finalT = t[i];
			finalIndex = i;
			finalU = u[i];
			finalV = v[i];
			validIntersection = true;

		} // if

	} // for

	if (validIntersection) {
		// Compute the point of intersection.
		qbVector<double> poi = bckRay.m_Point1 + finalT * k;
		qbVector<double> normalVector{ 3 };

		switch (finalIndex) {
		case 0:
			normalVector = std::vector<double>{ 0.0, 0.0, 1.0 }; // Down.
			break;

		case 1:
			normalVector = std::vector<double>{ 0.0, 0.0, -1.0 }; // Up.
			break;

		case 2:
			normalVector = std::vector<double>{ -1.0, 0.0, 0.0 }; // Left.
			break;

		case 3:
			normalVector = std::vector<double>{ 1.0, 0.0, 0.0 }; // Right.
			break;

		case 4:
			normalVector = std::vector<double>{ 0.0, -1.0, 0.0 }; // Backwards (towards the camera).
			break;

		case 5:
			normalVector = std::vector<double>{ 0.0, 1.0, 0.0 }; // Forwards (away from the camera).
			break;

		} // Switch

		// Transform the intersection point back into world coordinates
		intersectionPoint = m_TransformMatrix.Apply(poi, LRT::FWDTFORM);

		// transform the normal vector
		localNormal = m_TransformMatrix.ApplyNormal(normalVector);
		localNormal.Normalize();

		// return the base color
		localColor = m_BaseColor;

		// store uv coord for later use
		m_UVCoords.SetElement(0, finalU);
		m_UVCoords.SetElement(0, finalV);

		return true;

	} // if
	else 
		return false;

} // testIntersections