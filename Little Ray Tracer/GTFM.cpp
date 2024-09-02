#include "GTFM.hpp"

// 32:38

LRT::GTForm::GTForm() {
	m_FWDTFM.SetToIdentity();
	m_BCKTFM.SetToIdentity();

} // GTForm

LRT::GTForm::~GTForm() {} // ~GTForm

LRT::GTForm::GTForm(const qbMatrix2<double>& forward, const qbMatrix2<double>& back) {
	if (forward.GetNumRows() != 4 || forward.GetNumCols() != 4
		|| back.GetNumRows() != 4 || back.GetNumCols() != 4)
		throw std::invalid_argument("Cannot construct GTform, inputs are not all 4x4");

	m_FWDTFM = forward;
	m_BCKTFM = back;
	
} // GTForm(const qbMatrix2<double>& forward, const qbMatrix2<double>& back)

void LRT::GTForm::setTransform(const qbVector<double>& translation, const qbVector<double>& rotation, const qbVector<double>& scale) {
	// define a matrix for each component of the transform
	qbMatrix2<double> translationMatrix{ 4, 4 };
	qbMatrix2<double> rotationMatrix_X { 4, 4 };
	qbMatrix2<double> rotationMatrix_Y { 4, 4 };
	qbMatrix2<double> rotationMatrix_Z { 4, 4 };
	qbMatrix2<double> scaleMatrix	   { 4, 4 };

	// set these to identity
	translationMatrix.SetToIdentity();
	rotationMatrix_X.SetToIdentity(); 
	rotationMatrix_Y.SetToIdentity(); 
	rotationMatrix_Z.SetToIdentity();
	scaleMatrix.SetToIdentity(); 

	// populate these with the appropriate values
	translationMatrix.SetElement(0, 3, translation.GetElement(0));
	translationMatrix.SetElement(1, 3, translation.GetElement(1)); 
	translationMatrix.SetElement(2, 3, translation.GetElement(2));

	rotationMatrix_Z.SetElement(0, 0,  cos(rotation.GetElement(2)));
	rotationMatrix_Z.SetElement(0, 1, -sin(rotation.GetElement(2)));
	rotationMatrix_Z.SetElement(1, 0,  sin(rotation.GetElement(2)));
	rotationMatrix_Z.SetElement(1, 1,  cos(rotation.GetElement(2)));

	rotationMatrix_Y.SetElement(0, 0,  cos(rotation.GetElement(1)));
	rotationMatrix_Y.SetElement(0, 2,  sin(rotation.GetElement(1)));
	rotationMatrix_Y.SetElement(2, 0, -sin(rotation.GetElement(1)));
	rotationMatrix_Y.SetElement(2, 2,  cos(rotation.GetElement(1)));

	rotationMatrix_X.SetElement(1, 1,  cos(rotation.GetElement(0)));
	rotationMatrix_X.SetElement(1, 2, -sin(rotation.GetElement(0)));
	rotationMatrix_X.SetElement(2, 1,  sin(rotation.GetElement(0)));
	rotationMatrix_X.SetElement(2, 2,  cos(rotation.GetElement(0)));

	scaleMatrix.SetElement(0, 0, scale.GetElement(0));
	scaleMatrix.SetElement(1, 1, scale.GetElement(1));
	scaleMatrix.SetElement(2, 2, scale.GetElement(2)); 

	// combine to give final forward transform
	m_FWDTFM = translationMatrix * scaleMatrix * rotationMatrix_X * rotationMatrix_Y * rotationMatrix_Z; 

	// Compute the backwards
	m_BCKTFM = m_FWDTFM;
	m_BCKTFM.Inverse();

} // setTransform

qbMatrix2<double> LRT::GTForm::getForward() {
	return m_FWDTFM; 

} // getForward

qbMatrix2<double> LRT::GTForm::getBackward() {
	return m_BCKTFM;

} // getBackward

LRT::Ray LRT::GTForm::Apply(const LRT::Ray& inputRay, bool directionFlag) {
	// Create an output object
	LRT::Ray outputRay;
	if (directionFlag) {
		// apply the forward transform
		outputRay.m_Point1 = this->Apply(inputRay.m_Point1, LRT::FWDTFORM);
		outputRay.m_Point2 = this->Apply(inputRay.m_Point2, LRT::FWDTFORM);
		outputRay.m_lineAB = outputRay.m_Point2 - outputRay.m_Point1;

	} // if
	else {
		// apply the backward transform
		outputRay.m_Point1 = this->Apply(inputRay.m_Point1, LRT::BCKTFORM);
		outputRay.m_Point2 = this->Apply(inputRay.m_Point2, LRT::BCKTFORM);
		outputRay.m_lineAB = outputRay.m_Point2 - outputRay.m_Point1; 

	} // else

	return outputRay;

} // LRT::Ray LRT::GTForm::Apply

qbVector<double> LRT::GTForm::Apply(const qbVector<double>& inputVector, bool directionFlag) {
	// Convert input vector to 4-element vector
	std::vector<double> tempData{inputVector.GetElement(0),
								 inputVector.GetElement(1),
								 inputVector.GetElement(2),
								 1.0 }; // tempData

	qbVector<double> tempVector{ tempData };
	//Create a vector for the result
	qbVector<double> resultVector;

	if (directionFlag) 
		// apply the forward transform
		resultVector = m_FWDTFM * tempVector;
	else
		// apply the back transform
		resultVector = m_BCKTFM * tempVector;

	// Reform the output as a 3-element vector
	qbVector<double> outputVector {std::vector<double> { resultVector.GetElement(0), 
														 resultVector.GetElement(1),
														 resultVector.GetElement(2) }};

	return outputVector;

} // qbVector<double> LRT::GTForm::Apply

namespace LRT {

	LRT::GTForm operator*(const LRT::GTForm& lhs, const LRT::GTForm& rhs) {
		// perform the product of the two forward transform
		qbMatrix2<double> fwdResult = lhs.m_FWDTFM * rhs.m_FWDTFM; 
		// Compute the backward transform as the inverse of the forward
		qbMatrix2<double> bwdResult = fwdResult;
		bwdResult.Inverse();
		// Form the final result
		LRT::GTForm finalResult(fwdResult, bwdResult);
		return finalResult;

	} // operator*

} // LRT

LRT::GTForm LRT::GTForm::operator=(const LRT::GTForm& rhs) {
	// make sure we are not assigning ourself
	if (this != &rhs) {
		m_FWDTFM = rhs.m_FWDTFM;
		m_BCKTFM = rhs.m_BCKTFM;

	} // if
	return* this;

} // operator=

void LRT::GTForm::printMatrix(bool directionFlag) {
	if (directionFlag)
		print(m_FWDTFM);
	else
		print(m_BCKTFM);

} // printMatrix

void LRT::GTForm::print(const qbMatrix2<double>& matrix) {
	int nRows = matrix.GetNumRows();
	int nCols = matrix.GetNumCols();
	for (int i = 0; i < nRows; ++i) {
		for (int j = 0; j < nCols; ++j) {
			std::cout << std::fixed << std::setprecision(3) << matrix.GetElement(i, j) << " ";

		} // for

		std::cout << std::endl;

	} // for

} // print

void LRT::GTForm::printVector(const qbVector<double>& inputVector) {
	int nRows = inputVector.GetNumDims();
	for (int i = 0; i < nRows; ++i) 
		std::cout << std::fixed << std::setprecision(3) << inputVector.GetElement(i) << std::endl;

} // printVector