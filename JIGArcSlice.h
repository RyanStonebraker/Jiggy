/*
Unsigned Float
CS202
4/4/2017
JIGArcSlice.h
This is the .h responsible for function pertaining to arc slices and circles (has namespace)
*/

#ifndef JIG_ARC_SLICE_H
#define JIG_ARC_SLICE_H

#include "JIGShape.h"

#define degreesToRadians(angleDegrees) (angleDegrees * 3.14159265 / 180.0)

namespace JIG
{
    class ArcSlice : public Shape {

	public:
        ArcSlice(KFAPoint centerPoint, float radius, float theta, float rotationAngle, KFAColorRGBA color, int vaID = -1);
        ArcSlice(const ArcSlice &that);
        void virtual submitForRender(void);
        void virtual updateGeometry(int horizontalVelocity, int verticalVelocity, float rotation);
        void virtual updateGeometry(int horizontalVelocity, int verticalVelocity, float rotation, KFAColorRGBA color);
        ~ArcSlice();
        
		double getWidth() const;

	protected:
		//Functions
		double calculateArcLength(double, double);
        void virtual createDataBlock(void);

		//Variables
        float _theta;
		float _radius;
		float _arcLength;
	};
}
#endif 
