#pragma once

#include "ObjectBase.hpp"
#include "Box.hpp"
#include "SDF.hpp"

// std
#include <functional>

namespace LRT {
	namespace RM {
		class RayMarchBase : public ObjectBase {
		public:
			RayMarchBase();
			virtual ~RayMarchBase() override;

			virtual bool testIntersections(
				const Ray& castRay,
				qbVector<double>& intersectionPoint,
				qbVector<double>& localNormal,
				qbVector<double>& localColor) override;

			void setObjectFunction( std::function<double(qbVector<double>*, qbVector<double>*)> objectFunction );
			double evaluateSDF(qbVector<double>* location, qbVector<double>* params);

		public:
			LRT::Box m_BoundingBox = LRT::Box();
			qbVector<double> m_Params{ 3 };

		private:
			std::function<double(qbVector<double>*, qbVector<double>*)> m_ObjectFunction;

			bool m_HaveObjectFcn = false;
			double m_Epsilon;
			int m_MaxSteps;

			const double m_h = 0.0001; // half-step of Newton method
			qbVector<double> m_xDisp{ std::vector<double> {m_h, 0.0, 0.0} };
			qbVector<double> m_yDisp{ std::vector<double> {0.0, m_h, 0.0} };
			qbVector<double> m_zDisp{ std::vector<double> {0.0, 0.0, m_h} };


		}; // RayMarchBase

	} // RM

} // LRT