#pragma once

#include "RayMarchBase.hpp"

namespace LRT {
	namespace RM {
		class Sphere : public RayMarchBase {
		public:
			Sphere();
			virtual ~Sphere() override;

		private:
			double objectFunc(qbVector<double>* location, qbVector<double>* params);

		}; // Sphere
	
	} // RM

} // LRT