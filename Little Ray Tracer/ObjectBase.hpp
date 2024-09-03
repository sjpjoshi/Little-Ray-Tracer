#pragma once

#ifndef OBJECTBASE_H
#define OBJECTBASE_H

#include "Ray.hpp"
#include "GTFM.hpp"

// std
#include <memory>

// lin alg
#include "./qbLinAlg/qbVector.h"

namespace LRT {

	// forward declare our material baseclase, to be overwritten later
	class MaterialBase;

	class ObjectBase {
	public:
		ObjectBase();
		virtual ~ObjectBase();
		virtual bool testIntersections(
			const Ray &castRay, 
			qbVector<double>&intersectionPoint, 
			qbVector<double> &localNormal, 
			qbVector<double>& localColor);

		void setTransformMatrix(const LRT::GTForm& tranformMatrix);
		bool approxEqual(const double float_1, const double float_2);
		bool assignMaterial(const std::shared_ptr<LRT::MaterialBase>& objectMaterial);

	public:
		qbVector<double> m_BaseColor{ 3 };
		LRT::GTForm m_TransformMatrix;
		std::shared_ptr<LRT::MaterialBase> m_pMaterial;		
		bool m_HasMaterial = false;
		qbVector<double> m_UVCoords{ 2 };

	}; // ObjectBase

} // LRT

#endif