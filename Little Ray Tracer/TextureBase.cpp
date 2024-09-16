#include "TextureBase.hpp"

// std
#include <cmath>

LRT::Texture::TextureBase::TextureBase() {} // TextureBase
LRT::Texture::TextureBase::~TextureBase() {} // ~TextureBase

qbVector<double> LRT::Texture::TextureBase::getColor(const qbVector<double>& uvCoords) {
	// setup the output vector
	qbVector<double> outputColor{ 4 };
	return outputColor;	

} // getColor

void LRT::Texture::TextureBase::setTransform(const qbVector<double>& translation, const double& rotation, const qbVector<double>& scale) {
	// Build the transform matrix
	qbMatrix2<double> rotationMatrix = { 3,3, std::vector<double>{cos(rotation), -sin(rotation), 0.0,
																  sin(rotation), cos(rotation), 0.0,
																  0.0, 0.0, 1.0} };

	qbMatrix2<double> scaleMatrix = { 3, 3, std::vector<double> {scale.GetElement(0), 0.0, 0.0,
																 0.0, scale.GetElement(1), 0.0,
																 0.0, 0.0, 1.0} };

	qbMatrix2<double> translationMatrix = { 3, 3, std::vector<double> {1.0, 0.0, translation.GetElement(0),
																	   0.0, 1.0, translation.GetElement(1),
																	   0.0, 0.0, 1.0} };

	// And combine to form the final transform matrix.
	m_transformMatrix = translationMatrix * rotationMatrix * scaleMatrix; 

} // setTransform

qbVector<double> LRT::Texture::TextureBase::blendColors(const std::vector<qbVector<double>>& inputColorList) {
	// Setup the output color.
	qbVector<double> outputColor{ 3 };
	return outputColor;

} // blendColorss

qbVector<double> LRT::Texture::TextureBase::applyTransform(const qbVector<double>& inputVector) {
	// Copy the input vector and modify to have three elements.
	qbVector<double> newInput{ 3 };
	newInput.SetElement(0, inputVector.GetElement(0));
	newInput.SetElement(1, inputVector.GetElement(1));

	// Apply the transform.
	qbVector<double> result = m_transformMatrix * newInput;

	// Produce the output.
	qbVector<double> output{ 2 };
	output.SetElement(0, result.GetElement(0));
	output.SetElement(1, result.GetElement(1));

	return output;

} // applyTransform

double LRT::Texture::TextureBase::GetValue(const qbVector<double>& uvCoords) {
	// Return a default value.
	return 0.0;

} // getValue
