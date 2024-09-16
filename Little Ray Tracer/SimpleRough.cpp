#include "SimpleRough.hpp"

LRT::Normal::SimpleRough::SimpleRough() {
	std::random_device randDev;
	std::seed_seq seed{ randDev(), randDev(), randDev(), randDev() };
	p_randGen_ = std::make_shared<std::mt19937>(seed);

} // SimpleRough

LRT::Normal::SimpleRough::~SimpleRough() {} // ~SimpleRough

qbVector<double> LRT::Normal::SimpleRough::ComputePerturbation(const qbVector<double>& normal, const qbVector<double>& uvCoords) {
	std::uniform_real_distribution<double> randomDist(-amplitudeScale_, amplitudeScale_);
	double x = randomDist(*p_randGen_);
	double y = randomDist(*p_randGen_); 
	double z = randomDist(*p_randGen_);

	//double x = uvCoords.GetElement(0) * 0.5;
	//double y = 0.0;
	//double z = 0.0;

	qbVector<double> perturbation = std::vector<double>{ x, y, z };
	return PerturbNormal(normal, perturbation);

} // ComputePerturbation