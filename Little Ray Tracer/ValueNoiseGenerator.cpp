#include "ValueNoiseGenerator.hpp"

// std
#include <cmath>
#include <iostream>

LRT::Noise::ValueNoiseGenerator::ValueNoiseGenerator() {
	// Configure the default grid.
	SetupGrid(2);

} // ValueNoiseGenerator

LRT::Noise::ValueNoiseGenerator::~ValueNoiseGenerator() {} // ~ValueNoiseGenerator

double LRT::Noise::ValueNoiseGenerator::getValue(double x, double y) {
	// Ensure that x and y are cyclic.
	x = fmod(x, 1.0);
	y = fmod(y, 1.0);

	// Convert x and y to a range of 0 to 1.
	x = (x + 1.0) / 2.0;
	y = (y + 1.0) / 2.0;

	// Determine the spacing of the grid boundaries.
	double gridSpacing = 1.0 / static_cast<double>(scale_);

	// Compute local x and y.
	double localX = fmod(x, gridSpacing); 
	double localY = fmod(y, gridSpacing); 

	// Compute the grid corner indices.
	int minX = static_cast<int>((x - localX) * scale_); 
	int minY = static_cast<int>((y - localY) * scale_); 

	int c1Xi = std::max(minX, 0); 
	int c1Yi = std::max(minY, 0); 
	int c2Xi = std::min(minX + 1, scale_);
	int c2Yi = std::max(minY, 0); 

	int c3Xi = std::max(minX, 0);
	int c3Yi = std::min(minY + 1, scale_); 
	int c4Xi = std::min(minX + 1, scale_);
	int c4Yi = std::min(minY + 1, scale_); 

	// Extract the four values.
	double v1 = valueGrid_.at(c1Xi).at(c1Yi); 
	double v2 = valueGrid_.at(c2Xi).at(c2Yi); 
	double v3 = valueGrid_.at(c3Xi).at(c3Yi); 
	double v4 = valueGrid_.at(c4Xi).at(c4Yi); 

	// And interpolate.
	double xWeight = localX * static_cast<double>(scale_);
	double yWeight = localY * static_cast<double>(scale_);
	double t1 = Lerp(v1, v3, yWeight);
	double t2 = Lerp(v2, v4, yWeight);
	return Lerp(t1, t2, xWeight);

} // getValue

void LRT::Noise::ValueNoiseGenerator::SetupGrid(int scale) {
	scale_ = scale;

	// Generate a seed for the random number generation.
	std::random_device randDev;
	std::seed_seq seed{ randDev(), randDev(), randDev(), randDev() };

	// The random number generator

	/* Use the seed version if you want a different pattern everytime,
		or use without seed, or with a fixed seed, if you want the
		pattern to remain the same every time. */

		//std::mt19937 randGen(seed);
	std::mt19937 randGen;

	// Setup the random number distribution.
	// (uniform real numbers betweeon 0 and 1).
	std::uniform_real_distribution<double> randomDist(0.0, 1.0);

	// Generate the grid of random vectors.
	/*
		'scale' defines how many grid squares we want, so a scale of
		1 means a single grid square, 2 means a 2x2 grid, 3 a 3x3 grid
		and so on.
	*/
	valueGrid_.clear();
	valueGrid_.resize(scale_ + 1, std::vector<double>(scale_ + 1, 0.0));
	for (int x = 0; x <= scale_; ++x) {
		for (int y = 0; y <= scale_; ++y)
			// Store a random value.
			valueGrid_.at(x).at(y) = randomDist(randGen);

		 
	} // for

	if (wrap_) {
		for (int x = 0; x <= scale_; ++x)
			valueGrid_.at(x).at(scale_) = valueGrid_.at(x).at(0);
		
		for (int y = 0; y <= scale_; ++y)
			valueGrid_.at(scale_).at(y) = valueGrid_.at(0).at(y);
		
	} // if

} // SetupGrid