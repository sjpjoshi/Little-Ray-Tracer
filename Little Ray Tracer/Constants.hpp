#pragma once

#include "NormalBase.hpp"

// std
#include <random>

namespace LRT {
	namespace Normal {
		class Constant : public NormalBase {
		public:
			Constant();
			virtual ~Constant() override;
		
			virtual qbVector<double> ComputePerturbation(const qbVector<double>& normal, const qbVector<double>& uvCoords) override;

		public:
			qbVector<double> displacement_ { 3 };

		}; // Constant

	} // Normal

} // LRT