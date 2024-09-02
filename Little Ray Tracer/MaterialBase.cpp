#include "MaterialBase.hpp"

LRT::MaterialBase::MaterialBase()  {
	m_MaxReflectionRays = 3;
	m_ReflectionRayCount = 0;

} // MaterialBase

LRT::MaterialBase::~MaterialBase() {} // ~MaterialBase

qbVector<double> LRT::MaterialBase::ComputeColor(const std::vector<std::shared_ptr<LRT::ObjectBase>>& objectList, const std::vector<std::shared_ptr<LRT::LightBase>>& lightList, const std::shared_ptr<LRT::ObjectBase>& currentObject, const qbVector<double>& intPoint, const qbVector<double>& localNormal, const LRT::Ray& cameraRay) {
	// Define an initial material color
	qbVector<double> matColor{ 3 };
	return matColor;

} // ComputeColor

qbVector<double> LRT::MaterialBase::computeDiffuseColor(const std::vector<std::shared_ptr<LRT::ObjectBase>>& objectList, const std::vector<std::shared_ptr<LRT::LightBase>>& lightList, const std::shared_ptr<LRT::ObjectBase>& currentObject, const qbVector<double>& intPoint, const qbVector<double>& localNormal, const qbVector<double>& baseColor) {
	// Compute the color due to diffuse illumination.
	qbVector<double> diffuseColor{ 3 };
	double intensity = 100;
	qbVector<double> color{ 3 };
	double red = 0.0;
	double green = 0.0;
	double blue = 0.0;
	bool validIllum = false;
	bool illumFound = false;
	for (auto currentLight : lightList)
	{
		validIllum = currentLight->computeIllumination(intPoint, localNormal, objectList, currentObject, color, intensity);
		if (validIllum)
		{
			illumFound = true;
			red += color.GetElement(0) * intensity;
			green += color.GetElement(1) * intensity;
			blue += color.GetElement(2) * intensity;
		}
	}

	if (illumFound)
	{
		diffuseColor.SetElement(0, red * baseColor.GetElement(0));
		diffuseColor.SetElement(1, green * baseColor.GetElement(1));
		diffuseColor.SetElement(2, blue * baseColor.GetElement(2));
	}

	// Return the material color.
	return diffuseColor;


} // computeDiffuseColor

// Function to cast a ray into the scene.
bool LRT::MaterialBase::CastRay(const LRT::Ray& castRay, const std::vector<std::shared_ptr<LRT::ObjectBase>>& objectList, const std::shared_ptr<LRT::ObjectBase>& thisObject, std::shared_ptr<LRT::ObjectBase>& closestObject, qbVector<double>& closestIntPoint, qbVector<double>& closestLocalNormal, qbVector<double>& closestLocalColor) {
	// Test for intersections with all of the objects in the scene.
	qbVector<double> intPoint{ 3 };
	qbVector<double> localNormal{ 3 };
	qbVector<double> localColor{ 3 };

	double minDist = 1e6;
	bool intersectionFound = false;
	for (auto currentObject : objectList) {
		if (currentObject != thisObject) {
			bool validInt = currentObject->testIntersections(castRay, intPoint, localNormal, localColor);

			// If we have a valid intersection.
			if (validInt) {
				// Set the flag to show that we found an intersection.
				intersectionFound = true;

				// Compute the distance between the source and the intersection point.
				double dist = (intPoint - castRay.m_Point1).norm();

				// Store a reference to this object if it is the closest.
				if (dist < minDist) {
					minDist = dist;
					closestObject = currentObject;
					closestIntPoint = intPoint;
					closestLocalNormal = localNormal;
					closestLocalColor = localColor;

				} // if (dist < minDist)

			} // if (validInt)

		} // 	if (currentObject != thisObject)

	} // for (auto currentObject : objectList)

	return intersectionFound;
} // CastRay

qbVector<double> LRT::MaterialBase::computeReflectionColor(const std::vector<std::shared_ptr<LRT::ObjectBase>>& objectList, const std::vector<std::shared_ptr<LRT::LightBase>>& lightList, const std::shared_ptr<LRT::ObjectBase>& currentObject, const qbVector<double>& intPoint, const qbVector<double>& localNormal, const LRT::Ray& incidentRay) {
	qbVector<double> reflectionColor{ 3 };
	//Compute the reflection vector
	qbVector<double> d = incidentRay.m_lineAB;
	qbVector<double> reflectionVector = d - (2 * qbVector<double>::dot(d, localNormal) * localNormal); 
	// Construct the reflection ray
	LRT::Ray reflectionRay(intPoint, intPoint + reflectionVector);

	// Cast this ray into the scene and find the closest object that is intersects with
	std::shared_ptr<LRT::ObjectBase> closestObject;
	qbVector<double> closestIntPoint{ 3 };
	qbVector<double> closestLocalNormal{ 3 };
	qbVector<double> closestLocalColor{ 3 };

	bool intersectionFound = CastRay(reflectionRay, objectList, currentObject, closestObject, closestIntPoint, closestLocalNormal, closestLocalColor);
	// Compute the illumination for the closest object in the scene assuming there was a valid intersection
	qbVector<double> matColor{ 3 };
	if (intersectionFound && m_ReflectionRayCount < m_MaxReflectionRays) {
		// increment the reflection ray count
		m_ReflectionRayCount++;

		// check if a material has been assigned for this object
		if (closestObject->m_HasMaterial)
			// use the material to compute the color
			matColor = closestObject->m_pMaterial->ComputeColor(objectList, lightList, closestObject, closestIntPoint, closestLocalNormal, reflectionRay);

		else
			matColor = LRT::MaterialBase::computeDiffuseColor(objectList, lightList, closestObject, closestIntPoint, closestLocalColor, closestObject->m_BaseColor);

	} // if (intersectionFound && m_ReflectionRayCount < m_MaxReflectionRays)
	else {
		// leave the matColor as is

	} // else 

	reflectionColor = matColor;
	return reflectionColor;

} // computeReflectionColor