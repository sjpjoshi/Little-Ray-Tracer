#include "Cube.hpp"

// Constructor.
LRT::RM::Cube::Cube() {
	// Create a function pointer for our object function.
	std::function<double(qbVector<double>*, qbVector<double>*)> f = [=](qbVector<double>* location, qbVector<double>* parms) {
		return this->ObjectFcn(location, parms);

	}; // function

	// Assign the object function.
	setObjectFunction(f);

	// Modify the bounding box.
	m_BoundingBox.setTransformMatrix(LRT::GTForm{ qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
												  qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
											      qbVector<double>{std::vector<double>{1.2, 1.2, 1.2}} });

} // Cube

// Destructor.
LRT::RM::Cube::~Cube() {} // ~Cube

// The private object function.
double LRT::RM::Cube::ObjectFcn(qbVector<double>* location, qbVector<double>* parms) {
	qbVector<double> center = std::vector<double>{ 0.0, 0.0, 0.0 };
	qbVector<double> intParms = std::vector<double>{ 1.0, 1.0, 1.0 };
	return LRT::RM::SDF::Cube(*location, center, intParms);

} // ObjectFcn