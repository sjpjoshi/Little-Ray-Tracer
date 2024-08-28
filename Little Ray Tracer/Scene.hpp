#pragma once

#ifndef SCENE_H
#define SCENE_H

#include "Image.hpp"
#include "Camera.hpp"
#include "ObjectSphere.hpp"

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
		LRT::Camera m_camera;
		LRT::ObjectSphere m_testSphere;


	};// Scene

} // LRT

#endif