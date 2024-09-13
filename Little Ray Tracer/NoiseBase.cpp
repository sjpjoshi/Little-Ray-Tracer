#include "NoiseBase.hpp"

LRT::Noise::NoiseBase::NoiseBase() {

} // NoiseBase

LRT::Noise::NoiseBase::~NoiseBase() {

} // ~NoiseBase

double LRT::Noise::NoiseBase::getValue(double u, double v) {
	return 0.0;

} // getValue

double LRT::Noise::NoiseBase::Lerp(double v1, double v2, double iPos) {
	/* Note that here we are assuming the iPos will always be
		between 0 and 1. If we can't make that assumption, then
		we should ensure that it is between 0 and 1 before using
		it to compute fade. */

	// Smoothstep fade.
	double fade = iPos * iPos * (3 - 2 * iPos);

	// Linear fade.
	//double fade = iPos;

	// Implement the actual linear interpolation.
	return v1 + fade * (v2 - v1);

} // Lerp

void LRT::Noise::NoiseBase::SetupGrid(int scale) {
	scale_ = scale;

} // SetupGrid