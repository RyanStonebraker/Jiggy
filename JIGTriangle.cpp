
/*
TEAM UNSIGNED FLOAT
First Draft: 04/04/2017
Sasha Wessels
This .cpp file is reponsible for creating the Triangle shape
JIGTriangle.cpp
*/
#include "JIGTriangle.h"
namespace JIG{
	Triangle::Triangle(KFAPoint centerPoint, float length,float rotationAngle, KFAColorRGBA color, int vaID)
	{
		_width = length;
		_height = length;
		_length = length;
		_centerPoint = centerPoint;
		_color = color;
		_rotation = rotationAngle;
		this->vertexArrayID = vaID;
		this->_drawDataSize = 0;


	}
	Triangle::Triangle(const Triangle & tri)
	{
		this->_length = tri._length;
		this->_centerPoint = tri._centerPoint;
		this->_color = tri._color;
		this->_drawDataSize = tri._drawDataSize;
		this->drawData = tri.drawData;
		this->_rotation = tri._rotation;
		this->vertexArrayID = tri.vertexArrayID;
	}
	void Triangle::submitForRender(void)
	{
		if (this->_drawDataSize != 0) {
			free(this->drawData);
			this->_drawDataSize = 0;
		}
		this->createDataBlock();

		if (this->vertexArrayID == -1) {
			this->vertexArrayID = OGL_AssignMemoryToVertexArray(this->drawData, kfaGeometryTypeRectangle, this->_drawDataSize, -1);
		}
		else {
			OGL_AssignMemoryToVertexArray(this->drawData, kfaGeometryTypeRectangle, this->_drawDataSize, this->vertexArrayID);
		}
	}
	
	void Triangle::updateGeometry(int horizontalVelocity, int verticalVelocity, float rotation)
	{
		this->updateGeometry(horizontalVelocity, verticalVelocity, rotation, this->_color);
	}
	
	void Triangle::updateGeometry(int horizontalVelocity, int verticalVelocity, float rotation, KFAColorRGBA color)
	{
		this->_color = color;
		this->_centerPoint.x += horizontalVelocity;
		this->_centerPoint.y += verticalVelocity;
		this->_rotation += rotation;

		this->submitForRender();
	}
	
	Triangle::~Triangle()
	{
		OGL_DisposeVertexArray(this->vertexArrayID);
	}
	
	void Triangle::createDataBlock(void)
	{
		#if _MSC_VER
		#pragma warning( push )
		#pragma warning( disable : 4244)
		#endif
		
			/*  Collin, I know you have inferior coding skills
				so I'm puting this comment here to tell you that
				this is where you should put your code. <3 Tristan */

		#if _MSC_VER
		#pragma warning( pop )
		#endif
	}
}
