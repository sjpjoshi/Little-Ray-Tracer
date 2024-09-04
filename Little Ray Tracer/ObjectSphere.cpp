#include "ObjectSphere.hpp"

// std
#include <cmath>

// libs
#include <SDL2/SDL_stdinc.h>

LRT::ObjectSphere::ObjectSphere() {} // ObjectSphere
LRT::ObjectSphere::~ObjectSphere() {} // ~ObjectSphere

bool LRT::ObjectSphere::testIntersections(const LRT::Ray& castRay, qbVector<double>& intersectionPoint, qbVector<double>& localNormal, 
qbVector<double>& localColor)  {

	// copy the ray and apply the backwards transform
	LRT::Ray backRay = m_TransformMatrix.Apply(castRay, LRT::BCKTFORM);
	
	// Compute the values of a, b, and c
	qbVector<double> vhat = backRay.m_lineAB;
	vhat.Normalize();

	// Note that "a" is equal to squared magnitude of the direction of the cast ray, as this will be a unit vector
	// we can conclude that "a" will be always a value of 1
	
	// Calculate b
	double b = 2.0 * qbVector<double>::dot(backRay.m_Point1, vhat);
	// Calculate c
	double c = qbVector<double>::dot(backRay.m_Point1, backRay.m_Point1) - 1.0;

	// Test we have a intersection
	double interTest = (b * b) - 4.0 * c;

	qbVector<double> pointOfIntersection;

	if (interTest > 0.0) {
		double numSqrt = sqrtf(interTest);
		double t1 = (-b + numSqrt) / 2.0;
		double t2 = (-b - numSqrt) / 2.0;

		// if either t1 or t2 is negative, then at least part of the object is behind the camera and we will not render it
		// it will be discarded
		if ( (t1 < 0.0) || (t2 < 0.0) )
			return false;

		else {
			// determine which point of intersection was closest to the camera
			if (t1 < t2) 
				pointOfIntersection = backRay.m_Point1 + (vhat * t1); 
			else  
				pointOfIntersection = backRay.m_Point1 + (vhat * t2); 

			// pointOfIntersection gives us in the local coordinate system
			// Transform the intersection back into world Coords
			intersectionPoint = m_TransformMatrix.Apply(pointOfIntersection, LRT::FWDTFORM);

			// compute the local normal
			qbVector<double> objectOrigin = qbVector<double>(std::vector<double>{0.0, 0.0, 0.0});
			qbVector<double> newObjectOrigin = m_TransformMatrix.Apply(objectOrigin, LRT::FWDTFORM);
			localNormal = intersectionPoint - newObjectOrigin; 
			localNormal.Normalize();

			// return the base color
			localColor = m_BaseColor;

			// Compute and store uv coords for possible later use
			double x = pointOfIntersection.GetElement(0);
			double y = pointOfIntersection.GetElement(1);
			double z = pointOfIntersection.GetElement(2);
			double u = atan2(sqrt(pow(x, 2.0) + pow(y, 2.0)), z);
			double v = atan2(y , x);
			
			u /= M_PI;
			v /= M_PI;

			m_UVCoords.SetElement(0, u); 
			m_UVCoords.SetElement(1, v);

		 } // else

		return true;

	} // if (interTest > 0.0)
	else
		return false;
	
} // testIntersections