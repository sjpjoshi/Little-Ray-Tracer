#include "ObjectBase.hpp"

// std
#include <math.h>

#define epsilon 1e-21f

LRT::ObjectBase::ObjectBase() { m_pMaterial = nullptr; } // ObjectBase
LRT::ObjectBase::~ObjectBase(){} // ~ObjectBase

bool LRT::ObjectBase::testIntersections(const Ray& castRay,qbVector<double>& intersectionPoint, qbVector<double>& localNormal, 
qbVector<double>& localColor) {return false;} // testIntersections

void LRT::ObjectBase::setTransformMatrix(const LRT::GTForm& tranformMatrix) { m_TransformMatrix = tranformMatrix; } // setTransformMatrix
bool LRT::ObjectBase::approxEqual(const double float_1, const double float_2) { return fabs(float_1 - float_2) < epsilon; } // approxEqual

bool LRT::ObjectBase::assignMaterial(const std::shared_ptr<LRT::MaterialBase>& objectMaterial) {
    m_pMaterial = objectMaterial;
    m_HasMaterial = true;
    return m_HasMaterial;

} // assignMaterial
