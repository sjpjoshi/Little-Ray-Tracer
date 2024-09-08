#include "Torus.hpp"

LRT::RM::Torus::Torus() {
	// create a function pointer for our object function
	std::function<double(qbVector<double>*, qbVector<double>*)> f = [=](qbVector<double>* location, qbVector<double>* params) {
		return this->objectFunc(location, params); 

	}; // objectFunc

	// Assign the object function 
	setObjectFunction(f); 

	// Modify the bounding box
	m_BoundingBox.setTransformMatrix(LRT::GTForm{ 
		qbVector<double> {std::vector<double> {0.0, 0.0, 0.0} }, 
		qbVector<double> {std::vector<double> {0.0, 0.0, 0.0} }, 
		qbVector<double> {std::vector<double> {1.3, 1.3, 1.3} } 

	}); // setTransformMatrix 

} // Torus

LRT::RM::Torus::~Torus() {} // ~Torus

void LRT::RM::Torus::setRadii(double r_1, double r_2) {
	m_Params.SetElement(0, r_1);
	m_Params.SetElement(1, r_2);
	updateBounds(); 

} // setRadii

void LRT::RM::Torus::updateBounds() {
	m_BoundingBox.setTransformMatrix(LRT::GTForm{
		qbVector<double> {std::vector<double> {0.0,							0.0,				 0.0} },
		qbVector<double> {std::vector<double> {0.0,							0.0,				 0.0} },
		qbVector<double> {std::vector<double> {m_r_1 + m_r_2 + 0.3, m_r_1 + m_r_2 + 0.3, m_r_2 + 0.2} } // if you rotate the torus this wont work

	}); // setTransformMatrix 

} // updateBounds

double LRT::RM::Torus::objectFunc(qbVector<double>* location, qbVector<double>* params) {
	qbVector<double> center = std::vector<double>{ 0.0, 0.0, 0.0 };
	return LRT::RM::SDF::Torus(*location, center, *params);  

} // objectFunc