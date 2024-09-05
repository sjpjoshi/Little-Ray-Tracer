#pragma once

#include "ObjectBase.hpp"
#include "GTFM.hpp"

// std
#include <array>

namespace LRT {
	class Box : public ObjectBase {
	public:

		Box();
		virtual ~Box() override;

		virtual bool testIntersections(
			const Ray& castRay,
			qbVector<double>& intersectionPoint,
			qbVector<double>& localNormal,
			qbVector<double>& localColor) override;

	private:
		std::array<double, 6> t;
		std::array<double, 6> u;
		std::array<double, 6> v;

	}; // Box

} // LRT