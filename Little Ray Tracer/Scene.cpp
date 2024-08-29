#include "Scene.hpp"

LRT::Scene::Scene() {
	// configure the camera
	m_camera.SetPosition(qbVector<double>{std::vector<double>  {0.0, -10.0, 0.0}});
	m_camera.SetLookAt(  qbVector<double>{std::vector<double>  {0.0,  0.0,  0.0}});
	m_camera.SetUp(		 qbVector<double>{std::vector<double>  {0.0,  0.0,  1.0}});

	m_camera.SetHorzSize(0.25);
	m_camera.SetAspect(16.0 / 9.0);
	m_camera.UpdateCameraGeometry();

	// Construct a test sphere.
	m_objectList.push_back(std::make_shared<LRT::ObjectSphere>(LRT::ObjectSphere()));
	m_objectList.push_back(std::make_shared<LRT::ObjectSphere>(LRT::ObjectSphere()));
	m_objectList.push_back(std::make_shared<LRT::ObjectSphere>(LRT::ObjectSphere()));

	// Modify the spheres.
	LRT::GTForm testMatrix1, testMatrix2, testMatrix3;
	testMatrix1.setTransform(qbVector<double>{std::vector<double>{-1.5, 0.0, 0.0}},
		qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
		qbVector<double>{std::vector<double>{0.5, 0.5, 0.75}});

	testMatrix2.setTransform(qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
		qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
		qbVector<double>{std::vector<double>{0.75, 0.5, 0.5}});

	testMatrix3.setTransform(qbVector<double>{std::vector<double>{1.5, 0.0, 0.0}},
		qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
		qbVector<double>{std::vector<double>{0.75, 0.75, 0.75}});

	m_objectList.at(0)->setTransformMatrix(testMatrix1);
	m_objectList.at(1)->setTransformMatrix(testMatrix2);
	m_objectList.at(2)->setTransformMatrix(testMatrix3);

	m_objectList.at(0)->m_BaseColor = qbVector<double>{ std::vector<double>{64.0, 128.0, 200.0} };
	m_objectList.at(1)->m_BaseColor = qbVector<double>{ std::vector<double>{255.0, 128.0, 0.0} }; 
	m_objectList.at(2)->m_BaseColor = qbVector<double>{ std::vector<double>{255.0, 200.0, 0.0} };

	// Construct a test light.
	m_lightList.push_back(std::make_shared<LRT::PointLight>(LRT::PointLight()));
	m_lightList.at(0)->m_Location = qbVector<double>{ std::vector<double> {5.0, -10.0, -5.0} };
	m_lightList.at(0)->m_Color = qbVector<double>{ std::vector<double> {255.0, 255.0, 255.0} };

} // Scene

bool LRT::Scene::Render(Image& outputImage) {
	// Get the dimensions of the output image.
	int xSize = outputImage.getImageX();
	int ySize = outputImage.getImageY();

	// Loop over each pixel in our image.
	LRT::Ray cameraRay;
	qbVector<double> intPoint(3);
	qbVector<double> localNormal(3);
	qbVector<double> localColor(3);
	double xFact = 1.0 / (static_cast<double>(xSize) / 2.0);
	double yFact = 1.0 / (static_cast<double>(ySize) / 2.0);
	double minDist = 1e6;
	double maxDist = 0.0;
	for (int x = 0; x < xSize; ++x) {
		for (int y = 0; y < ySize; ++y) {
			// Normalize the x and y coordinates.
			double normX = (static_cast<double>(x) * xFact) - 1.0;
			double normY = (static_cast<double>(y) * yFact) - 1.0;

			// Generate the ray for this pixel.
			m_camera.GenerateRay(normX, normY, cameraRay);

			// Test for intersections with all objects in the scene.
			for (auto currentObject : m_objectList) {
				bool validInt = currentObject->testIntersections(cameraRay, intPoint, localNormal, localColor);
				// If we have a valid intersection, change pixel color to red.
				if (validInt) {
					// Compute intensity of illumination.
					double intensity = 1000;
					qbVector<double> color{ 3 };
					bool validIllum = false;
					for (auto currentLight : m_lightList)
						validIllum = currentLight->computeIllumination(intPoint, localNormal, m_objectList, currentObject, color, intensity); 
					

					// Compute the distance between the camera and the point of intersection.
					double dist = (intPoint - cameraRay.m_Point1).norm();
					if (dist > maxDist)
						maxDist = dist;

					if (dist < minDist)
						minDist = dist;

					if (validIllum)
						outputImage.setPixel(x, y, localColor.GetElement(0) * intensity,
							localColor.GetElement(1) * intensity,
							localColor.GetElement(2) * intensity);
					
					//else	
						// Leave this pixel unchanged.
						//outputImage.setPixel(x, y, 0.0, 0.0, 0.0);
					
				} // if

				//else
					// Leave this pixel unchanged.
					//outputImage.setPixel(x, y, 0.0, 0.0, 0.0);
				
			} // for

		} // for

	} // for

	std::cout << "Minimum distance: " << minDist << std::endl;
	std::cout << "Maximum distance: " << maxDist << std::endl;

	return true;

} // Render