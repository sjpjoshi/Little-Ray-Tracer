#pragma once

#include "TextureBase.hpp"

namespace LRT {
	namespace Texture {
		class Checker : public TextureBase {
		public:
			Checker();
			virtual ~Checker() override;

			virtual qbVector<double> getColor(const qbVector<double>& uvCoords) override;
			void setColor(const qbVector<double>& inputColor1, const qbVector<double>& inputColor2);
			void setColor(const std::shared_ptr<LRT::Texture::TextureBase>& inputColor1, const std::shared_ptr<LRT::Texture::TextureBase>& inputColor2);

		private:
			std::shared_ptr<LRT::Texture::TextureBase> m_pColor1;
			std::shared_ptr<LRT::Texture::TextureBase> m_pColor2;

		}; // Checker

	} // Texture

} // LRT