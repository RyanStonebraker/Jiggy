
/*
TEAM UNSIGNED FLOAT
First Draft: 04/04/2017
Sasha Wessels
This .cpp file is reponsible for creating the Triangle shape
JIGTriangle.cpp
*/
#include "JIGTriangle.h"
JIG::Triangle::Triangle(KFAPoint centerPoint, float side, float rotationAngle, KFAColorRGBA color, int vaID) {
	this->_centerPoint = centerPoint;
	this->_side = side;
	this->_rotation = rotationAngle;
	this->_color = color;
	this->_drawDataSize = 0;
	this->vertexArrayID = vaID; 
}

JIG::Triangle::Triangle(const JIG::Triangle &copyTri)
{
	this->_side = copyTri._side;
	this->_centerPoint = copyTri._centerPoint;
	this->_color = copyTri._color;
	this->_drawDataSize = copyTri._drawDataSize;
	this->drawData = copyTri.drawData;
	this->_rotation = copyTri._rotation;
	this->vertexArrayID = copyTri.vertexArrayID;
}