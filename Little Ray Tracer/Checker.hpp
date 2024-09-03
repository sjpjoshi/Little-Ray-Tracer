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

		private:
			qbVector<double> m_Color1{4};
			qbVector<double> m_Color2{4}; 

		}; // Checker

	} // Texture

} // LRT