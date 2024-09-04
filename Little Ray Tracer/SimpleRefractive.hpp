#pragma once

#include "MaterialBase.hpp"

namespace LRT {
	class SimpleRefractive : public MaterialBase {
	public:
		SimpleRefractive();
		virtual ~SimpleRefractive() override;

		virtual qbVector<double> ComputeColor(const std::vector<std::shared_ptr<LRT::ObjectBase>>& objectList,
			const std::vector<std::shared_ptr<LRT::LightBase>>& lightList,
			const std::shared_ptr<LRT::ObjectBase>& currentObject,
			const qbVector<double>& intPoint, const qbVector<double>& localNormal,
			const LRT::Ray& cameraRay) override;

		qbVector<double> computeSpecular(const std::vector<std::shared_ptr<LRT::ObjectBase>>& objectList,
			const std::vector<std::shared_ptr<LRT::LightBase>>& lightList,
			const qbVector<double>& intPoint, 
			const qbVector<double>& localNormal,
			const LRT::Ray& cameraRay);

		qbVector<double> computeTransluency(const std::vector<std::shared_ptr<LRT::ObjectBase>>& objectList,
			const std::vector<std::shared_ptr<LRT::LightBase>>& lightList,
			const std::shared_ptr<LRT::ObjectBase>& currentObject,
			const qbVector<double>& intPoint, const qbVector<double>& localNormal,
			const LRT::Ray& incidentRay);

	public:
		qbVector<double> m_baseColor{ std::vector<double> {1.0, 0.0, 1.0} };
		double m_reflectivity = 0.0;
		double m_shininess = 0.0;
		double m_translucency = 0.0;
		double m_indexOfRefraction = 1.0;

	}; // SimpleRefractive

} // LRT