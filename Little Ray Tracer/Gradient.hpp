#pragma once

#include "TextureBase.hpp"
#include "ColorMap.hpp"

namespace LRT {
	namespace Texture {
		class Gradient : public TextureBase {
		public:
			Gradient();
			virtual ~Gradient() override;

			virtual qbVector<double> getColor(const qbVector<double>& uvCoords); 
			void setStop(double position, const qbVector<double>& value);

		private:
			LRT::Texture::ColorMap m_ColorMap;

		}; // Gradient
	
	} // Texture

} // LRT