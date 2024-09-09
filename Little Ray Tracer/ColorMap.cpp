#include "ColorMap.hpp"

LRT::Texture::ColorMap::ColorMap()  {} // ColorMap
LRT::Texture::ColorMap::~ColorMap() {} // ~ColorMap

void LRT::Texture::ColorMap::setStop(double position, const qbVector<double>& value) {
	m_StopPosition.push_back(position);
	m_StopValues.push_back(value);

} // setStop

qbVector<double> LRT::Texture::ColorMap::getColor(double position){
	// find the closest stops to the current position
	int nStops = m_StopPosition.size();
	int firstStop  = 0;
	int secondStop = 0;
	double diff    = 2.0;
	
	for (int i = 0; i < nStops; ++i) {
		double t = m_StopPosition.at(i) - position;
		if (fabs(t) < diff) {
			diff = fabs(t);
			firstStop = i;
			if (t < 0.0)
				secondStop = std::min(nStops, (i + 1));

			else if (t > 0.0)
				secondStop = std::max((i - 1), 0); 

			else
				secondStop = i;

		} // if

	} // for

	// if the position was exactly at a stop, we simply return that value
	if (firstStop == secondStop)
		return m_StopValues.at(firstStop);

	// Otherwise we need to interpolate between the first and second stop
	// make sure the stops are in the right order
	if (secondStop < firstStop)
		std::swap(firstStop, secondStop);

	// perform linear interpolation of the values between the two stops
	// equation: yi + * ( (x - xi ) * ( (yf - yi ) / (xf - xi) ) ) )
	double x = position;
	double xi = m_StopPosition.at(firstStop);
	double xf = m_StopPosition.at(secondStop);
	return  m_StopPosition.at(firstStop) + (x - xi) * ((m_StopPosition.at(secondStop) - m_StopPosition.at(firstStop)) * (1.0 / (xf - xi)));

} // getColor