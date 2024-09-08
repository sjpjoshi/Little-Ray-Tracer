#pragma once

// lin alg
#include "qbLinAlg/qbVector.h"

// Sine Distance Function namespace

namespace LRT {
	namespace RM { // Ray Marching
		namespace SDF { // Sine Distance Function
			double Sphere(const qbVector<double>& p, const qbVector<double>& center, const qbVector<double>& params);
			double Torus(const qbVector<double>& p, const qbVector<double>& center, const qbVector<double>& params);
			double Cube(const qbVector<double>& p, const qbVector<double>& center, const qbVector<double>& params);

		} // SDF

	} // RM

} // LRT