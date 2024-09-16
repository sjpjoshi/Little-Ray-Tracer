#include "Constants.hpp"

LRT::Normal::Constant::Constant()  {} // Constant
LRT::Normal::Constant::~Constant() {} // ~Constant

qbVector<double> LRT::Normal::Constant::ComputePerturbation(const qbVector<double>& normal, const qbVector<double>& uvCoords) {
	return PerturbNormal(normal, displacement_);

} // ComputePerturbation