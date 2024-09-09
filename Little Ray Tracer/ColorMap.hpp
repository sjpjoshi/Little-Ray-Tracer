#pragma once

// lin alg
#include "qbLinAlg/qbVector.h"

namespace LRT {
	namespace Texture {
		class ColorMap {
		public:
			ColorMap();
			~ColorMap();
		
			void setStop(double position, const qbVector<double> &value);
			qbVector<double> getColor(double position);

		private:
			std::vector<double> m_StopPosition;
			std::vector<qbVector<double>> m_StopValues;

 		}; // ColorMap
	
	} // Texture

} // LRT