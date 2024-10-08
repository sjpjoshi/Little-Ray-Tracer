#include "Ray.hpp"

LRT::Ray::Ray() {
	m_Point1 = qbVector<double>{ std::vector<double> {0.0, 0.0, 0.0} };
	m_Point2 = qbVector<double>{ std::vector<double> {0.0, 0.0, 1.0} };
	m_lineAB = m_Point2 - m_Point1;

} // Ray

LRT::Ray::Ray(const qbVector<double>& point1, const qbVector<double>& point2) {
	m_Point1 = point1;
	m_Point2 = point2;
	m_lineAB = m_Point2 - m_Point1;

} // Ray

qbVector<double> LRT::Ray::getPoint1() const {
	return m_Point1; 

} // getPoint1

qbVector<double> LRT::Ray::getPoint2() const {
	return m_Point2;

} // getPoint2