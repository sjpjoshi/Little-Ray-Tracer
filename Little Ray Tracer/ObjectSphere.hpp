#pragma once

#ifndef OBJECTSPHERE_H
#define OBJECTSPHERE_H

#include "ObjectBase.hpp"
#include "GTFM.hpp"

namespace LRT {
	class ObjectSphere : public ObjectBase {
	public:
		ObjectSphere();
		virtual ~ObjectSphere() override;
		virtual bool testIntersections(
			const LRT::Ray& castRay,
			qbVector<double>& intersectionPoint,
			qbVector<double>& localNormal,
			qbVector<double>& localColor) override;



	}; // ObjectSphere

} // LRT

#endif