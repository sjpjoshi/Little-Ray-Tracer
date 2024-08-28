#include "LightBase.hpp"

LRT::LightBase::LightBase() {} // LightBase
LRT::LightBase::~LightBase() {} // ~LightBase

bool LRT::LightBase::computeIllumination(const qbVector<double>& intersectionPoint, const qbVector<double>& localNormal, 
										 const std::vector<std::shared_ptr<LRT::ObjectBase>>& objectBase,
										 const std::shared_ptr<LRT::ObjectBase>& currentObject, 
										 qbVector<double>& color, double intensity)  { return false; } // computeIllumination