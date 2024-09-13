#include "BasicNoise.hpp"

// std
#include <algorithm>

LRT::Texture::BasicNoise::BasicNoise() {
	noiseGenerator_.SetupGrid(scale_);

} // BasicNoise 

LRT::Texture::BasicNoise::~BasicNoise() {} // ~BasicNoise

qbVector<double> LRT::Texture::BasicNoise::getColor(const qbVector<double>& uvCoords) {
	// Apply the local transform to the (u,v) coordinates.
	qbVector<double> inputLoc = uvCoords;
	qbVector<double> newLoc = applyTransform(inputLoc); 
	double newU = newLoc.GetElement(0); 
	double newV = newLoc.GetElement(1); 

	qbVector<double> localColor;
	/* If no color map has been provided, then output purple. This should be
		easily recognizable in the scene, indicating that something is wrong. */
	if (!haveColorMap_)
		localColor = qbVector<double>{ std::vector<double>{1.0, 0.0, 1.0, 1.0} }; // purple
	
	else {
		// Generate the base function.
		double mapPosition = std::clamp(noiseGenerator_.getValue(newU, newV) * amplitude_, 0.0, 1.0);
		localColor = colorMap_->getColor(mapPosition);

	} // else

	return localColor;

} // getColor

void LRT::Texture::BasicNoise::SetColorMap(const std::shared_ptr<LRT::Texture::ColorMap>& colorMap) {
	colorMap_ = colorMap; 
	haveColorMap_ = true; 

} // SetColorMap

void LRT::Texture::BasicNoise::SetAmplitude(double amplitude) {
	amplitude_ = amplitude;

} // SetAmplitude

void LRT::Texture::BasicNoise::SetScale(int scale) {
	scale_ = scale;
	noiseGenerator_.SetupGrid(scale_);

} // SetScale
