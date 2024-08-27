#include "ObjectBase.hpp"

// std
#include <math.h>

#define epsilon 1e-21f

LRT::ObjectBase::ObjectBase() {} // ObjectBase
LRT::ObjectBase::~ObjectBase(){} // ~ObjectBase
bool LRT::ObjectBase::testIntersections(const Ray& castRay,qbVector<double>& intersectionPoint, qbVector<double>& localNormal, 
qbVector<double>& localColor) {return false; } // testIntersections
bool LRT::ObjectBase::approxEqual(const double float_1, const double float_2) { return fabs(float_1 - float_2) < epsilon; } // approxEqual