#include "Scene.hpp"

LRT::Scene::Scene() {
	// configure the camera
	m_camera.SetPosition(qbVector<double>{std::vector<double>  {0.0, -10.0, -1.0}});
	m_camera.SetLookAt(  qbVector<double>{std::vector<double>  {0.0,  0.0,  0.0}});
	m_camera.SetUp(		 qbVector<double>{std::vector<double>  {0.0,  0.0,  1.0}});

	m_camera.SetHorzSize(0.25);
	m_camera.SetAspect(16.0 / 9.0);
	m_camera.UpdateCameraGeometry();

	// Construct a test sphere.
	m_objectList.push_back(std::make_shared<LRT::ObjectSphere>(LRT::ObjectSphere()));
	m_objectList.push_back(std::make_shared<LRT::ObjectSphere>(LRT::ObjectSphere()));
	m_objectList.push_back(std::make_shared<LRT::ObjectSphere>(LRT::ObjectSphere()));

	// Construct a plane
	m_objectList.push_back(std::make_shared<LRT::ObjectPlane>(LRT::ObjectPlane())); 
	m_objectList.at(3)->m_BaseColor = qbVector<double>{ std::vector<double> {6.0, 18.0, 200.0}};

	//Define a transform for the plane
	LRT::GTForm planeMatrix;
	planeMatrix.setTransform(qbVector<double>{std::vector<double>{0.0, 0.0, 0.75}},
		qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
		qbVector<double>{std::vector<double>{4.0, 4.0, 1.0}});  
	 
	m_objectList.at(3)->setTransformMatrix(planeMatrix); 

	// Modify the spheres 
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
	m_lightList.at(0)->m_Color = qbVector<double>{ std::vector<double> {0.0, 0.0, 1.0} }; 

	m_lightList.push_back(std::make_shared<LRT::PointLight>(LRT::PointLight())); 
	m_lightList.at(1)->m_Location = qbVector<double>{ std::vector<double> {-5.0, -10.0, -5.0} };
	m_lightList.at(1)->m_Color = qbVector<double>{ std::vector<double> {1.0, 0.0, 0.0} };

	m_lightList.push_back(std::make_shared<LRT::PointLight>(LRT::PointLight()));
	m_lightList.at(2)->m_Location = qbVector<double>{ std::vector<double> { 0.0, -10.0, -5.0} }; 
	m_lightList.at(2)->m_Color = qbVector<double>{ std::vector<double> {0.0, 1.0, 0.0} }; 

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

			// test for intersections with all objects in the scene
			std::shared_ptr<LRT::ObjectBase> closestObject;
			qbVector<double> closestIntersectionPoint{ 3 };
			qbVector<double> closestLocalNormal		 { 3 };
			qbVector<double> closestLocalColor		 { 3 };
			double minDist = 1e6;
			bool intersectionFound = false;

			// Test for intersections with all objects in the scene.
			for (auto currentObject : m_objectList) {
				bool validInt = currentObject->testIntersections(cameraRay, intPoint, localNormal, localColor); 

				// If we have a valid intersection, change pixel color to red.
				if (validInt) {
					// set the flag to indicate if we found a intersection
					intersectionFound = true;

					// compute the distance between the camera and the point of intersection
					double dist = (intPoint - cameraRay.m_Point1).norm();

					// if this  object is closer to the camera than any one that we have 
					// seen before, then store a reference to it
					if (dist < minDist) {
						minDist = dist;
						closestObject = currentObject; 
						closestIntersectionPoint = intPoint;
						closestLocalNormal = localNormal;
						closestLocalColor = localColor; 

					} // if (dist < minDist)

				} // if (validInt)
				
			} // for (auto currentObject : m_objectList)

			// compute the illumination for the closest object, assuming that there was a valid intersection 
			if (intersectionFound) {
				// compute the intensity of illumination
				double intensity = 1; 
				qbVector<double> color{ 3 };
				double red = 0.0;
				double green = 0.0;
				double blue = 0.0;
				bool validIllum = false;
				bool illumFound = false;
				for (auto currentLight : m_lightList) {
					validIllum = currentLight->computeIllumination(closestIntersectionPoint, 
					closestLocalNormal, m_objectList, closestObject, color, intensity);
					
					if (validIllum) {
						illumFound = true;
						red   += color.GetElement (0) * intensity;
						green += color.GetElement (1) * intensity;
						blue  += color.GetElement (2) * intensity;


					} // if

				} // for (auto currentLight : m_lightList)

				if (illumFound) {
					red *= closestLocalColor.GetElement(0);
					green *= closestLocalColor.GetElement(1);
					blue *= closestLocalColor.GetElement(2);
					outputImage.setPixel(x, y, red, green, blue);

				} // if (illumFound)

			} // if (intersectionFound)

		} // for (int y = 0; y < ySize; ++y)

	} // for (int x = 0; x < xSize; ++x)

	std::cout << "Minimum distance: " << minDist << std::endl;
	std::cout << "Maximum distance: " << maxDist << std::endl;

	return true;

} // Render