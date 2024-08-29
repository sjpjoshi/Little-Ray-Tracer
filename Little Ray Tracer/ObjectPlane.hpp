#pragma once

#include "ObjectBase.hpp"
#include "GTFM.hpp"

namespace LRT {
	class ObjectPlane : public ObjectBase {
	public:
		ObjectPlane();
		virtual ~ObjectPlane();
		virtual bool testIntersections(const LRT::Ray &castRay, 
			qbVector<double>&intersectionPoint,
			qbVector<double>& localNormal, 
			qbVector<double>& localColor) override;

	private:


	}; // ObjectPlane

} // LRT