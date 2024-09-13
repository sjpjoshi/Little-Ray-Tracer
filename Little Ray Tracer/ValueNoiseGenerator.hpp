#pragma once

#include "noisebase.hpp"

// std
#include <vector>
#include <random>

namespace LRT {
	namespace Noise {
		class ValueNoiseGenerator : public NoiseBase {
		public:
			ValueNoiseGenerator();
			virtual ~ValueNoiseGenerator() override;

			// Function to get the value at a specific location.
			virtual double getValue(double x, double y) override;

			// Function to setup the grid.
			virtual void SetupGrid(int scale) override;

		public:
			// Store the grid of vectors.
			std::vector<std::vector<double>> valueGrid_;
			bool wrap_ = false;

		}; // ValueNoiseGenerator

	} // Noise

} // LRT