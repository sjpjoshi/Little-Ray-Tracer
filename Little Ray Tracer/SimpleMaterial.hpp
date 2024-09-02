#pragma once

#include "MaterialBase.hpp"

namespace LRT {
	
	class SimpleMaterial : public MaterialBase {
	public:
		SimpleMaterial();
		virtual ~SimpleMaterial() override;

		virtual qbVector<double> ComputeColor(const std::vector<std::shared_ptr<LRT::ObjectBase>>& objectList,
			const std::vector<std::shared_ptr<LRT::LightBase>>& lightList,
			const std::shared_ptr<LRT::ObjectBase>& currentObject,
			const qbVector<double>& intPoint, const qbVector<double>& localNormal,
			const LRT::Ray& cameraRay) override;

		qbVector<double> computeSpecular(const std::vector<std::shared_ptr<LRT::ObjectBase>>& objectList,
			const std::vector<std::shared_ptr<LRT::LightBase>>& lightList,
			const qbVector<double>& intPoint, const qbVector<double>& localNormal,
			const LRT::Ray& cameraRay);
	
	public:
		qbVector<double> m_BaseColor{ std::vector<double>{1.0, 0.0, 1.0} };
		double m_Reflectivity = 0.0;
		double m_Shininess = 0.0;

	}; // SimpleMaterials

} // LRT