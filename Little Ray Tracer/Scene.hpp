#pragma once

#ifndef SCENE_H
#define SCENE_H

#include "Image.hpp"
#include "Camera.hpp"
#include "ObjectSphere.hpp"
#include "PointLight.hpp"
#include "ObjectPlane.hpp"
#include "Cylinder.hpp"
#include "Cone.hpp"
#include "MaterialBase.hpp"
#include "SimpleMaterial.hpp"
#include "Checker.hpp"
#include "TImage.hpp"
#include "SimpleRefractive.hpp"
#include "Box.hpp"
#include "Sphere.hpp"
#include "Torus.hpp"
#include "Gradient.hpp"

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
		bool CastRay(LRT::Ray& castRay, 
			std::shared_ptr<LRT::ObjectBase>& closestObject, 
			qbVector<double>&closestIntPoint, 
			qbVector<double>& closestLocalNormal,
			qbVector<double>& closestLocalColor);

	private:

	private:
		LRT::Camera m_camera;
		std::vector<std::shared_ptr<LRT::ObjectBase>> m_objectList;
		std::vector<std::shared_ptr<LRT::LightBase>>  m_lightList;
		
	};// Scene

} // LRT

#endif