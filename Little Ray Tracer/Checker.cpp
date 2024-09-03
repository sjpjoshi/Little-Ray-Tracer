#include "Checker.hpp"

LRT::Texture::Checker::Checker() {
	m_Color1 = qbVector<double>{ std::vector<double>{1.0, 1.0, 1.0, 1.0} }; 
	m_Color2 = qbVector<double>{ std::vector<double>{0.2, 0.2, 0.2, 1.0} };

} // Checker

LRT::Texture::Checker::~Checker() {} //~Checker 

qbVector<double> LRT::Texture::Checker::getColor(const qbVector<double>& uvCoords) {
	// Apply the local transform to the UV coords
	qbVector<double> inputLocation = uvCoords;
	qbVector<double> newLoc = applyTransform(inputLocation); // new location
	double newU = newLoc.GetElement(0);
	double newV = newLoc.GetElement(1);

	qbVector<double> localColor{ 4 };
	int check = static_cast<int>(floor(newU)) + static_cast<int>(floor(newV)); 
	if ((check % 2) == 0)
		localColor = m_Color1;
	else
		localColor = m_Color2;

	return localColor;

} // getColor

void LRT::Texture::Checker::setColor(const qbVector<double>& inputColor1, const qbVector<double>& inputColor2) {
	m_Color1 = inputColor1; 
	m_Color2 = inputColor2; 

} // setColor