#pragma once
#ifndef LIGHTBASE_H
#define LIGHTBASE_H

#include "Ray.hpp"
#include "ObjectBase.hpp"

// std
#include <memory>

// lin alg
#include "qbLinAlg/qbVector.h"

namespace LRT {
	class LightBase {
	public:
		LightBase();
		virtual ~LightBase();

		virtual bool computeIllumination(
			const qbVector<double> &intersectionPoint, 
			const qbVector<double>& localNormal, 
			const std::vector<std::shared_ptr<LRT::ObjectBase>> & objectBase,
			const std::shared_ptr<LRT::ObjectBase> & currentObject,
			qbVector<double>& color,
			double intensity);

	public:
		qbVector<double> m_Color	{ 3 };
		qbVector<double> m_Location { 3 };
		double			 m_Intensity;

	}; // LightBase

} // LRT

#endif