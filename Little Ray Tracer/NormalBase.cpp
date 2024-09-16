#include "NormalBase.hpp"

LRT::Normal::NormalBase::NormalBase()  {} // NormalBase
LRT::Normal::NormalBase::~NormalBase() {} // ~NormalBase

qbVector<double> LRT::Normal::NormalBase::ComputePerturbation(const qbVector<double>& normal, const qbVector<double>& uvCoords) {
	// The default response.
	return qbVector<double>{std::vector<double> {0.0, 0.0, 0.0} };

} // ComputePerturbation

qbVector<double> LRT::Normal::NormalBase::PerturbNormal(const qbVector<double>& normal, const qbVector<double>& perturbation) {
	// Decide upon an appropriate up vector.
	qbVector<double> newUpVector = std::vector<double>{ 0.0, 0.0, -1.0 };
	if ((normal.GetElement(2) > 0.99) || (normal.GetElement(2) < -0.99)) 
		newUpVector = std::vector<double>{ 1.0, 0.0, 0.0 }; 

	// Compute the directions (based on the tangent plane).
	qbVector<double> pV = qbVector<double>::cross(newUpVector, normal);
	pV.Normalize();
	qbVector<double> pU = qbVector<double>::cross(normal, pV);
	pU.Normalize();

	// Apply the perturbation.
	qbVector<double> output = normal + (pU * perturbation.GetElement(0)) + (pV * perturbation.GetElement(1)) + (normal * perturbation.GetElement(2));

	// Normalize the output.
	output.Normalize();

	// And return.
	return output;

} // PerturbNormal

void LRT::Normal::NormalBase::setAmplitude(double amplitude) {
	amplitudeScale_ = amplitude;

} // setAmplitude

void LRT::Normal::NormalBase::setTransform(const qbVector<double>& translation, const double& rotation, const qbVector<double>& scale) {
	// Build the transform matrix.
	qbMatrix2<double> rotationMatrix = { 3,3,  std::vector<double> {cos(rotation), -sin(rotation), 0.0,
															  sin(rotation), cos(rotation), 0.0,
															  0.0, 0.0, 1.0} };

	qbMatrix2<double> scaleMatrix = { 3,3, std::vector<double> {scale.GetElement(0), 0.0, 0.0,
														   0.0, scale.GetElement(1), 0.0,
														   0.0, 0.0, 1.0} };

	qbMatrix2<double> translationMatrix = { 3,3, std::vector<double> { 1.0, 0.0, translation.GetElement(0),
																  0.0, 1.0, translation.GetElement(1),
																  0.0, 0.0, 1.0} };

	// And combine to form the final transform matrix.
	transformMatrix_ = translationMatrix * rotationMatrix * scaleMatrix;

} // setTransform

qbVector<double> LRT::Normal::NormalBase::ApplyTransform(const qbVector<double>& inputVector) {
	// Copy the input vector and modify to have three elements.
	qbVector<double> newInput;
	newInput.SetElement(0, inputVector.GetElement(0));
	newInput.SetElement(1, inputVector.GetElement(1));

	// Apply the transform.
	qbVector<double> result = transformMatrix_ * newInput;

	// Produce the output.
	qbVector<double> output;
	output.SetElement(0, result.GetElement(0));
	output.SetElement(1, result.GetElement(1));

	return output;

} // ApplyTransform