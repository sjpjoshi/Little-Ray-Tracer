#pragma once

#ifndef RAY_H
#define RAY_H

// lin alg
#include "qbLinAlg/qbVector.h"

namespace LRT {
	class Ray {
	public:
		Ray();
		Ray(const qbVector<double> &point1, const qbVector<double> &point2);

		qbVector<double> getPoint1() const;
		qbVector<double> getPoint2() const;

	public:
		// because this is going to be an internal class, no need for the variables to be private
		qbVector<double> m_Point1{3};
		qbVector<double> m_Point2{3};
		qbVector<double> m_lineAB{3};

	}; // Ray

} // LRT

#endif