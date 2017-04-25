/*
TEAM UNSIGNED FLOAT
First Draft: 04/04/2017
Sasha Wessels
This .cpp file is reponsible for creating the Rectangle shape
JIGRectangle.cpp
*/
#include "JIGRect.h"
#include <cmath>

JIG::Rectangle::Rectangle(KFAPoint centerPoint, float width, float height, float rotationAngle, KFAColorRGBA color, int vaID)
{
    this->_centerPoint = centerPoint;
    this->_width = width; //*std::cos(rotationAngle) + height*std::sin(rotationAngle)
    this->_height = height; //*std::sin(rotationAngle) + width*std::cos(rotationAngle)
	_rWidth = width;
	_rHeight = height;
    this->_rotation = rotationAngle;
    this->_color = color;
    this->_drawDataSize = 0;
    this->vertexArrayID = vaID;
}

JIG::Rectangle::Rectangle(const JIG::Rectangle &copyRect)
{
	this->_width = copyRect._width;
	this->_height = copyRect._height;
	this->_centerPoint = copyRect._centerPoint;
	this->_color = copyRect._color;
	/*Do NOT change the following two lines! The Rectangle does NOT OWN the drawData pointer!!!*/
	/*The KFAGLSupport library maintains a pointer, so it will handle freeing*/
	this->_drawDataSize = copyRect._drawDataSize;
	this->drawData = copyRect.drawData;
	this->_rotation = copyRect._rotation;
	this->vertexArrayID = copyRect.vertexArrayID;
}

void JIG::Rectangle::submitForRender(void)
{
    if (this->_drawDataSize != 0) {
        free(this->drawData);
        this->_drawDataSize = 0;
    }
    this->createDataBlock();
    
    if (this->vertexArrayID == -1){
        this->vertexArrayID = OGL_AssignMemoryToVertexArray(this->drawData, kfaGeometryTypeRectangle, this->_drawDataSize, -1);
    }else{
        OGL_AssignMemoryToVertexArray(this->drawData, kfaGeometryTypeRectangle, this->_drawDataSize, this->vertexArrayID);
    }
}

void JIG::Rectangle::createDataBlock(void)
{
#if _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4244)
#endif
    long int dataSize = sizeof(KFAColorRGBA)+sizeof(float)+sizeof(KFAPoint)*4+sizeof(KFAPoint);
    float *objData = (float *)malloc(dataSize);
    
    objData[0] = this->_color.r; objData[1] = this->_color.g; objData[2] = this->_color.b; objData[3] = this->_color.a;
    objData[4] = this->_rotation;
    objData[5] = this->_centerPoint.x; objData[6] = this->_centerPoint.y; objData[7] = this->_centerPoint.z;
    
    objData[VERTEX_OFFSET_2D + 1] = this->_centerPoint.x + (0.5f*this->_width);
    objData[VERTEX_OFFSET_2D + 2] = this->_centerPoint.y + (-0.5*this->_height);
    objData[VERTEX_OFFSET_2D + 3] = this->_centerPoint.z;
    
    objData[VERTEX_OFFSET_2D + 4] = this->_centerPoint.x + (0.5f*this->_width);
    objData[VERTEX_OFFSET_2D + 5] = this->_centerPoint.y + (0.5*this->_height);
    objData[VERTEX_OFFSET_2D + 6] = this->_centerPoint.z;
    
    objData[VERTEX_OFFSET_2D + 7] = this->_centerPoint.x + (-0.5f*this->_width);
    objData[VERTEX_OFFSET_2D + 8] = this->_centerPoint.y + (0.5*this->_height);
    objData[VERTEX_OFFSET_2D + 9] = this->_centerPoint.z;
    
    objData[VERTEX_OFFSET_2D + 10] = this->_centerPoint.x + (-0.5f*this->_width);
    objData[VERTEX_OFFSET_2D + 11] = this->_centerPoint.y + (-0.5*this->_height);
    objData[VERTEX_OFFSET_2D + 12] = this->_centerPoint.z;
    
    this->drawData = objData;
    this->_drawDataSize = dataSize;
#if _MSC_VER
#pragma warning( pop )
#endif
}

void JIG::Rectangle::updateGeometry(int horizontalVelocity, int verticalVelocity, float rotation)
{
    this->updateGeometry(horizontalVelocity, verticalVelocity, rotation, this->_color);
}

void JIG::Rectangle::updateGeometry(int horizontalVelocity, int verticalVelocity, float rotation, KFAColorRGBA color)
{
    this->_color = color;
    this->_centerPoint.x += horizontalVelocity;
    this->_centerPoint.y += verticalVelocity;
    this->_rotation += rotation;
    
    this->submitForRender();
}

JIG::Rectangle::~Rectangle()
{
	OGL_DisposeVertexArray(this->vertexArrayID);
}

