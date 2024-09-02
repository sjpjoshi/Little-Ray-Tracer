#pragma once

#include "ObjectBase.hpp"
#include "GTFM.hpp"

namespace LRT {
	class Cone : public ObjectBase {
	public:
		Cone();
		virtual ~Cone();
		virtual bool testIntersections(
			const Ray& castRay,
			qbVector<double>& intersectionPoint,
			qbVector<double>& localNormal,
			qbVector<double>& localColor) override;
	private:

	}; // Cone

} // LRT