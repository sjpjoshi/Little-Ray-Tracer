#include "camera.hpp"
#include "ray.hpp"

// std
#include "math.h"

LRT::Camera::Camera() {
	// The default constructor.
	m_cameraPosition = qbVector<double> { std::vector<double> {0.0, -10.0, 0.0}  };
	m_cameraLookAt = qbVector<double>	{ std::vector<double> {0.0, 0.0,   0.0}  };
	m_cameraUp = qbVector<double>	    { std::vector<double> {0.0, 0.0,   1.0}  };
	m_cameraLength = 1.0;
	m_cameraHorzSize = 1.0;
	m_cameraAspectRatio = 1.0;

} // Camera

void LRT::Camera::SetPosition(const qbVector<double>& newPosition) { m_cameraPosition = newPosition; } // SetPosition
void LRT::Camera::SetLookAt(const qbVector<double>& newLookAt)	   { m_cameraLookAt = newLookAt; } // SetLookAt
void LRT::Camera::SetUp(const qbVector<double>& upVector)		   { m_cameraUp = upVector; } // SetUp
void LRT::Camera::SetLength(double newLength)					   { m_cameraLength = newLength; } // SetLength
void LRT::Camera::SetHorzSize(double newHorzSize)				   { m_cameraHorzSize = newHorzSize; } // SetHorzSize
void LRT::Camera::SetAspect(double newAspect)					   { m_cameraAspectRatio = newAspect; } // SetAspect

qbVector<double> LRT::Camera::GetPosition()	   { return m_cameraPosition; } // GetPosition
qbVector<double> LRT::Camera::GetLookAt()	   { return m_cameraLookAt; } // GetLookAt
qbVector<double> LRT::Camera::GetUp()		   { return m_cameraUp; } // GetUp
double LRT::Camera::GetLength()				   { return m_cameraLength; } // GetLength
double LRT::Camera::GetHorzSize()			   { return m_cameraHorzSize; } // GetHorzSize
double LRT::Camera::GetAspect()				   { return m_cameraAspectRatio; } // GetAspect
qbVector<double> LRT::Camera::GetU()           { return m_projectionScreenU; } // GetU
qbVector<double> LRT::Camera::GetV()		   { return m_projectionScreenV; } // GetV
qbVector<double> LRT::Camera::GetScreenCentre(){ return m_projectionScreenCentre; } // GetScreenCentre

void LRT::Camera::UpdateCameraGeometry() {
	// First, compute the vector from the camera position to the LookAt position.
	m_alignmentVector = m_cameraLookAt - m_cameraPosition;
	m_alignmentVector.Normalize();

	// Second, compute the alpha and beta unit vectors.
	m_projectionScreenU = qbVector<double>::cross(m_alignmentVector, m_cameraUp);
	m_projectionScreenU.Normalize();
	m_projectionScreenV = qbVector<double>::cross(m_projectionScreenU, m_alignmentVector);
	m_projectionScreenV.Normalize();

	// Thirdly, compute the position of the center point of the screen.
	m_projectionScreenCentre = m_cameraPosition + (m_cameraLength * m_alignmentVector);

	// Modify the U and V vectors to match the size and aspect ratio.
	m_projectionScreenU = m_projectionScreenU * m_cameraHorzSize;
	m_projectionScreenV = m_projectionScreenV * (m_cameraHorzSize / m_cameraAspectRatio);

} // UpdateCameraGeometry

LRT::Ray LRT::Camera::GenerateRay(float proScreenX, float proScreenY) {
	// Compute the location of the screen point in world coordinates.
	qbVector<double> screenWorldPart1 = m_projectionScreenCentre + (m_projectionScreenU * proScreenX);
	qbVector<double> screenWorldCoordinate = screenWorldPart1 + (m_projectionScreenV * proScreenY);

	// Use this point along with the camera position to compute the ray.
	return Ray(m_cameraPosition, screenWorldCoordinate);

} // GenerateRay