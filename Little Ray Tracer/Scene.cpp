#include "Scene.hpp"

LRT::Scene::Scene() {


} // Scene

bool LRT::Scene::Render(Image& outputImage) {

	// image size
	int imageX = outputImage.getImageX();
	int imageY = outputImage.getImageY();

	for (int i = 0; i < imageX; ++i) {
		for (int j = 0; j < imageY; ++j) {
			double red =   (static_cast<double>(i)  /  static_cast<double> (imageX) ) * 255.0;
			double green = (static_cast<double>(j) /   static_cast<double> (imageY) ) * 255.0;
			outputImage.setPixel(i, j, red, green, 0.0);

		} // for

	} // for

	return true;

} // Render