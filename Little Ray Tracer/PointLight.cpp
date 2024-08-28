#include "PointLight.hpp"

LRT::PointLight::PointLight() {
	m_Color = qbVector<double>{ std::vector<double> {1.0, 1.0, 1.0} };
	m_Intensity = 1.0;

} // PointLight

LRT::PointLight::~PointLight() {} // ~PointLight

bool LRT::PointLight::computeIllumination(const qbVector<double>& intersectionPoint, const qbVector<double>& localNormal, const std::vector<std::shared_ptr<LRT::ObjectBase>>& objectBase, const std::shared_ptr<LRT::ObjectBase>& currentObject, qbVector<double>& color, double intensity) {
	// Construct a vector pointing from the intersection point to the light
	qbVector<double> lightDirection = (m_Location - intersectionPoint).Normalized();
	// compute starting point
	qbVector<double> startPoint = intersectionPoint; // this currently makes no sense but later it will make sense
	// Compute the angle between the local normal and the light ray
	// assume local normal is a unit vector
	double angle = acos(qbVector<double>::dot(localNormal, lightDirection));  

	// if the normal is  pointing away from the light, then we have no illumintaion
	if (angle > 1.5708) {
		// no illumination
		color = m_Color;
		intensity = 0.0;
		return false;

	} // if
	else {
		// we do have illumination
		color = m_Color;
		intensity = m_Intensity * (1.0 - (angle / 1.5708) );
		return true;

	} // else

	return true;

} // computeIllumination