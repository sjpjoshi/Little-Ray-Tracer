#include "Ray.hpp"

LRT::Ray::Ray(const qbVector<double>& point1, const qbVector<double>& point2) {
	m_Point1 = point1;
	m_Point2 = point2;

} // Ray

qbVector<double> LRT::Ray::getPoint1() const {
	return m_Point1; 

} // getPoint1

qbVector<double> LRT::Ray::getPoint2() const {
	return m_Point2;

} // getPoint2