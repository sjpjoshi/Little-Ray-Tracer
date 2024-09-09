#include "Checker.hpp"
#include "Flat.hpp"

LRT::Texture::Checker::Checker() {
	LRT::Texture::Flat color1;
	LRT::Texture::Flat color2;

	color1.setColor(qbVector<double> {std::vector<double> {1.0, 1.0, 1.0, 1.0} });
	color2.setColor(qbVector<double> {std::vector<double> {0.2, 0.2, 0.2, 1.0} });

	m_pColor1 = std::make_shared<LRT::Texture::Flat>(color1);
	m_pColor2 = std::make_shared<LRT::Texture::Flat>(color2);

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
		localColor = m_pColor1 -> getColor(uvCoords);
	else
		localColor = m_pColor2 -> getColor(uvCoords); 

	return localColor;

} // getColor

void LRT::Texture::Checker::setColor(const qbVector<double>& inputColor1, const qbVector<double>& inputColor2) {
	auto color1 = std::make_shared<LRT::Texture::Flat>(LRT::Texture::Flat());
	auto color2 = std::make_shared<LRT::Texture::Flat>(LRT::Texture::Flat()); 

	color1->setColor(inputColor1); 
	color2->setColor(inputColor2);

	m_pColor1 = color1;
	m_pColor2 = color2;

} // setColor

void LRT::Texture::Checker::setColor(const std::shared_ptr<LRT::Texture::TextureBase>& inputColor1, const std::shared_ptr<LRT::Texture::TextureBase>& inputColor2) {
	m_pColor1 = inputColor1;
	m_pColor2 = inputColor2;

} // setColor