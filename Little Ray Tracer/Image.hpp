#pragma once
#ifndef IMAGE_H
#define IMAGE_H
	
#include <string>
#include <vector>
#include "SDL2/SDL.h"

class Image {

public:
	Image();
	~Image();
	void intialize(const int ImageX, const int ImageY, SDL_Renderer *Renderer);
	
	// remember we have to convert double later
	void setPixel(const int ImageX, const int ImageY, const double red, const double green, const double blue);
	void displayImage();

	int getImageX(); 
	int getImageY(); 

private:
	Uint32 convertColor(const double Red, const double Green, const double Blue);
	void intializeTexture();

private:
	// Image data
	std::vector<std::vector<double>> m_redChannel;
	std::vector<std::vector<double>> m_greenChannel;
	std::vector<std::vector<double>> m_blueChannel;

	// Image size
	int imageX, imageY;

	// SDL Vars
	SDL_Renderer* m_renderer;
	SDL_Texture* m_Texture;

}; // Image

#endif