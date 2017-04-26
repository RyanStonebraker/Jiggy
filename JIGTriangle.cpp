
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
	Triangle::~Triangle()
	{
		OGL_DisposeVertexArray(this->vertexArrayID);
	}
}
