#pragma once

#include "TextureBase.hpp"

namespace LRT {
	namespace Texture {
		class Flat : public TextureBase {
		public:
			Flat();
			virtual ~Flat() override;

			virtual qbVector<double> getColor(const qbVector<double>& uvCoords) override;
			void setColor(const qbVector<double>& inputColor); 

		private:
			qbVector<double> m_Color{ 4 };

		}; // Flat

	} // Texture

} // LRT