#pragma once

#ifndef SCENE_H
#define SCENE_H

#include "Image.hpp"
#include "Camera.hpp"
#include "ObjectSphere.hpp"
#include "PointLight.hpp"
#include "ObjectPlane.hpp"

// std
#include <vector>
#include <memory>

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
		std::vector<std::shared_ptr<LRT::ObjectBase>> m_objectList;
		std::vector<std::shared_ptr<LRT::LightBase>>  m_lightList;
		
	};// Scene

} // LRT

#endif