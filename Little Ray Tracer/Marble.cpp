#include "Marble.hpp"

// libs
#include <SDL2/SDL_stdinc.h>

LRT::Texture::Marble::Marble() {
	// Configure the noise generators.
	noiseGeneratorList_.push_back(LRT::Noise::GradientNoiseGenerator());
	noiseGeneratorList_.push_back(LRT::Noise::GradientNoiseGenerator()) ;

	noiseGeneratorList_.at(0).SetupGrid(4); 
	noiseGeneratorList_.at(1).SetupGrid(40); 

	min_value_ = -3.0;
	max_value_ = 3.0;

} // Marble

LRT::Texture::Marble::~Marble() {} // ~Marble

qbVector<double> LRT::Texture::Marble::getColor(const qbVector<double>& uvCoords) {
	// Apply the local transform to the (u,v) coordinates.
	qbVector<double> inputLoc = uvCoords; 
	qbVector<double> newLoc = applyTransform(inputLoc); 
	double newU = newLoc.GetElement(0); 
	double newV = newLoc.GetElement(1); 

	qbVector<double> localColor;
	/* If no color map has been provided, then output purple. This should be
		easily recognizable in the scene, indicating that something is wrong. */
	if (!have_color_map_)
		localColor = qbVector<double>{ std::vector<double>{1.0, 0.0, 1.0, 1.0} };
	
	else {
		// Generate the base function.
		double mapPosition = sine_amplitude_ *
			sin(sine_frequency_ * M_PI *
				(((newU + newV) / 2.0) +
					(noiseGeneratorList_.at(0).getValue(newU, newV) * amplitude1_) +
					(noiseGeneratorList_.at(1).getValue(newU, newV) * amplitude2_)));

		// Normalize to min and max values.
		mapPosition = std::clamp((mapPosition - min_value_) / (max_value_ - min_value_), 0.0, 1.0);

		localColor = color_map_->getColor(mapPosition);
	}

	return localColor;
} // getColor

void LRT::Texture::Marble::setColorMap(const std::shared_ptr<LRT::Texture::ColorMap>& colorMap) {
	color_map_ = colorMap;
	have_color_map_ = true;

} // setColorMap

void LRT::Texture::Marble::setAmplitude(double amplitude1, double amplitude2) {
	amplitude1_ = amplitude1;
	amplitude2_ = amplitude2;

} // setAmplitude

void LRT::Texture::Marble::setScale(int scale1, int scale2) {
	scale_1_ = scale1; 
	scale_2_ = scale2;
	noiseGeneratorList_.at(0).SetupGrid(scale_1_); 
	noiseGeneratorList_.at(1).SetupGrid(scale_2_); 

} // setScale

void LRT::Texture::Marble::setMinMax(double minValue, double maxValue) {
	min_value_ = minValue;
	max_value_ = maxValue; 

} // setMinMax

void LRT::Texture::Marble::setSine(double amplitude, double frequency) {
	sine_amplitude_ = amplitude; 
	sine_frequency_ = frequency; 

} // setSine