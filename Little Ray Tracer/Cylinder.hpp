#pragma once

#include "ObjectBase.hpp"
#include "GTFM.hpp"

namespace LRT {
	class Cylinder : public ObjectBase {
	public:
		Cylinder();
		virtual ~Cylinder();
		virtual bool testIntersections(
			const Ray& castRay,
			qbVector<double>& intersectionPoint,
			qbVector<double>& localNormal,
			qbVector<double>& localColor) override;

	private:

	}; // Cylinder

} // LRT