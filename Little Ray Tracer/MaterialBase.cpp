#include "MaterialBase.hpp"

LRT::MaterialBase::MaterialBase()  {} // MaterialBase
LRT::MaterialBase::~MaterialBase() {} // ~MaterialBase

qbVector<double> LRT::MaterialBase::ComputeColor(const std::vector<std::shared_ptr<LRT::ObjectBase>>& objectList, const std::vector<std::shared_ptr<LRT::LightBase>>& lightList, const std::shared_ptr<LRT::ObjectBase>& currentObject, const qbVector<double>& intPoint, const qbVector<double>& localNormal, const LRT::Ray& cameraRay) {
	// Define an initial material color
	qbVector<double> matColor{ 3 };
	return matColor;

} // ComputeColor

qbVector<double> LRT::MaterialBase::computeDiffuseColor(const std::vector<std::shared_ptr<LRT::ObjectBase>>& objectList, const std::vector<std::shared_ptr<LRT::LightBase>>& lightList, const std::shared_ptr<LRT::ObjectBase>& currentObject, const qbVector<double>& intPoint, const qbVector<double>& localNormal, const qbVector<double>& baseColor) {
	// Compute the color due to diffuse illumination
	qbVector<double> diffuseColor{ 3 };
	double intensity = 1.0;
	qbVector<double> color{ 3 };
	double red = 0.0, green = 0.0, blue = 0.0;
	double validIllum = false;
	bool illumFound = false;

	for (auto currentLight : lightList) {
		validIllum = currentLight->computeIllumination(intPoint, localNormal, objectList, currentObject, color, intensity);
		if (validIllum) {
			illumFound = true;
			red += color.GetElement(0) * intensity;
			green += color.GetElement(1) * intensity;
			blue += color.GetElement(2) * intensity;

		} // if (validIllum)

	} // for (auto currentLight : lightList)

	if (illumFound) {
		diffuseColor.SetElement(0, red * baseColor.GetElement(0));
		diffuseColor.SetElement(1, green * baseColor.GetElement(1));
		diffuseColor.SetElement(2, blue * baseColor.GetElement(2));

	} // if

	// return the material color
	return diffuseColor;

} // computeDiffuseColor

bool LRT::MaterialBase::CastRay(const LRT::Ray& castRay, const std::vector<std::shared_ptr<LRT::ObjectBase>>& objectList, const std::shared_ptr<LRT::ObjectBase>& thisObject, std::shared_ptr<LRT::ObjectBase>& closestObject, qbVector<double>& closestLocalColor) {
	return false;
} // CastRay