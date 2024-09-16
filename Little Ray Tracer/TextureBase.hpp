#pragma once

#include "Ray.hpp"

// std
#include <memory>

// Lin alg
#include "./qbLinAlg/qbVector.h"
#include "./qbLinAlg/qbMatrix.h"

namespace LRT {
	namespace Texture {
		class TextureBase {
		public:
			TextureBase();
			virtual ~TextureBase();

			// note that the coords are returned as a 4D vector -> rgba
			virtual qbVector<double> getColor(const qbVector<double>& uvCoords);
			void setTransform(const qbVector<double>& translation, const double &rotation, const qbVector<double>& scale);
			static qbVector<double> blendColors(const std::vector<qbVector<double>>& inputColorList);
			qbVector<double> applyTransform(const qbVector<double>& inputVector);
			virtual double GetValue(const qbVector<double>& uvCoords);

		private:

		private:
			qbMatrix2<double> m_transformMatrix{ 3, 3, std::vector<double>{1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0} };

		}; // TextureBase

	} // Texture

} // LRT