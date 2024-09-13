#pragma once

#include "NoiseBase.hpp"

// std
#include <vector>
#include <random>

namespace LRT {
	namespace Noise {
		class GradientNoiseGenerator : public NoiseBase {
		public:
			GradientNoiseGenerator();
			virtual ~GradientNoiseGenerator() override;
			virtual double getValue(double x, double y) override;
			virtual void SetupGrid(int scale) override;

		public:
			std::vector<std::vector<double>> vectorGridX_;
			std::vector<std::vector<double>> vectorGridY_;

			bool wrap_ = false;

		private:
			std::vector<double> ComputeNormDisp(double x1, double y1, double x2, double y2);
		
		}; // GradientNoiseGenerator
	
	} // Noise

} // LRT