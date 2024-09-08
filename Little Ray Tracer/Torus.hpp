#pragma once

#include "RayMarchBase.hpp"

namespace LRT {
	namespace RM {
		class Torus : public RayMarchBase {
		public:
			Torus();
			virtual ~Torus() override;
			void setRadii(double r_1, double r_2);

		private:
			double objectFunc(qbVector<double>* location, qbVector<double>* params);
			void updateBounds();

		private:
			double m_r_1 = 1.0;
			double m_r_2 = 0.25;

		}; // Torus
	
	} // RM

} // LRT