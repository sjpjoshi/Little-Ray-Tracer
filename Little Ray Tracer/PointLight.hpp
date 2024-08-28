#pragma once
#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "LightBase.hpp"

namespace LRT {
	class PointLight : public LightBase {
	public:
		PointLight();
		virtual ~PointLight() override;

		virtual bool computeIllumination(
			const qbVector<double>& intersectionPoint,
			const qbVector<double>& localNormal,
			const std::vector<std::shared_ptr<LRT::ObjectBase>>& objectBase,
			const std::shared_ptr<LRT::ObjectBase>& currentObject,
			qbVector<double>& color,
			double intensity) override;
		
		

	}; // PointLight

} // LRT

#endif POINTLIGHT_H