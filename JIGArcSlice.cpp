/*
Unsigned Float
CS202
4/4/2017
JIGArcSlice.cpp
This is the .cpp responsible for function pertaining to arc slices and circles
*/

#include "JIGArcSlice.h"
//using namespace JIG; syntax

JIG::ArcSlice::ArcSlice(KFAPoint centerPoint, float radius, float theta, float rotationAngle, KFAColorRGBA color, int vaID)
{
    _centerPoint = centerPoint;
    _theta = theta;
    _radius = radius;
    _rotation = rotationAngle;
    _color = color;
    this->vertexArrayID = vaID;
    this->_drawDataSize = 0;
}

JIG::ArcSlice::ArcSlice(const ArcSlice &that)
{
    this->_theta = that._theta;
    this->_radius = that._radius;
    this->_centerPoint = that._centerPoint;
    this->_color = that._color;
    /*Do NOT change the following two lines! The ArcSlice does NOT OWN the drawData pointer!!!*/
    /*The KFAGLSupport library maintains a pointer to this data, so it will handle freeing*/
    this->_drawDataSize = that._drawDataSize;
    this->drawData = that.drawData;
    this->_rotation = that._rotation;
    this->vertexArrayID = that.vertexArrayID;
}

void JIG::ArcSlice::submitForRender(void)
{
    if (this->_drawDataSize != 0) {
        free(this->drawData);
        this->_drawDataSize = 0;
    }
    this->createDataBlock();
    
    if (this->vertexArrayID == -1){
        this->vertexArrayID = OGL_AssignMemoryToVertexArray(this->drawData, kfaGeometryTypeArc, this->_drawDataSize, -1);
    }else{
        OGL_AssignMemoryToVertexArray(this->drawData, kfaGeometryTypeArc, this->_drawDataSize, this->vertexArrayID);
    }
}

void JIG::ArcSlice::createDataBlock(void)
{
#if _MSC_VER
    #pragma warning( push )
    #pragma warning( disable : 4244)
#endif
    long int dataSize = sizeof(KFAColorRGBA)+sizeof(float)+sizeof(KFAPoint)+sizeof(float)*2;
    float *objData = (float *)malloc(dataSize);
    
    objData[0] = this->_color.r; objData[1] = this->_color.g; objData[2] = this->_color.b; objData[3] = this->_color.a;
    objData[4] = this->_rotation;
    objData[5] = this->_centerPoint.x; objData[6] = this->_centerPoint.y; objData[7] = this->_centerPoint.z;
    
    objData[VERTEX_OFFSET_2D + 1] = this->_radius;
    objData[VERTEX_OFFSET_2D + 2] = this->_theta;
    
    this->drawData = objData;
    this->_drawDataSize = dataSize;
#if _MSC_VER
    #pragma warning( pop )
#endif
}

void JIG::ArcSlice::updateGeometry(int horizontalVelocity, int verticalVelocity, float rotation)
{
    this->updateGeometry(horizontalVelocity, verticalVelocity, rotation, this->_color);
}

void JIG::ArcSlice::updateGeometry(int horizontalVelocity, int verticalVelocity, float rotation, KFAColorRGBA color)
{
    this->_color = color;
    this->_centerPoint.x += horizontalVelocity;
    this->_centerPoint.y += verticalVelocity;
    this->_rotation += rotation;
    
    this->submitForRender();
}

JIG::ArcSlice::~ArcSlice()
{
    OGL_DisposeVertexArray(this->vertexArrayID);
}

double JIG::ArcSlice::getWidth() const
{
    return 0.0;
}

double JIG::ArcSlice::calculateArcLength(double radius, double theta)
{
	return radius * degreesToRadians(theta); //using s=r(theta) where s is the arc length of a circle with radius r and angle theta(radians)
}
