#include "PointLight.hpp"

LRT::PointLight::PointLight() {
	m_Color = qbVector<double>{ std::vector<double> {1.0, 1.0, 1.0} };
	m_Intensity = 1.0;

} // PointLight

LRT::PointLight::~PointLight() {} // ~PointLight

bool LRT::PointLight::computeIllumination(const qbVector<double>& intersectionPoint, const qbVector<double>& localNormal, const std::vector<std::shared_ptr<LRT::ObjectBase>>& objectList, const std::shared_ptr<LRT::ObjectBase>& currentObject, qbVector<double>& color, double intensity) {
	
	// Construct a vector pointing from the intersection point to the light
	qbVector<double> lightDirection = (m_Location - intersectionPoint).Normalized();

	// compute starting point
	qbVector<double> startPoint = intersectionPoint; // this currently makes no sense but later it will make sense

	// Compute the angle between the local normal and the light ray
	// assume local normal is a unit vector
	double angle = acos(qbVector<double>::dot(localNormal, lightDirection));  
	
	// Construct a ray from the point of intersection to the light
	LRT::Ray lightRay(startPoint, startPoint + lightDirection);

	// check for intersections with all of our objects in our scene except for the current object
	qbVector<double> pointOfIntersection{ 3 };
	qbVector<double> poiNormal{ 3 }; // poi: pointOfIntersection
	qbVector<double> poiColor{ 3 };
	bool validIntersection = false;
	for (auto sceneObject : objectList) {
		if (sceneObject != currentObject) 
			validIntersection = sceneObject->testIntersections(lightRay, pointOfIntersection, poiNormal, poiColor);

		// if we have a intersection, then no need to check further, we can break the loop
		// this object is blocking light from this source
		if (validIntersection)
			break;

	} // for (auto sceneObject : objectList)

	/*  only continue to compute illumination if the light ray didn't
		intersect with any object in the scene. IE. no objects are
		casting a shadow */
	if (!validIntersection) {
		// Compute the angle between the local normal and the light ray
		// note: assume localNormal is a unit vector
		double angle = acos(qbVector<double>::dot(localNormal, lightDirection));

		// if the normal is pointing away from the light, then we have no illumination
		if (angle > 1.5708) {
			// no illumination
			color = m_Color;
			intensity = 0;
			return false;

		} //(angle > 1.5708)
		else {
			// we do have illumination 
			color = m_Color;
			intensity = m_Intensity * (1.0 - (angle / 1.5708));
			return true;

		} // else

	} // (!validIntersection)
	else {
		// Shadow, so no illumination
		color = m_Color;
		intensity = 0;
		return false;

	} // else 

} // computeIllumination