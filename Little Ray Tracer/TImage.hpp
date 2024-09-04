#pragma once

#include "TextureBase.hpp"

// lib
#include <SDL2/SDL.h>

namespace LRT {
	namespace Texture {
		class TImage : public TextureBase {
		public:
			TImage();
			virtual ~TImage() override;

			virtual qbVector<double> getColor(const qbVector<double>& uvCoords);
			
			bool loadImage(std::string fileName);
			
		private:
			std::string m_fileName;
			SDL_Surface* m_imageSurface;
			SDL_PixelFormat* m_pixelFormat;
			bool m_imageLoaded = false;
			int m_xSize, m_ySize, m_pitch;
			uint8_t m_bytesPerPixel;
			uint32_t m_rMask, m_gMask, m_bMask, m_aMask; 

		}; // TImage

	} // Texture

} // LRT