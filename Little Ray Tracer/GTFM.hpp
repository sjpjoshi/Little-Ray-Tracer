#pragma once

#ifndef GTFM_H
#define GTFM_H

#include "Ray.hpp"

// Lin Alg
#include "qbLinAlg/qbVector.h"
#include "qbLinAlg/qbMatrix.h"

namespace LRT {
	// direction flag values
	constexpr bool FWDTFORM = true;  // forward transform
	constexpr bool BCKTFORM = false; // back transform

	class GTForm {
	public:
		GTForm();
		~GTForm();
		GTForm(const qbMatrix2<double>& forward, const qbMatrix2<double>& back);

		GTForm(const qbVector<double>& translation, const qbVector<double>& rotation, const qbVector<double>& scale);

		void setTransform(const qbVector<double>& translation, 
						  const qbVector<double>& rotation, 
						  const qbVector<double>& scale);

		qbMatrix2<double> getForward();
		qbMatrix2<double> getBackward();

		LRT::Ray Apply(const LRT::Ray& inputRay, bool directionFlag);
		qbVector<double> Apply(const qbVector<double>& inputVector, bool directionFlag);
		qbVector<double> ApplyNormal(const qbVector<double>& inputVector);
		qbMatrix2<double> getNormalTransform();

		// lhs: left hand side
		// rhs: right hand side
		friend GTForm operator* (const LRT::GTForm& lhs, const LRT::GTForm& rhs); 
		GTForm operator= (const GTForm& rhs);

		// debug function
		void printMatrix(bool directionFlag);
		static void printVector(const qbVector<double> &inputVector);

	private:
		void print(const qbMatrix2<double>& matrix);
		void extractLinearTransform();

	private:
		qbMatrix2<double> m_FWDTFM{ 4,4 }; // forward transform
		qbMatrix2<double> m_BCKTFM{ 4,4 }; // forward transform
		qbMatrix2<double> m_LINTFM{ 3,3 }; // linear transform

	}; // GTFM

} // LRT

#endif