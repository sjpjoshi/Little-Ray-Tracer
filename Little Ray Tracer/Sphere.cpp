#include "Sphere.hpp"


LRT::RM::Sphere::Sphere() {
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
		qbVector<double> {std::vector<double> {1.2, 1.2, 1.2} }

	}); // setTransformMatrix

} // Sphere

LRT::RM::Sphere::~Sphere() {} // ~Sphere 

double LRT::RM::Sphere::objectFunc(qbVector<double>* location, qbVector<double>* params) {
	qbVector<double> center = std::vector<double>{ 0.0, 0.0, 0.0 };
	qbVector<double> intParams = std::vector<double>{ 1.0, 0.0, 0.0 };

	return LRT::RM::SDF::Sphere(*location, center, intParams); 

} // objectFunc