#include "Scene.hpp"
#include "MaterialBase.hpp"
#include "SimpleMaterial.hpp"
#include "Checker.hpp"

LRT::Scene::Scene() {
	// Configure the camera.
	//m_camera.SetPosition(	qbVector<double>{std::vector<double> {3.0, -3.75, -3.0}} );
	m_camera.SetPosition(qbVector<double>{std::vector<double> {2.0, -5.0, -2.0}});
	m_camera.SetLookAt(qbVector<double>{std::vector<double> {0.0, 0.0, 0.0}});
	m_camera.SetUp(qbVector<double>{std::vector<double> {0.0, 0.0, 1.0}});
	m_camera.SetHorzSize(1.0);
	m_camera.SetAspect(16.0 / 9.0);
	//m_camera.SetAspect(1.0);
	m_camera.UpdateCameraGeometry();

	// Create some textures.
	auto floorTexture = std::make_shared<LRT::Texture::Checker>(LRT::Texture::Checker());
	auto sphereTexture = std::make_shared<LRT::Texture::Checker>(LRT::Texture::Checker());
	auto cylinderTexture = std::make_shared<LRT::Texture::Checker>(LRT::Texture::Checker());
	auto coneTexture = std::make_shared<LRT::Texture::Checker>(LRT::Texture::Checker());

	// Setup the textures.
	floorTexture->setTransform(qbVector<double>{std::vector<double>{0.0, 0.0}},
		0.0,
		qbVector<double>{std::vector<double>{16.0, 16.0}});

	sphereTexture->setColor(qbVector<double>{std::vector<double>{0.2, 0.2, 0.8}}, qbVector<double>{std::vector<double>{0.8, 0.8, 0.2}});
	sphereTexture->setTransform(qbVector<double>{std::vector<double>{0.0, 0.0}},
		0.0,
		qbVector<double>{std::vector<double>{16.0, 16.0}});

	cylinderTexture->setColor(qbVector<double>{std::vector<double>{1.0, 0.5, 0.0}}, qbVector<double>{std::vector<double>{0.8, 0.8, 0.2}});
	cylinderTexture->setTransform(qbVector<double>{std::vector<double>{0.0, 0.0}},
		0.0,
		qbVector<double>{std::vector<double>{4.0 * M_PI, 4.0}});

	coneTexture->setColor(qbVector<double>{std::vector<double>{0.2, 0.2, 0.8}}, qbVector<double>{std::vector<double>{1.0, 0.5, 0.0}});
	coneTexture->setTransform(qbVector<double>{std::vector<double>{0.0, 0.0}},
		0.0,
		qbVector<double>{std::vector<double>{8.0 * (M_PI / 2.0), 8.0}});

	// Create some materials.
	auto silverMetal = std::make_shared<LRT::SimpleMaterial>(LRT::SimpleMaterial());
	auto goldMetal = std::make_shared<LRT::SimpleMaterial>(LRT::SimpleMaterial());
	auto blueDiffuse = std::make_shared<LRT::SimpleMaterial>(LRT::SimpleMaterial());
	auto yellowDiffuse = std::make_shared<LRT::SimpleMaterial>(LRT::SimpleMaterial());
	auto orangeDiffuse = std::make_shared<LRT::SimpleMaterial>(LRT::SimpleMaterial());
	auto floorMaterial = std::make_shared<LRT::SimpleMaterial>(LRT::SimpleMaterial());
	auto wallMaterial = std::make_shared<LRT::SimpleMaterial>(LRT::SimpleMaterial());

	// Setup the materials.
	silverMetal->m_BaseColor = qbVector<double>{ std::vector<double>{0.5, 0.5, 0.8} };
	silverMetal->m_Reflectivity = 0.5;
	silverMetal->m_Shininess = 20.0;

	goldMetal->m_BaseColor = qbVector<double>{ std::vector<double>{0.8, 0.8, 0.3} };
	goldMetal->m_Reflectivity = 0.25;
	goldMetal->m_Shininess = 20.0;

	blueDiffuse->m_BaseColor = qbVector<double>{ std::vector<double>{0.2, 0.2, 0.8} };
	blueDiffuse->m_Reflectivity = 0.05;
	blueDiffuse->m_Shininess = 5.0;
	blueDiffuse->assignTexture(coneTexture);

	yellowDiffuse->m_BaseColor = qbVector<double>{ std::vector<double>{0.8, 0.8, 0.2} };
	yellowDiffuse->m_Reflectivity = 0.05;
	yellowDiffuse->m_Shininess = 20.0;
	yellowDiffuse->assignTexture(sphereTexture);

	orangeDiffuse->m_BaseColor = qbVector<double>{ std::vector<double>{1.0, 0.5, 0.0} };
	orangeDiffuse->m_Reflectivity = 0.05;
	orangeDiffuse->m_Shininess = 5.0;
	orangeDiffuse->assignTexture(cylinderTexture);

	floorMaterial->m_BaseColor = qbVector<double>{ std::vector<double>{1.0, 1.0, 1.0} };
	floorMaterial->m_Reflectivity = 0.5;
	floorMaterial->m_Shininess = 0.0;
	floorMaterial->assignTexture(floorTexture);

	wallMaterial->m_BaseColor = qbVector<double>{ std::vector<double>{1.0, 0.125, 0.125} };
	wallMaterial->m_Reflectivity = 0.75;
	wallMaterial->m_Shininess = 0.0;

	// Create and setup objects.
	auto cone = std::make_shared<LRT::Cone>(LRT::Cone());
	cone->setTransformMatrix(LRT::GTForm{ qbVector<double>{std::vector<double>{-1.0, -2.0, -2.0}},
																						qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
																						qbVector<double>{std::vector<double>{0.5, 0.5, 1.0}} });
	cone->assignMaterial(blueDiffuse);

	auto leftSphere = std::make_shared<LRT::ObjectSphere>(LRT::ObjectSphere());
	leftSphere->setTransformMatrix(LRT::GTForm{ qbVector<double>{std::vector<double>{1.0, -1.0, 0.5}},
																									qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
																									qbVector<double>{std::vector<double>{0.5, 0.5, 0.5}} });
	leftSphere->assignMaterial(silverMetal);

	auto rightSphere = std::make_shared<LRT::ObjectSphere>(LRT::ObjectSphere());
	rightSphere->setTransformMatrix(LRT::GTForm{ qbVector<double>{std::vector<double>{2.0, 0.0, 0.0}},
																									qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
																									qbVector<double>{std::vector<double>{1.0, 1.0, 1.0}} });
	rightSphere->assignMaterial(yellowDiffuse);

	auto floor = std::make_shared<LRT::ObjectPlane>(LRT::ObjectPlane());
	floor->setTransformMatrix(LRT::GTForm{ qbVector<double>{std::vector<double>{0.0, 0.0, 1.0}},
																							qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
																							qbVector<double>{std::vector<double>{16.0, 16.0, 1.0}} });
	floor->assignMaterial(floorMaterial);

	auto leftWall = std::make_shared<LRT::ObjectPlane>(LRT::ObjectPlane());
	leftWall->setTransformMatrix(LRT::GTForm{ qbVector<double>{std::vector<double>{-4.0, 0.0, 0.0}},
																								qbVector<double>{std::vector<double>{0.0, -M_PI / 2.0, -M_PI / 2.0}},
																								qbVector<double>{std::vector<double>{16.0, 16.0, 1.0}} });
	leftWall->assignMaterial(wallMaterial);

	auto backWall = std::make_shared<LRT::ObjectPlane>(LRT::ObjectPlane());
	backWall->setTransformMatrix(LRT::GTForm{ qbVector<double>{std::vector<double>{0.0, 4.0, 0.0}},
																								qbVector<double>{std::vector<double>{-M_PI / 2.0, 0.0, 0.0}},
																								qbVector<double>{std::vector<double>{16.0, 16.0, 1.0}} });
	backWall->assignMaterial(wallMaterial);

	auto cylinder2 = std::make_shared<LRT::Cylinder>(LRT::Cylinder());
	cylinder2->setTransformMatrix(LRT::GTForm{ qbVector<double>{std::vector<double>{-1.0, -2.0, 0.0}},
																									qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
																									qbVector<double>{std::vector<double>{1.0, 1.0, 1.0}} });
	cylinder2->assignMaterial(orangeDiffuse);

	// Put the objects into the scene.	
	m_objectList.push_back(cone);
	m_objectList.push_back(leftSphere);
	m_objectList.push_back(rightSphere);
	m_objectList.push_back(floor);
	m_objectList.push_back(leftWall);
	m_objectList.push_back(backWall);
	m_objectList.push_back(cylinder2);

	// Construct and setup the lights.
	m_lightList.push_back(std::make_shared<LRT::PointLight>(LRT::PointLight()));
	m_lightList.at(0)->m_Location = qbVector<double>{ std::vector<double> {3.0, -10.0, -5.0} }; 
	m_lightList.at(0)->m_Color = qbVector<double>{ std::vector<double> {1.0, 1.0, 1.0} };

	m_lightList.push_back(std::make_shared<LRT::PointLight>(LRT::PointLight()));
	m_lightList.at(1)->m_Location = qbVector<double>{ std::vector<double> {0.0, -10.0, -5.0} };
	m_lightList.at(1)->m_Color = qbVector<double>{ std::vector<double> {1.0, 1.0, 1.0} };

	m_lightList.push_back(std::make_shared<LRT::PointLight>(LRT::PointLight()));
	m_lightList.at(2)->m_Location = qbVector<double>{ std::vector<double> {-2.0, 2.0, 0.0} };
	m_lightList.at(2)->m_Color = qbVector<double>{ std::vector<double> {1.0, 0.8, 0.8} };
	m_lightList.at(2)->m_Intensity = 0.5;

	m_lightList.push_back(std::make_shared<LRT::PointLight>(LRT::PointLight()));
	m_lightList.at(3)->m_Location = qbVector<double>{ std::vector<double> {4.0, 2.0, 0.0} };
	m_lightList.at(3)->m_Color = qbVector<double>{ std::vector<double> {1.0, 0.8, 0.8} };
	m_lightList.at(3)->m_Intensity = 0.5;

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
