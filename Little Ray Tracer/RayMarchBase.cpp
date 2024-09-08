#include "RayMarchBase.hpp"

LRT::RM::RayMarchBase::RayMarchBase() {
	// define the tolerance
	m_Epsilon = 1e-3;
	// define the maximum amount of steps allowed
	m_MaxSteps = 100;

} // RayMarchBase

LRT::RM::RayMarchBase::~RayMarchBase() {} // ~RayMarchBase

bool LRT::RM::RayMarchBase::testIntersections(const Ray& castRay, qbVector<double>& intersectionPoint, qbVector<double>& localNormal, qbVector<double>& localColor) {
	
	if (m_HaveObjectFcn) {
		
		// Check if the object is visible
		if (!m_isVisible) 
			return false;

		// Copy the ray and apply the backwards transition
		LRT::Ray backRay = m_TransformMatrix.Apply(castRay, LRT::BCKTFORM);

		// test for intersecting with the bounding box
		qbVector<double> boundPOI   { 3 };
		qbVector<double> boundNormal{ 3 };
		qbVector<double> boundColor { 3 }; 

		if (m_BoundingBox.testIntersections(backRay, boundPOI, boundNormal, boundColor)) {

			// Extract ray direction
			qbVector<double> vhat = backRay.m_lineAB;
			vhat.Normalize();

			qbVector<double> currentLoc = backRay.m_Point1;
			int stepCount = 0;
			double dist = evaluateSDF(&currentLoc, &m_Params);

			// Main loop
			while ((dist > m_Epsilon) && (stepCount < m_MaxSteps)) {
				currentLoc = currentLoc + (vhat * dist);
				dist = evaluateSDF(&currentLoc, &m_Params);

				if(dist > 1e6) {
					stepCount = m_MaxSteps; 
					break;

				} // if(dist > 1e6)
				
				stepCount++; 

			} // while ((dist > m_Epsilon) && (stepCount < m_MaxSteps))

			// if maxSteps exceeded, then no valid intersection found
			if (stepCount == m_MaxSteps)
				return false;

			// otherwise we have a valid intersection at current location
			// transform the intersection point back into world coordinates
			intersectionPoint = m_TransformMatrix.Apply(currentLoc, LRT::FWDTFORM);

			// compute the local normal
			qbVector<double> surfaceNormal{ 3 };

			// we are simply evaluting the numerical gradient of the SDF at these points
			// the gradient in this case is a vector that is perpendicular to the SDF at that point
			qbVector<double> x_1 = currentLoc - m_xDisp;
			qbVector<double> x_2 = currentLoc + m_xDisp;

			qbVector<double> y_1 = currentLoc - m_yDisp;
			qbVector<double> y_2 = currentLoc + m_yDisp;

			qbVector<double> z_1 = currentLoc - m_zDisp;
			qbVector<double> z_2 = currentLoc + m_zDisp;

			surfaceNormal.SetElement(0, evaluateSDF(&x_2, &m_Params)  -  evaluateSDF(&x_1, &m_Params));
			surfaceNormal.SetElement(1, evaluateSDF(&y_2, &m_Params)  -  evaluateSDF(&y_1, &m_Params));
			surfaceNormal.SetElement(2, evaluateSDF(&z_2, &m_Params)  -  evaluateSDF(&z_1, &m_Params));

			// Transform the local normal
			surfaceNormal.Normalize();
			localNormal = m_TransformMatrix.ApplyNormal(surfaceNormal); 
			localNormal.Normalize();

			// return the base color
			localColor = m_BaseColor; 

			return true;

		} // (m_BoundingBox.testIntersections(backRay, boundPOI, boundNormal, boundColor))

	} // if (m_HaveObjectFcn)

	return false;

} // testIntersections

void LRT::RM::RayMarchBase::setObjectFunction(std::function<double(qbVector<double>*, qbVector<double>*)> objectFunction) {
	m_ObjectFunction = objectFunction; 
	m_HaveObjectFcn = true;

} // setObjectFunction

double LRT::RM::RayMarchBase::evaluateSDF(qbVector<double>* location, qbVector<double>* params) {
	return m_ObjectFunction(location, params);

} // evaluateSDF