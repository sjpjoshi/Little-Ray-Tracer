#pragma once


#include "RayMarchBase.hpp"

namespace LRT {
	namespace RM {
		class Cube : public RayMarchBase {
		public:
			Cube();
			virtual ~Cube() override;

		private:
			double ObjectFcn(qbVector<double>* location, qbVector<double>* parms);

		}; // Cube
	} // RM
} // LRT