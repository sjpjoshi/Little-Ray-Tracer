#pragma once

// std
#include <vector>
#include <random>

namespace LRT {
	namespace Noise {
		class NoiseBase {
		public:
			NoiseBase();
			virtual ~NoiseBase();

			virtual double getValue(double u, double v);
			double Lerp(double v1, double v2, double iPos);
			virtual void SetupGrid(int scale);

		public:
			int scale_;

 		}; // NoiseBase

	} // Noise

} // LRT