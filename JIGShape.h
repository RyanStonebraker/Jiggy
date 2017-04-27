/*
TEAM UNSIGNED FLOAT
First Draft: 04/04/2017
Sasha Wessels
This .h file is reponsible for creating the base shape class
JIGShape.h
*/
#ifndef JIGShape_H_
#define JIGShape_H_

#include "KFAGLSupport.h"
#if __APPLE__
#include <OpenGL/OpenGL.h>
#elif _WIN32

#endif

namespace JIG{
	class Shape {
	public:
        
        void virtual submitForRender(void) = 0;
        void virtual updateGeometry(int horizontalVelocity, int verticalVelocity, float rotation) = 0;
        void virtual updateGeometry(int horizontalVelocity, int verticalVelocity, float rotation, KFAColorRGBA color) = 0;
		float getWidth() const;
		float getHeight() const;
		int getxPos() const;
		int getyPos() const;
        void setxPos(int x);
        void setyPos(int y);
        void setRotPos(float r);
        
		float angle() const;
		KFAPoint centerPoint() const;
	
    protected:
		float _width;
		float _height;
        KFAPoint _centerPoint;
        KFAColorRGBA _color;
        void *drawData;
        size_t _drawDataSize;
        float _rotation;
        static unsigned int nextVertexBuffer;
        unsigned int vertexArrayID;
        
        void virtual createDataBlock(void) = 0;
	};
}
#endif /*JIGShape_H_*/
