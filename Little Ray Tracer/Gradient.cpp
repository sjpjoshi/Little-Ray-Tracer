#include "Gradient.hpp"

LRT::Texture::Gradient::Gradient()  {} // Gradient
LRT::Texture::Gradient::~Gradient() {} // ~Gradient

qbVector<double> LRT::Texture::Gradient::getColor(const qbVector<double>& uvCoords) {
	// Apply the local transform to the uv coords
	qbVector<double> inputLocation = uvCoords;
	qbVector<double> newLocation = applyTransform(inputLocation);
	double newU = std::min((inputLocation.GetElement(1) + 1.0) / 2.0, 1.0); 

	return m_ColorMap.getColor(newU);

} // getColor

void LRT::Texture::Gradient::setStop(double position, const qbVector<double>& value){
	m_ColorMap.setStop(position, value);

} // setStop