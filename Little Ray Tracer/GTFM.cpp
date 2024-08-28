#include "GTFM.hpp"

// 32:38

LRT::GTForm::GTForm() {

} // GTForm

LRT::GTForm::~GTForm() {

} // ~GTForm

LRT::GTForm::GTForm(const qbMatrix2<double>& forward, const qbMatrix2<double>& back) {


} // GTForm(const qbMatrix2<double>& forward, const qbMatrix2<double>& back)

void LRT::GTForm::setTransform(const qbVector<double>& translation, const qbVector<double>& rotation, const qbVector<double>& scale) {

} // setTransform

qbMatrix2<double> LRT::GTForm::getForward() {
	return qbMatrix2<double>();

} // getForward

qbMatrix2<double> LRT::GTForm::getBackward() {
	return qbMatrix2<double>();

} // getBackward

LRT::Ray LRT::GTForm::Apply(const LRT::Ray& inputRay, bool directionFlag) {
	return LRT::Ray();

} // Apply


LRT::GTForm LRT::operator*(const LRT::GTForm& lhs, const LRT::GTForm& rhs) {
	return GTForm();

} // operator*

LRT::GTForm LRT::GTForm::operator=(const GTForm& rhs) {
	return GTForm();

} // operator=

void LRT::GTForm::printMatrix(bool directionFlag) {

} // printMatrix

void LRT::GTForm::printVector(const qbVector<double>& vector) {

} // printVector

void LRT::GTForm::print(const qbMatrix2<double>& matrix) {

} // print