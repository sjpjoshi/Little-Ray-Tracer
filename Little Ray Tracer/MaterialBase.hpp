#pragma once

#include "ObjectBase.hpp"
#include "LightBase.hpp"
#include "Ray.hpp"
#include "TextureBase.hpp"

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

		void assignTexture(const std::shared_ptr<LRT::Texture::TextureBase>& inputTexture);

	public:
		inline static int m_MaxReflectionRays;
		inline static int m_ReflectionRayCount;
		std::vector<std::shared_ptr<LRT::Texture::TextureBase>> m_TextureList;

		bool m_HasTexture = false;

	private:

		
	}; // MaterialBase

} // LRT