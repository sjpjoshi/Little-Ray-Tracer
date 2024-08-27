#pragma once

#ifndef OBJECTBASE_H
#define OBJECTBASE_H

#include "Ray.hpp"

// lin alg
#include "./qbLinAlg/qbVector.h"

namespace LRT {
	class ObjectBase {
	public:
		ObjectBase();
		virtual ~ObjectBase();
		virtual bool testIntersections(
			const Ray &castRay, 
			qbVector<double>&intersectionPoint, 
			qbVector<double> &localNormal, 
			qbVector<double>& localColor);

		bool approxEqual(const double float_1, const double float_2);

	public:
		qbVector<double> m_BaseColor{ 3 };


	}; // ObjectBase

} // LRT

#endif