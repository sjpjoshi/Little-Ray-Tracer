#pragma once

#include "GradidentNoiseGenerator.hpp"
#include "ValueNoiseGenerator.hpp"
#include "TextureBase.hpp"
#include "ColorMap.hpp"

namespace LRT {
	namespace Texture {
		class BasicNoise : public TextureBase {
		public:
			BasicNoise();
			virtual ~BasicNoise() override;
			virtual qbVector<double> getColor(const qbVector<double>& uvCoords) override;

			void SetColorMap(const std::shared_ptr<LRT::Texture::ColorMap>& colorMap);
			void SetAmplitude(double amplitude);
			void SetScale(int scale);

		public:
			std::shared_ptr<LRT::Texture::ColorMap> colorMap_;
			bool haveColorMap_ = false;
			LRT::Noise::GradientNoiseGenerator noiseGenerator_;
			double amplitude_ = 8.0;
			int scale_ = 3;

		}; // BasicNoise
	
	} // Texture

} // LRT