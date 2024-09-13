#include "GradidentNoiseGenerator.hpp"
#include "TextureBase.hpp"
#include "ColorMap.hpp"

namespace LRT {
	namespace Texture {
		class Marble : public TextureBase {
		public:
			Marble();
			virtual ~Marble() override;

			virtual qbVector<double> getColor(const qbVector<double>& uvCoords) override;

			void setColorMap(const std::shared_ptr<LRT::Texture::ColorMap>& colorMap);
			void setAmplitude(double amplitude1, double amplitude2);
			void setScale(int scale1, int scale2);
			void setMinMax(double minValue, double maxValue);
			void setSine(double amplitude, double frequency);

		public:
			std::shared_ptr<LRT::Texture::ColorMap> color_map_;
			bool have_color_map_ = false; 

			std::vector<LRT::Noise::GradientNoiseGenerator> noiseGeneratorList_; 

			double amplitude1_ = 8.0;
			double amplitude2_ = 8.0;

			int scale_1_ = 4;
			int scale_2_ = 40;

			double max_value_ = 1.0;
			double min_value_ = -1.0;

			double sine_amplitude_ = 0.25;
			double sine_frequency_ = 4.0;

		}; // Marble

	} // Texture

} // LRT