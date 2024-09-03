#include "Flat.hpp"

LRT::Texture::Flat::Flat()  {
	m_Color = qbVector<double>{ std::vector<double> {1.0, 0.0, 0.0, 1.0} }; 

} // Flat

LRT::Texture::Flat::~Flat() {} // ~Flat

qbVector<double> LRT::Texture::Flat::getColor(const qbVector<double>& uvCoords) {
	return m_Color;

} // getColor

void LRT::Texture::Flat::setColor(const qbVector<double>& inputColor) {
	m_Color = inputColor;

} // setColor