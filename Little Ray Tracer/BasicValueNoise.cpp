#include "BasicValueNoise.hpp"

LRT::Texture::BasicValueNoise::BasicValueNoise() {
	noiseGenerator_.SetupGrid(scale_);

} // BasicValueNoise

LRT::Texture::BasicValueNoise::~BasicValueNoise() {} // ~BasicValueNoise

qbVector<double> LRT::Texture::BasicValueNoise::getColor(const qbVector<double>& uvCoords) {
	// Apply the local transform to the (u,v) coordinates.
	qbVector<double> inputLoc = uvCoords;
	qbVector<double> newLoc = applyTransform(inputLoc);
	double newU = newLoc.GetElement(0);
	double newV = newLoc.GetElement(1);

	qbVector<double> localColor;
	/* If no color map has been provided, then output purple. This should be
		easily recognizable in the scene, indicating that something is wrong. */
	if (!haveColorMap_)
		localColor = qbVector<double>{ std::vector<double>{1.0, 0.0, 1.0, 1.0} };
	
	else {
		// Generate the base function.
		double mapPosition = std::clamp(noiseGenerator_.getValue(newU, newV) * amplitude_, 0.0, 1.0);
		localColor = colorMap_->getColor(mapPosition);

	} // else

	return localColor;

} // getColor

void LRT::Texture::BasicValueNoise::setColorMap(const std::shared_ptr<LRT::Texture::ColorMap>& colorMap) {
	colorMap_ = colorMap;
	haveColorMap_ = true;

} //  setColorMap

void LRT::Texture::BasicValueNoise::setAmplitude(double amplitude) {
	amplitude_ = amplitude;

} // setAmplitude

void LRT::Texture::BasicValueNoise::setScale(int scale) {
	scale_ = scale;
	noiseGenerator_.SetupGrid(scale_); 

} // setScale