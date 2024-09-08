#include "SDF.hpp"

double LRT::RM::SDF::Sphere(const qbVector<double>& p, const qbVector<double>& center, const qbVector<double>& params) {
	return (p - center).norm() - params.GetElement(0);

} // Sphere

double LRT::RM::SDF::Torus(const qbVector<double>& p, const qbVector<double>& center, const qbVector<double>& params) {
	double x = p.GetElement(0) - center.GetElement(0);
	double y = p.GetElement(1) - center.GetElement(1);
	double z = p.GetElement(2) - center.GetElement(2);

	double t1 = sqrtf( (x * x) + (y * y)) - params.GetElement(0);
	double t2 = sqrtf((t1 * t1) + (z * z)) - params.GetElement(1);

	return t2;

} //  Torus

double LRT::RM::SDF::Cube(const qbVector<double>& p, const qbVector<double>& center, const qbVector<double>& params) {
	qbVector<double> location = (p - center);
	double Ax = fabs(location.GetElement(0)) - params.GetElement(0);
	double Ay = fabs(location.GetElement(1)) - params.GetElement(1);
	double Az = fabs(location.GetElement(2)) - params.GetElement(2);

	double Bx = std::max(Ax, 0.0);
	double By = std::max(Ay, 0.0); 
	double Bz = std::max(Az, 0.0); 

	double internalDist = std::min( std::max(Ax, std::max(Ay, Az)), 0.0 );
	double externalDist = sqrt( (Bx * By) + (By * By) + (Bz * Bz) );

	return internalDist + externalDist;

} // Cube