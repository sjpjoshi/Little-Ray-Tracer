#include "Scene.hpp"
#include "MaterialBase.hpp"
#include "SimpleMaterial.hpp"

LRT::Scene::Scene() {

	// create some materials
	auto testMaterial = std::make_shared <LRT::SimpleMaterial>(LRT::SimpleMaterial());
	auto testMaterial2 = std::make_shared <LRT::SimpleMaterial>(LRT::SimpleMaterial());
	auto testMaterial3 = std::make_shared <LRT::SimpleMaterial>(LRT::SimpleMaterial());
	auto floorMaterial = std::make_shared <LRT::SimpleMaterial>(LRT::SimpleMaterial());


	// Setup the materials
	testMaterial->m_BaseColor = qbVector<double>{ std::vector<double> {0.25, 0.5, 0.8} };
	testMaterial->m_Reflectivity = 0.1;
	testMaterial->m_Shininess = 10.0;

	testMaterial2->m_BaseColor = qbVector<double>{ std::vector<double> {1.0, 0.5, 0.0} };
	testMaterial2->m_Reflectivity = 0.75;
	testMaterial2->m_Shininess = 10.0;

	testMaterial3->m_BaseColor = qbVector<double>{ std::vector<double> {1.0, 0.8, 0.0} };
	testMaterial3->m_Reflectivity = 0.25;
	testMaterial3->m_Shininess = 10.0;

	floorMaterial->m_BaseColor = qbVector<double>{ std::vector<double> {1.0, 1.0, 1.0} }; 
	floorMaterial->m_Reflectivity = 0.5; 
	floorMaterial->m_Shininess = 10.0;


	// configure the camera
	m_camera.SetPosition(qbVector<double>{std::vector<double> {0.0, -10.0, -2.0}});
	m_camera.SetLookAt(qbVector<double>{std::vector<double> {0.0, 0.0, 0.0}});; 
	m_camera.SetUp(qbVector<double>{std::vector<double> {0.0, 0.0, 1.0}}); 

	m_camera.SetHorzSize(0.25);
	m_camera.SetAspect(16.0 / 9.0);
	m_camera.UpdateCameraGeometry();

	// Construct a test sphere.
	m_objectList.push_back(std::make_shared<LRT::ObjectSphere>(LRT::ObjectSphere()));
	m_objectList.push_back(std::make_shared<LRT::ObjectSphere>(LRT::ObjectSphere()));
	m_objectList.push_back(std::make_shared<LRT::ObjectSphere>(LRT::ObjectSphere()));

	// Construct a plane
	m_objectList.push_back(std::make_shared<LRT::ObjectPlane>(LRT::ObjectPlane())); 
	m_objectList.at(3)->m_BaseColor = qbVector<double>{ std::vector<double> {0.5, 0.5, 0.5} };

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
		qbVector<double>{std::vector<double>{0.5, 0.5, 0.5}});

	testMatrix2.setTransform(qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
		qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
		qbVector<double>{std::vector<double>{0.5, 0.5, 0.5}});

	testMatrix3.setTransform(qbVector<double>{std::vector<double>{1.5, 0.0, 0.0}},
		qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}}, 
		qbVector<double>{std::vector<double>{0.5, 0.5, 0.5}}); 


	m_objectList.at(0)->setTransformMatrix(testMatrix1); 
	m_objectList.at(1)->setTransformMatrix(testMatrix2); 
	m_objectList.at(2)->setTransformMatrix(testMatrix3); 

	m_objectList.at(0)->m_BaseColor = qbVector<double>{ std::vector<double> {0.25, 0.5, 0.8} };
	m_objectList.at(1)->m_BaseColor = qbVector<double>{ std::vector<double> {1.0, 0.5, 0.0}  };
	m_objectList.at(2)->m_BaseColor = qbVector<double>{ std::vector<double> {1.0, 0.8, 0.0}  };

	// Assign materials to objects
	m_objectList.at(0)->assignMaterial(testMaterial3);
	m_objectList.at(1)->assignMaterial(testMaterial2);
	m_objectList.at(2)->assignMaterial(testMaterial);
	m_objectList.at(3)->assignMaterial(floorMaterial);

	// Construct a test light.
	m_lightList.push_back(std::make_shared<LRT::PointLight>(LRT::PointLight()));
	m_lightList.at(0)->m_Location = qbVector<double>{ std::vector<double> {5.0, -10.0, -5.0} };
	m_lightList.at(0)->m_Color = qbVector<double>{ std::vector<double> {0.0, 0.0, 1.0} };

	m_lightList.push_back(std::make_shared<LRT::PointLight>(LRT::PointLight())); 
	m_lightList.at(1)->m_Location = qbVector<double>{ std::vector<double> {-5.0, -10.0, -5.0} };
	m_lightList.at(1)->m_Color = qbVector<double>{ std::vector<double> {1.0, 0.0, 0.0} };

	m_lightList.push_back(std::make_shared<LRT::PointLight>(LRT::PointLight()));
	m_lightList.at(2)->m_Location = qbVector<double>{ std::vector<double> {0.0, -10.0, -5.0} };
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
	for (int y = 0; y < ySize; ++y) {
		// display progress
		std::cout << "procesing line " << y << " of " << ySize << std::endl;
		for (int x = 0; x < xSize; ++x) {
			// Normalize the x and y coordinates.
			double normX = (static_cast<double>(x) * xFact) - 1.0;
			double normY = (static_cast<double>(y) * yFact) - 1.0;

			// Generate the ray for this pixel.
			m_camera.GenerateRay(normX, normY, cameraRay);

			// test for intersections with all objects in the scene
			std::shared_ptr<LRT::ObjectBase> closestObject;
			qbVector<double> closestIntPoint{ 3 };
			qbVector<double> closestLocalNormal{ 3 };
			qbVector<double> closestLocalColor{ 3 };

			bool intersectionFound = CastRay(cameraRay, closestObject, closestIntPoint, closestLocalNormal, closestLocalColor);

			// compute the illumination for the closest object, assuming that there was a valid intersection 
			if (intersectionFound) {
				
				// check if the object has a material
				if (closestObject->m_HasMaterial) {

					LRT::MaterialBase::m_ReflectionRayCount = 0;
					// use the material to compute the color
					qbVector<double> color = closestObject->m_pMaterial->ComputeColor
						(m_objectList, m_lightList,
						closestObject, closestIntPoint,
						closestLocalNormal, cameraRay);

					outputImage.setPixel(x, y, color.GetElement(0), color.GetElement(1), color.GetElement(2));

				} // if (closestObject->m_HasMaterial)
				else {
					// use the basic method to compute the color
					qbVector<double> matColor = LRT::MaterialBase::computeDiffuseColor
					(m_objectList, m_lightList, closestObject, 
					 closestIntPoint, closestLocalNormal,  
					 closestObject -> m_BaseColor);

					outputImage.setPixel(x, y, matColor.GetElement(0), matColor.GetElement(1), matColor.GetElement(2));

				} // else

			} // if (intersectionFound)

		} // for (int y = 0; y < ySize; ++y)

	} // for (int x = 0; x < xSize; ++x)

	std::cout << "done!" << std::endl;
	return true;

} // Render

