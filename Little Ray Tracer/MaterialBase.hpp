#pragma once

#include "ObjectBase.hpp"
#include "LightBase.hpp"
#include "Ray.hpp"

// std
#include <memory>

// lin alg
#include "qbLinAlg/qbVector.h"

namespace LRT {
	class MaterialBase {
	public:
		MaterialBase();
		virtual ~MaterialBase();

		virtual qbVector<double> ComputeColor(const std::vector<std::shared_ptr<LRT::ObjectBase>>& objectList,
			const std::vector<std::shared_ptr<LRT::LightBase>>& lightList,
			const std::shared_ptr<LRT::ObjectBase>& currentObject,
			const qbVector<double>& intPoint, const qbVector<double>& localNormal,
			const LRT::Ray& cameraRay);

		static qbVector<double> computeDiffuseColor(const std::vector<std::shared_ptr<LRT::ObjectBase>>& objectList,
			const std::vector<std::shared_ptr<LRT::LightBase>>& lightList,
			const std::shared_ptr<LRT::ObjectBase>& currentObject,
			const qbVector<double>& intPoint, const qbVector<double>& localNormal,
			const qbVector<double>& baseColor);

		// Function to cast a ray into the scene.
		bool CastRay(const LRT::Ray& castRay, const std::vector<std::shared_ptr<LRT::ObjectBase>>& objectList,
			const std::shared_ptr<LRT::ObjectBase>& thisObject,
			std::shared_ptr<LRT::ObjectBase>& closestObject,
			qbVector<double>& closestIntPoint, qbVector<double>& closestLocalNormal,
			qbVector<double>& closestLocalColor);

		qbVector<double> computeReflectionColor(const std::vector<std::shared_ptr<LRT::ObjectBase>>& objectList,
			const std::vector<std::shared_ptr<LRT::LightBase>>& lightList,
			const std::shared_ptr<LRT::ObjectBase>& currentObject,
			const qbVector<double>& intPoint, const qbVector<double>& localNormal,
			const LRT::Ray& incidentRay);

	public:
		inline static int m_MaxReflectionRays;
		inline static int m_ReflectionRayCount;

	private:

		
	}; // MaterialBase

} // LRT