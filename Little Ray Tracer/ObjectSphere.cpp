#include "ObjectSphere.hpp"

// std
#include <cmath>

LRT::ObjectSphere::ObjectSphere() {} // ObjectSphere
LRT::ObjectSphere::~ObjectSphere() {} // ~ObjectSphere

bool LRT::ObjectSphere::testIntersections(const LRT::Ray& castRay, qbVector<double>& intersectionPoint, qbVector<double>& localNormal, 
qbVector<double>& localColor) {
	// Compute the values of a, b, and c
	qbVector<double> vhat = castRay.m_lineAB;
	vhat.Normalize();

	// Note that "a" is equal to squared magnitude of the direction of the cast ray, as this will be a unit vector
	// we can conclude that "a" will be always a value of 1
	
	// Calculate b
	double b = 2.0 * qbVector<double>::dot(castRay.m_Point1, vhat);
	// Calculate c
	double c = qbVector<double>::dot(castRay.m_Point1, castRay.m_Point1) - 1.0;

	// Test we have a intersection
	double interTest = (b * b) - 4.0 * c;

	if (interTest > 0.0) {
		double numSqrt = sqrtf(interTest);
		double t1 = (-b + numSqrt) / 2.0;
		double t2 = (-b - numSqrt) / 2.0;

		// if either t1 or t2 is negative, then at least part of the object is behind the camera and we will not render it
		// it will be discarded
		if (t1 < 0 || t2 < 0)
			return false;

		else {
			// determine which point of intersection was closest to the camera
			if (t1 < t2) 
				intersectionPoint = castRay.m_Point1 + (vhat * t1);
			else 
				intersectionPoint = castRay.m_Point1 + (vhat * t2);

		 } // else

		return true;

	} // if
	else
		return false;
	
} // testIntersections