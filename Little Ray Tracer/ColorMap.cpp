#include "ColorMap.hpp"

LRT::Texture::ColorMap::ColorMap()  {} // ColorMap
LRT::Texture::ColorMap::~ColorMap() {} // ~ColorMap

void LRT::Texture::ColorMap::setStop(double position, const qbVector<double>& value) {
	m_StopPosition.push_back(position);
	m_StopValues.push_back(value);

} // setStop

qbVector<double> LRT::Texture::ColorMap::getColor(double position){
	// Find the closest stops to the current position.
	int numStops = m_StopPosition.size(); 
	int firstStop = 0; 
	int secondStop = 0; 
	double diff = 2.0;
	for (int i = 0; i < numStops; ++i)  {
		double t = m_StopPosition.at(i) - position; 
		if (fabs(t) < diff) {
			diff = fabs(t); 
			firstStop = i; 
			if (t < 0.0)
				secondStop = std::min(numStops, (i + 1)); 
			else if (t > 0.0)
				secondStop = std::max((i - 1), 0); 
			else 
				secondStop = i; 

		} // if

	} // for

	// If the position was exactly at a stop, we simply return that value.
	if (firstStop == secondStop) 
		return m_StopValues.at(firstStop); 

	// Otherwise we need to interpolate between the first and second stops.
	// Make sure the stops are in the right order.
	if (secondStop < firstStop) 
		std::swap(firstStop, secondStop); 

	// Perform linear interpolation of the values between the two stops.
	// y0 + ((x - x0)*((y1 - y0)/(x1 - x0)))
	double x = position; 
	double x0 = m_StopPosition.at(firstStop); 
	double x1 = m_StopPosition.at(secondStop); 
	return m_StopValues.at(firstStop) + (x - x0) * ((m_StopValues.at(secondStop) - m_StopValues.at(firstStop)) * (1.0 / (x1 - x0))); 

} // getColor