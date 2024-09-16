#pragma once

#include "NormalBase.hpp"

// std
#include <random>

namespace LRT {
	namespace Normal {
		class SimpleRough : public NormalBase {
		public:
			SimpleRough();
			virtual ~SimpleRough() override;

			virtual qbVector<double> ComputePerturbation(const qbVector<double>& normal, const qbVector<double>& uvCoords) override;

		private:
			std::shared_ptr<std::mt19937> p_randGen_;

		}; // SimpleRough

	} // Normal

} // LRT