bool LRT::Scene::CastRay(LRT::Ray& castRay, std::shared_ptr<LRT::ObjectBase>& closestObject, qbVector<double>& closestIntPoint, qbVector<double>& closestLocalNormal, qbVector<double>& closestLocalColor) {
	qbVector<double> intPoint{ 3 };
	qbVector<double> localNormal{ 3 };
	qbVector<double> localColor{ 3 };
	double minDist = 1e6;
	bool intersectionFound = false;
	for (auto currentObject : m_objectList)	{
		bool validInt = currentObject->testIntersections(castRay, intPoint, localNormal, localColor);
		// If we have a valid intersection.
		if (validInt) {
			// Set the flag to indicate that we found an intersection.
			intersectionFound = true;
			// Compute the distance between the camera and the point of intersection.
			double dist = (intPoint - castRay.m_Point1).norm();
			/* If this object is closer to the camera than any one that we have
				seen before, then store a reference to it. */
			if (dist < minDist) {
				minDist = dist;
				closestObject = currentObject;
				closestIntPoint = intPoint;
				closestLocalNormal = localNormal;
				closestLocalColor = localColor;

			} // if  (dist < minDist)

		} // if (validInt)

	} // for (auto currentObject : m_objectList)

	return intersectionFound;

} // CastRay
