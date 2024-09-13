#pragma once

#include "ValueNoiseGenerator.hpp"
#include "TextureBase.hpp"
#include "ColorMap.hpp"

namespace LRT {
	namespace Texture {
		class BasicValueNoise : public TextureBase {
		public:
			BasicValueNoise();
			virtual ~BasicValueNoise() override;

			virtual qbVector<double> getColor(const qbVector<double>& uvCoords) override;
			void setColorMap(const std::shared_ptr<LRT::Texture::ColorMap>& colorMap);
			void setAmplitude(double amplitude);
			void setScale(int scale);

		public:
			std::shared_ptr<LRT::Texture::ColorMap> colorMap_;
			bool haveColorMap_ = false;
			LRT::Noise::ValueNoiseGenerator noiseGenerator_;
			double amplitude_ = 8.0;
			int scale_ = 3;

 		}; // basicValueNoise
	
	} // Texture

} // LRT