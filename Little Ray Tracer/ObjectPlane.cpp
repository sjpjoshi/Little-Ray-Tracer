#include "ObjectPlane.hpp"
#include <cmath>

LRT::ObjectPlane::ObjectPlane() {} // ObjectPlane
LRT::ObjectPlane::~ObjectPlane() {} // ~ObjectPlane

bool LRT::ObjectPlane::testIntersections(const LRT::Ray& castRay, qbVector<double>& intersectionPoint, qbVector<double>& localNormal, qbVector<double>& localColor) {
	if (!m_isVisible)
		return false;

	// Copy the ray and apply the backwards transform 
	LRT::Ray backRay = m_TransformMatrix.Apply(castRay, LRT::BCKTFORM);

	//Cop the lineAB vector from the castRay and nomarlize it
	qbVector<double> khat = backRay.m_lineAB;
	khat.Normalize();

	// check if there is a interection, if the cast ray is not parallel to the plane
	if (!approxEqual(khat.GetElement(2), 0.0)) {

		// there is a intersection
		double t = backRay.m_Point1.GetElement(2) / -khat.GetElement(2);

		// if t is negative, then the intersection point must be behind the camera
		// so we can ignore it
		if (t > 0.0) {

			// assume planes are not infinite, in fact infinte planes are not useful
			// Compute the values for u and v
			double u = backRay.m_Point1.GetElement(0) + (khat.GetElement(0) * t);
			double v = backRay.m_Point1.GetElement(1) + (khat.GetElement(1) * t);

			// if the magnitude of both u and v is <= 1, then we must be in the plane
			if (abs(u) < 1.0 && abs(v) < 1.0) {

				// compute the point of intersection
				qbVector<double> pointOfIntersection = backRay.m_Point1 + t * khat;
				// Transform the intersection point back into the world coord
				intersectionPoint = m_TransformMatrix.Apply(pointOfIntersection, LRT::FWDTFORM);

				// Compute the local normal
				qbVector<double> normalVector{ std::vector<double> {0.0, 0.0, -1.0} };
				localNormal = m_TransformMatrix.ApplyNormal(normalVector); 
				localNormal.Normalize();

				// return the base color
				localColor = m_BaseColor;

				// store the UV coords for possible later use
				m_UVCoords.SetElement(0, u);
				m_UVCoords.SetElement(1, v);

				return true;

			} // if (abs(u) < 1.0 && abs(v) < 1.0)
			else
				return false;

		} // if (t > 0.0)
		else
			return false;

	} // if  (!approxEqual(khat.GetElement(2), 0.0))
	else
		return false;

	return false;

} // testIntersections