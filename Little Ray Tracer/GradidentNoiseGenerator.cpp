#include "GradidentNoiseGenerator.hpp"
#include <SDL2/SDL_stdinc.h>

LRT::Noise::GradientNoiseGenerator::GradientNoiseGenerator() {
	// Configure the default grid.
	SetupGrid(2);

} // GradientNoiseGenerator

LRT::Noise::GradientNoiseGenerator::~GradientNoiseGenerator() {} // ~GradientNoiseGenerator

double LRT::Noise::GradientNoiseGenerator::getValue(double x, double y) {
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

	// Extract the four vectors.
	std::vector<double> v1{ vectorGridX_.at(c1Xi).at(c1Yi), vectorGridY_.at(c1Xi).at(c1Yi) }; 
	std::vector<double> v2{ vectorGridX_.at(c2Xi).at(c2Yi), vectorGridY_.at(c2Xi).at(c2Yi) }; 
	std::vector<double> v3{ vectorGridX_.at(c3Xi).at(c3Yi), vectorGridY_.at(c3Xi).at(c3Yi) }; 
	std::vector<double> v4{ vectorGridX_.at(c4Xi).at(c4Yi), vectorGridY_.at(c4Xi).at(c4Yi) }; 

	// Compute locations of the four corners.
	double c1X = static_cast<double>(c1Xi) * gridSpacing; 
	double c1Y = static_cast<double>(c1Yi) * gridSpacing; 
	double c2X = static_cast<double>(c2Xi) * gridSpacing; 
	double c2Y = static_cast<double>(c2Yi) * gridSpacing; 
	double c3X = static_cast<double>(c3Xi) * gridSpacing; 
	double c3Y = static_cast<double>(c3Yi) * gridSpacing; 
	double c4X = static_cast<double>(c4Xi) * gridSpacing; 
	double c4Y = static_cast<double>(c4Yi) * gridSpacing; 

	// Compute the displacement vectors.
	std::vector<double> d1 = ComputeNormDisp(x, y, c1X, c1Y); 
	std::vector<double> d2 = ComputeNormDisp(x, y, c2X, c2Y);
	std::vector<double> d3 = ComputeNormDisp(x, y, c3X, c3Y);
	std::vector<double> d4 = ComputeNormDisp(x, y, c4X, c4Y);

	// Compute the dot products.
	double dp1 = (v1.at(0) * d1.at(0)) + (v1.at(1) * d1.at(1));
	double dp2 = (v2.at(0) * d2.at(0)) + (v2.at(1) * d2.at(1));
	double dp3 = (v3.at(0) * d3.at(0)) + (v3.at(1) * d3.at(1));
	double dp4 = (v4.at(0) * d4.at(0)) + (v4.at(1) * d4.at(1));

	// And interpolate.
	double xWeight = localX * static_cast<double>(scale_); 
	double yWeight = localY * static_cast<double>(scale_);
	double t1 = Lerp(dp1, dp3, yWeight);
	double t2 = Lerp(dp2, dp4, yWeight);
	return Lerp(t1, t2, xWeight);

} // getValue

void LRT::Noise::GradientNoiseGenerator::SetupGrid(int scale) {
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
	vectorGridX_.clear();
	vectorGridY_.clear();
	vectorGridX_.resize(scale_ + 1, std::vector<double>(scale_ + 1, 0.0));
	vectorGridY_.resize(scale_ + 1, std::vector<double>(scale_ + 1, 0.0));
	for (int x = 0; x <= scale_; ++x) {
		for (int y = 0; y <= scale_; ++y) {
			// Compute a random theta.
			double theta = randomDist(randGen) * 2.0 * M_PI;

			// Convert this to Cartessian coordinates (assuming r = 1.0).
			double vX = cos(theta);
			double vY = sin(theta);

			// And store at the appropriate grid location.
			vectorGridX_.at(x).at(y) = vX;
			vectorGridY_.at(x).at(y) = vY;

		} // for 

	} // for

	if (wrap_) {
		for (int x = 0; x <= scale_; ++x) {
			vectorGridX_.at(x).at(scale_) = vectorGridX_.at(x).at(0);
			vectorGridY_.at(x).at(scale_) = vectorGridY_.at(x).at(0);

		} // for

		for (int y = 0; y <= scale_; ++y) {
			vectorGridX_.at(scale_).at(y) = vectorGridX_.at(0).at(y);
			vectorGridY_.at(scale_).at(y) = vectorGridY_.at(0).at(y);

		} // for

	} // if

} // SetupGrid

std::vector<double> LRT::Noise::GradientNoiseGenerator::ComputeNormDisp(double x1, double y1, double x2, double y2) {
	double xComp = x1 - x2;
	double yComp = y1 - y2;
	return std::vector<double> {xComp, yComp};

} // 