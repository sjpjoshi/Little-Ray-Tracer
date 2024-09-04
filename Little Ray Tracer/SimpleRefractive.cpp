#include "SimpleRefractive.hpp"

// std
#include <cmath>

LRT::SimpleRefractive::SimpleRefractive() {} // SimpleRefractive

LRT::SimpleRefractive::~SimpleRefractive(){} // ~SimpleRefractive

qbVector<double> LRT::SimpleRefractive::ComputeColor(const std::vector<std::shared_ptr<LRT::ObjectBase>>& objectList, const std::vector<std::shared_ptr<LRT::LightBase>>& lightList, const std::shared_ptr<LRT::ObjectBase>& currentObject, const qbVector<double>& intPoint, const qbVector<double>& localNormal, const LRT::Ray& cameraRay) {
	// Define the initial material colors
	qbVector<double> matColor { 3 }; 
	qbVector<double> refColor { 3 }; 
	qbVector<double> diffColor{ 3 };
	qbVector<double> spcColor { 3 }; 
	qbVector<double> trnColor { 3 }; // transluncent color

	// Compute the diffuse component
	if (!m_HasTexture)
		diffColor = computeDiffuseColor(objectList, lightList, currentObject, intPoint, localNormal, m_baseColor);
	else
		diffColor = computeDiffuseColor(objectList, lightList, currentObject, intPoint, localNormal, m_TextureList.at(0)->getColor(currentObject->m_UVCoords));

	// compute the reflection component
	if (m_reflectivity > 0.0) 
		refColor = computeReflectionColor(objectList, lightList, currentObject, intPoint, localNormal, cameraRay);
	
	// combine reflection and diffuse components
	matColor = (refColor * m_reflectivity) + (diffColor * (1 - m_reflectivity));

	// Compute the refractive component
	if (m_translucency > 0.0) 
		trnColor = computeTransluency(objectList, lightList, currentObject, intPoint, localNormal, cameraRay);

	matColor = (trnColor * m_translucency) + (matColor * (1.0 - m_translucency));

	// Compute the specular Component
	if (m_shininess > 0) 
		spcColor = computeSpecular(objectList, lightList, intPoint, localNormal, cameraRay); 

	// add the specular component to final color
	matColor = matColor + spcColor; 
	return matColor; 

} // ComputeColor

qbVector<double> LRT::SimpleRefractive::computeSpecular(const std::vector<std::shared_ptr<LRT::ObjectBase>>& objectList, const std::vector<std::shared_ptr<LRT::LightBase>>& lightList, const qbVector<double>& intPoint, const qbVector<double>& localNormal, const LRT::Ray& cameraRay) {
	qbVector<double> spcColor{ 3 };
	double red = 0.0;
	double green = 0.0;
	double blue = 0.0;

	// Loop through all of the lights in the scene.
	for (auto currentLight : lightList) {
		/* Check for intersections with all objects in the scene. */
		double intensity = 0.0;

		// Construct a vector pointing from the intersection point to the light.
		qbVector<double> lightDir = (currentLight->m_Location - intPoint).Normalized();

		// Compute a start point.
		qbVector<double> startPoint = intPoint + (lightDir * 0.001);

		// Construct a ray from the point of intersection to the light.
		LRT::Ray lightRay(startPoint, startPoint + lightDir);

		/* Loop through all objects in the scene to check if any
			obstruct light from this source. */
		qbVector<double> poi{ 3 };
		qbVector<double> poiNormal{ 3 };
		qbVector<double> poiColor{ 3 };
		bool validInt = false;
		for (auto sceneObject : objectList) {
			validInt = sceneObject->testIntersections(lightRay, poi, poiNormal, poiColor);
			if (validInt)
				break;

		} //for (auto sceneObject : objectList)

		/* If no intersections were found, then proceed with
			computing the specular component. */
		if (!validInt) {
			// Compute the reflection vector.
			qbVector<double> d = lightRay.m_lineAB;
			qbVector<double> r = d - (2 * qbVector<double>::dot(d, localNormal) * localNormal);
			r.Normalize();

			// Compute the dot product.
			qbVector<double> v = cameraRay.m_lineAB;
			v.Normalize();
			double dotProduct = qbVector<double>::dot(r, v);

			// Only proceed if the dot product is positive.
			if (dotProduct > 0.0)
				intensity = m_reflectivity * std::pow(dotProduct, m_shininess);

		} // if (!validInt)

		red += currentLight->m_Color.GetElement(0) * intensity;
		green += currentLight->m_Color.GetElement(1) * intensity;
		blue += currentLight->m_Color.GetElement(2) * intensity;
	
	} // for (auto currentLight : lightList)

	spcColor.SetElement(0, red);
	spcColor.SetElement(1, green);
	spcColor.SetElement(2, blue);
	return spcColor;

} // computeSpecular

