#include "Scene.hpp"

LRT::Scene::Scene() {
	// configure the camera
	m_camera.SetPosition(qbVector<double>{std::vector<double>   {0.0, -2.0, 0.0}});
	m_camera.SetLookAt  (qbVector<double>{std::vector<double>   {0.0,  0.0, 0.0}});
	m_camera.SetUp      (qbVector<double>{std::vector<double>   {0.0, 0.0,  1.0}});

	m_camera.SetHorzSize(0.25);
	m_camera.SetAspect(16.0/9.0);
	m_camera.UpdateCameraGeometry();

} // Scene

bool LRT::Scene::Render(Image& outputImage) {
	// image size
	int imageX = outputImage.getImageX();
	int imageY = outputImage.getImageY();
	
	// 32:34

	return true;

} // Render