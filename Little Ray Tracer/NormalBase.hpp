#pragma once

#include "Ray.hpp"
#include "TextureBase.hpp"

// lin alg
#include "qbLinAlg/qbMatrix.h"
#include "qbLinAlg/qbVector.h"

// std
#include <memory>

namespace LRT {
	namespace Normal {
		class NormalBase {
		public: 
			NormalBase();
			virtual ~NormalBase();

			virtual qbVector<double> ComputePerturbation(const qbVector<double>& normal, const qbVector<double>& uvCoords);

			qbVector<double> PerturbNormal(const qbVector<double>& normal, const qbVector<double>& perturbation);	

			void setAmplitude(double amplitude);
			void setTransform(const qbVector<double>& translation, const double& rotation, const qbVector<double>& scale);
			qbVector<double> ApplyTransform(const qbVector<double>& inputVector);

		public:
			double amplitudeScale_ = 1.0;

		private:
			// Initialise the transform matrix to the identity matrix.
			qbMatrix2<double> transformMatrix_{ 3,3, std::vector<double>{1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0} };

		}; // NormalBase

	} // Normal

} // LRT