qbVector<double> LRT::SimpleRefractive::computeTransluency(const std::vector<std::shared_ptr<LRT::ObjectBase>>& objectList, const std::vector<std::shared_ptr<LRT::LightBase>>& lightList, const std::shared_ptr<LRT::ObjectBase>& currentObject, const qbVector<double>& intPoint, const qbVector<double>& localNormal, const LRT::Ray& incidentRay) {
	qbVector<double> trnColor{ 3 }; // transluncent color
	
	// Compute the refracted vector
	qbVector<double> p = incidentRay.m_lineAB;
	p.Normalize(); 
	qbVector<double> tempNormal = localNormal;
	double r = 1.0 / m_indexOfRefraction;
	double c = -qbVector<double>::dot(tempNormal, p);
	if (c < 0.0) {
		tempNormal = tempNormal * -1.0;
		c = -qbVector<double>::dot(tempNormal, p); 

	} // if (c < 0.0)

	qbVector<double> refractedVector = r * p + (r * c - sqrtf( 1.0 - pow(r, 2.0) * (1.0 - pow(c, 2.0)))) * tempNormal; 

	// Construct the refracted ray
	LRT::Ray refractedRay(intPoint + (refractedVector * 0.01), intPoint + refractedVector);
	
	// Test for secondary intersection with this object
	std::shared_ptr<LRT::ObjectBase> closestObject;
	qbVector<double> closestIntPoint   { 3 };
	qbVector<double> closestLocalNormal{ 3 };
	qbVector<double> closestLocalColor { 3 }; 
	qbVector<double> newIntPoint       { 3 };
	qbVector<double> newLocalNormal	   { 3 };
	qbVector<double> newLocalColor	   { 3 };
	bool test = currentObject->testIntersections(refractedRay, newIntPoint, newLocalNormal, newLocalColor);
	bool intersectionFound = false;
	LRT::Ray finalRay;

	if (test) {
		// Compute the refracted vector
		qbVector<double> p_2 = refractedRay.m_lineAB;
		p_2.Normalize();
		qbVector<double> tempNormal_2 = newLocalNormal;
		double r_2 = 1.0 / m_indexOfRefraction; 
		double c_2 = -qbVector<double>::dot(tempNormal_2, p_2);
		if (c_2 < 0.0) {
			tempNormal_2 = tempNormal_2 * -1.0; 
			c_2 = -qbVector<double>::dot(tempNormal_2, p_2);

		} // if (c_2 < 0.0)

		// Compute the refracted ray
		qbVector<double> refractedVector_2 = r_2 * p_2 + (r_2 * c_2 - sqrtf(1.0 - pow(r_2, 2.0) * (1.0 - pow(c_2, 2.0)))) * tempNormal_2;
		LRT::Ray refractedRay_2(newIntPoint + (refractedVector_2 * 0.01), newIntPoint + refractedVector_2); 

		// Cast this ray to the scene
		// This ray is now leaving the object
		intersectionFound = CastRay(refractedRay_2, objectList, currentObject, closestObject, closestIntPoint, closestLocalNormal, closestLocalColor); 
		finalRay = refractedRay_2;

	} // if(test)
	else {
		// no secondary intersections were found
		// continue the original refracted ray
		intersectionFound = CastRay(refractedRay, objectList, currentObject, closestObject, closestIntPoint, closestLocalNormal, closestLocalColor); 
		finalRay = refractedRay; 

	} // else

	// Compute the color for closestObject
	qbVector<double> matColor{ 3 };
	if (intersectionFound) {
		// check if a material has been assigned
		if (closestObject->m_HasMaterial)
			matColor = closestObject->m_pMaterial->ComputeColor(objectList, lightList, closestObject, closestIntPoint, closestLocalNormal, finalRay);
		else
			matColor = LRT::MaterialBase::computeDiffuseColor(objectList, lightList, closestObject, closestIntPoint, closestLocalNormal, closestObject->m_BaseColor);

	} // if (intersectionFound)
	else {
		// leave matColor as it is

	} // else

	trnColor = matColor;
	return trnColor;

} // computeTransluency