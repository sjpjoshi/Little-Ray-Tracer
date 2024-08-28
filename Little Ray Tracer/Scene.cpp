#include "Scene.hpp"

LRT::Scene::Scene() {
	// configure the camera
	m_camera.SetPosition(qbVector<double>{std::vector<double>  {0.0,  -10.0, 0.0}});
	m_camera.SetLookAt  (qbVector<double>{std::vector<double>  {0.0,  0.0,  0.0}});
	m_camera.SetUp      (qbVector<double>{std::vector<double>  {0.0,  0.0,  1.0}});

	m_camera.SetHorzSize(0.25);
	m_camera.SetAspect(16.0/9.0);
	m_camera.UpdateCameraGeometry();

	// construct a test sphere
	m_objectList.push_back(std::make_shared<LRT::ObjectSphere>(LRT::ObjectSphere()));

	// construct a test light
	m_lightList.push_back(std::make_shared<LRT::PointLight>(LRT::PointLight()));
	m_lightList.at(0)->m_Location = qbVector<double>{ std::vector<double> {5.0,   -10.0, -5.0}  };
	m_lightList.at(0)->m_Color = qbVector<double>   { std::vector<double> {255.0, 255.0, 255.0} }; 

} // Scene

bool LRT::Scene::Render(Image& outputImage) {
	// image size
	int imageX = outputImage.getImageX();
	int imageY = outputImage.getImageY();
	
	// Loop over each pixel in our image
	LRT::Ray cameraRay;
	qbVector<double> intersectionPoint( 3 );
	qbVector<double> localNormal	  ( 3 );
	qbVector<double> localColor		  ( 3 );

	double xScaler = 1.0 / (static_cast<double>(imageX) / 2.0);
	double yScaler = 1.0 / (static_cast<double>(imageY) / 2.0);
	
	double minDistance = 1e6;
	double maxDistance = 0.0;

	for (int i = 0; i < imageX; ++i) {
		for (int j = 0; j < imageY; ++j) { 
			// Normalize the x and y coordinates
			double normalX = (static_cast<double>(i) * xScaler) - 1.0;
			double normalY = (static_cast<double>(j) * yScaler) - 1.0;
			
			// generate the ray for this pixel
			m_camera.GenerateRay(normalX, normalY, cameraRay);

			// test for intersection with all objects in the scene
			for (auto currentObject : m_objectList) {
				bool validTest = currentObject -> testIntersections(cameraRay, intersectionPoint, localNormal, localColor);

				// if we have a valid intersection, change pixel color to red
				if (validTest) {

					// Compute the intensity of the illumination
					double intensity = 100.0;
					qbVector<double> color{ 3 };
					bool validIllumination = false;
					for (auto currentLight : m_lightList) {
						validIllumination = currentLight->computeIllumination(
							intersectionPoint, 
							localNormal,  
							m_objectList, 
							currentObject, 
							color,
							intensity);

					} // for
					// compute the distance between the camera and the point of intersection
					double dist = (intersectionPoint - cameraRay.m_Point1).norm();
					if (dist > maxDistance)
						maxDistance = dist;

					if (dist < minDistance)
						minDistance = dist;

					//outputImage.setPixel(i, j, 255.0 - ((dist - 9.0) / 0.94605) * 255.0, 0.0, 0.0);
					if (validIllumination)
						outputImage.setPixel(i, j, 255.0 * intensity, 0.0, 0.0);

					else
						outputImage.setPixel(i, j, 0.0, 0.0, 0.0);

				} // if
				else
					outputImage.setPixel(i, j, 0.0, 0.0, 0.0);

			} // for
					
		} // for

	} // for

	std::cout << "Min dist: " << minDistance << std::endl;
	std::cout << "Max dist: " << maxDistance << std::endl;


	return true;

} // Render