#include "SimpleMaterial.hpp"

LRT::SimpleMaterial::SimpleMaterial() {} // SimpleMaterial

LRT::SimpleMaterial::~SimpleMaterial() {} // ~SimpleMaterial

qbVector<double> LRT::SimpleMaterial::ComputeColor(const std::vector<std::shared_ptr<LRT::ObjectBase>>& objectList, const std::vector<std::shared_ptr<LRT::LightBase>>& lightList, const std::shared_ptr<LRT::ObjectBase>& currentObject, const qbVector<double>& intPoint, const qbVector<double>& localNormal, const LRT::Ray& cameraRay) {
	// define the intial material colors
	qbVector<double> matColor { 3 }; // materials
	qbVector<double> refColor { 3 }; // reflective
	qbVector<double> diffColor{ 3 };// diffuse
	qbVector<double> spcColor { 3 }; // specular

	// Compute the diffuse component
	if (!m_HasTexture) {
		std::cout << "hi if (!m_HasTexture) ComputeColor" << std::endl;  
		diffColor = computeDiffuseColor(objectList, lightList, currentObject, intPoint, localNormal, m_BaseColor);
	}
	else {
		std::cout << "hi else ComputeColor" << std::endl;  
		diffColor = computeDiffuseColor(objectList, lightList, currentObject, intPoint, localNormal, getTextureColor(currentObject->m_UVCoords)); 
	}
	// compute the reflection component
	if (m_Reflectivity > 0.0)
		refColor = computeReflectionColor(objectList, lightList, currentObject, intPoint, localNormal, cameraRay);

	// combine reflection and diffuse components
	matColor = (refColor * m_Reflectivity) + (diffColor * (1 - m_Reflectivity));

	// Compute the specular Component
	if (m_Shininess > 0) 
		spcColor = computeSpecular(objectList, lightList, intPoint, localNormal, cameraRay);

	// add the specular component to final color
	matColor = matColor + spcColor;
	return matColor;

} // ComputeColor

qbVector<double> LRT::SimpleMaterial::computeSpecular(const std::vector<std::shared_ptr<LRT::ObjectBase>>& objectList, const std::vector<std::shared_ptr<LRT::LightBase>>& lightList, const qbVector<double>& intPoint, const qbVector<double>& localNormal, const LRT::Ray& cameraRay) {
	qbVector<double> spcColor{ 3 }; // specular
	double red = 0.0, green = 0.0, blue = 0.0;

	// loop through all of the lights in the scene
	for (auto currentLight : lightList) {
		// check for intersections with all objects in the scene
		double intensity = 0.0;
		// construct a vector pointing from the intersection point to the light
		qbVector<double> lightDirection = (currentLight->m_Location - intPoint).Normalized();
		// compute the start point
		qbVector<double> startPoint = intPoint + (lightDirection * 0.001);
		//Construct a ray from the point of intersection to the light
		LRT::Ray lightRay(startPoint, startPoint + lightDirection);
	
		qbVector<double> poi{ 3 }; // point of instersection
		qbVector<double> poiNormal{ 3 }; // point of instersection
		qbVector<double> poiColor{ 3 }; // point of instersection
		bool validInt = false; // valid intersection

		// Loop through all of the objects in the scene to check if any
		// obstruct light from this source
		for (auto sceneObject : objectList) {
			validInt = sceneObject->testIntersections(lightRay, poi, poiNormal, poiColor);
			if(validInt)
				break;

		} // for
	
		// if no intersections were found, then proceed with computing the specular component
		if (!validInt) {
			// Compute the reflection vector
			qbVector<double> d = lightRay.m_lineAB;
			qbVector<double> r = d - (2 * qbVector<double>::dot(d, localNormal) * localNormal);
			r.Normalize();

			// Compute the dot product
			qbVector<double> v = cameraRay.m_lineAB;
			v.Normalize();
			double dotProduct = qbVector<double>::dot(r, v);

			// only proceed if the dot product is positive
			if (dotProduct > 0.0) 
				intensity = m_Reflectivity * std::pow(dotProduct, m_Shininess);

		} // if
		
		red   += currentLight->m_Color.GetElement(0) * intensity;
		green += currentLight->m_Color.GetElement(1) * intensity;
		blue  += currentLight->m_Color.GetElement(2) * intensity;

	} // for
	
	spcColor.SetElement(0, red);
	spcColor.SetElement(1, green);
	spcColor.SetElement(2, blue);

	return spcColor;

} // computeSpecular