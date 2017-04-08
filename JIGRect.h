/*
TEAM UNSIGNED FLOAT
First Draft: 04/04/2017
Sasha Wessels
This .h file is reponsible for creating the Rectangle shape
JIGRectangle.h
*/
#ifndef JIGRect_H_
#define JIGRect_H_

#include "JIGShape.h"

namespace JIG{
    class Rectangle : public Shape {
	public:
        Rectangle(KFAPoint centerPoint, float width, float height, float rotationAngle, KFAColorRGBA color, int vaID = -1);
        void virtual submitForRender(void);
        void virtual updateGeometry(int horizontalVelocity, int verticalVelocity, float rotation);
        void virtual updateGeometry(int horizontalVelocity, int verticalVelocity, float rotation, KFAColorRGBA color);
        ~Rectangle();
        
	protected:
		float _height;
		float _width;
        
        void virtual createDataBlock(void);

	};
	
}
#endif /*JIGRect_H_*/
