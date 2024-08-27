#pragma once

#ifndef SCENE_H
#define SCENE_H

#include "Image.hpp"

// std
#include <vector>

// libs
#include <SDL2/SDL.h>

namespace LRT {
	class Scene {
	public:
		Scene();
		bool Render(Image& outputImage);

	private:
	

	private:


	};// Scene

} // LRT

#endif