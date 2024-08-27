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
	double c = qbVector<double>::dot(castRay.m_Point1, vhat) - 1.0;

	// Test we have a intersection
	double interTest = (b * b) - 4.0 * c;

	if (interTest > 0.0)
		return true;
	else
		return false;
	
} // testIntersections