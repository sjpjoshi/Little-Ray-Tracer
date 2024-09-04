#include "Scene.hpp"
#include "MaterialBase.hpp"
#include "SimpleMaterial.hpp"
#include "Checker.hpp"
#include "TImage.hpp"
#include "SimpleRefractive.hpp"

LRT::Scene::Scene() {
	// Configure the camera.
	m_camera.SetPosition(qbVector<double>{std::vector<double> {2.0, -5.0, 0.25}});
	m_camera.SetLookAt(qbVector<double>{std::vector<double> {0.0, 0.0, 0.0}});
	m_camera.SetUp(qbVector<double>{std::vector<double> {0.0, 0.0, 1.0}});
	m_camera.SetHorzSize(1.0);
	m_camera.SetAspect(16.0 / 9.0);
	m_camera.UpdateCameraGeometry();

	// Setup ambient lightling.
	LRT::MaterialBase::m_AmbientColor = std::vector<double>{ 1.0, 1.0, 1.0 };
	LRT::MaterialBase::m_AmbientIntensity = 0.2;

	// Create some textures.
	auto floorTexture = std::make_shared<LRT::Texture::Checker>(LRT::Texture::Checker());

	// Setup the textures.
	floorTexture->setTransform(qbVector<double>{std::vector<double>{0.0, 0.0}},
		0.0,
		qbVector<double>{std::vector<double>{16.0, 16.0}});

	// Create some materials.
	auto floorMaterial = std::make_shared<LRT::SimpleMaterial>(LRT::SimpleMaterial());
	auto imageMaterial = std::make_shared<LRT::SimpleMaterial>(LRT::SimpleMaterial());
	auto sphereMaterial = std::make_shared<LRT::SimpleMaterial>(LRT::SimpleMaterial());
	auto sphereMaterial2 = std::make_shared<LRT::SimpleMaterial>(LRT::SimpleMaterial());
	auto sphereMaterial3 = std::make_shared<LRT::SimpleMaterial>(LRT::SimpleMaterial());
	auto glassMaterial = std::make_shared<LRT::SimpleRefractive>(LRT::SimpleRefractive());

	// Setup the materials.
	floorMaterial->m_BaseColor = qbVector<double>{ std::vector<double>{1.0, 1.0, 1.0} };
	floorMaterial->m_Reflectivity = 0.25;
	floorMaterial->m_Shininess = 0.0;
	floorMaterial->assignTexture(floorTexture);

	sphereMaterial->m_BaseColor = qbVector<double>{ std::vector<double>{1.0, 0.2, 0.2} };
	sphereMaterial->m_Reflectivity = 0.8;
	sphereMaterial->m_Shininess = 32.0;

	sphereMaterial2->m_BaseColor = qbVector<double>{ std::vector<double>{0.2, 1.0, 0.2} };
	sphereMaterial2->m_Reflectivity = 0.8;
	sphereMaterial2->m_Shininess = 32.0;

	sphereMaterial3->m_BaseColor = qbVector<double>{ std::vector<double>{0.2, 0.2, 1.0} };
	sphereMaterial3->m_Reflectivity = 0.8; 
	sphereMaterial3->m_Shininess = 32.0; 

	glassMaterial->m_baseColor = qbVector<double>{ std::vector<double>{0.7, 0.7, 0.2} }; 
	glassMaterial->m_reflectivity = 0.25; 
	glassMaterial->m_shininess = 32.0; 
	glassMaterial->m_translucency = 0.75; 
	glassMaterial->m_indexOfRefraction = 1.333;  

	// Create and setup objects.
	auto floor = std::make_shared<LRT::ObjectPlane>(LRT::ObjectPlane());
	floor->setTransformMatrix(LRT::GTForm{ qbVector<double>{std::vector<double>{0.0, 0.0, 1.0}},
																							qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
																							qbVector<double>{std::vector<double>{16.0, 16.0, 1.0}} });
	floor->assignMaterial(floorMaterial);

	auto sphere = std::make_shared<LRT::ObjectSphere>(LRT::ObjectSphere());
	sphere->setTransformMatrix(LRT::GTForm{ qbVector<double>{std::vector<double>{-2.0, -2.0, 0.25}},
																							qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
																							qbVector<double>{std::vector<double>{0.75, 0.75, 0.75}} });
	sphere->assignMaterial(sphereMaterial);

	auto sphere2 = std::make_shared<LRT::ObjectSphere>(LRT::ObjectSphere());
	sphere2->setTransformMatrix(LRT::GTForm{ qbVector<double>{std::vector<double>{-2.0, -0.5, 0.25}},
																							qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
																							qbVector<double>{std::vector<double>{0.75, 0.75, 0.75}} });
	sphere2->assignMaterial(sphereMaterial2);

	auto sphere3 = std::make_shared<LRT::ObjectSphere>(LRT::ObjectSphere());
	sphere3->setTransformMatrix(LRT::GTForm{ qbVector<double>{std::vector<double>{-2.0, -1.25, -1.0}},
																							qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
																							qbVector<double>{std::vector<double>{0.75, 0.75, 0.75}} });
	sphere3->assignMaterial(sphereMaterial3);

	auto sphere4 = std::make_shared<LRT::ObjectSphere>(LRT::ObjectSphere());
	sphere4->setTransformMatrix(LRT::GTForm{ qbVector<double>{std::vector<double>{2.0, -1.25, 0.25}},
																							qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
																							qbVector<double>{std::vector<double>{0.75, 0.75, 0.75}} });
	sphere4->assignMaterial(glassMaterial);

	// Put the objects into the scene.	
	m_objectList.push_back(floor);
	m_objectList.push_back(sphere);
	m_objectList.push_back(sphere2);
	m_objectList.push_back(sphere3);
	m_objectList.push_back(sphere4);

	// Construct and setup the lights.
	m_lightList.push_back(std::make_shared<LRT::PointLight>(LRT::PointLight()));
	m_lightList.at(0)->m_Location = qbVector<double>{ std::vector<double> {3.0, -10.0, -5.0} };
	m_lightList.at(0)->m_Color = qbVector<double>{ std::vector<double> {1.0, 1.0, 1.0} };
	m_lightList.at(0)->m_Intensity = 4.0;

	m_lightList.push_back(std::make_shared<LRT::PointLight>(LRT::PointLight()));
	m_lightList.at(1)->m_Location = qbVector<double>{ std::vector<double> {0.0, -10.0, -5.0} };
	m_lightList.at(1)->m_Color = qbVector<double>{ std::vector<double> {1.0, 1.0, 1.0} };
	m_lightList.at(1)->m_Intensity = 2.0;

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
		std::cout << "procesing line " << y << " of " << ySize << ". " << "\r";
		std::cout.flush();

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

	std::cout << std::endl;
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
