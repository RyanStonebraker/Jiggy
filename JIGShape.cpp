/*
TEAM UNSIGNED FLOAT
First Draft: 04/04/2017
Sasha Wessels
This .cpp file is reponsible for creating the base shape class
JIGShape.cpp
*/
#include "JIGShape.h"

float JIG::Shape::getWidth() const
{
	return _width;
}

float JIG::Shape::getHeight() const
{
	return _height;
}

KFAPoint JIG::Shape::centerPoint() const
{
	return _centerPoint;
}

float JIG::Shape::angle() const
{
	return _rotation;
}

int JIG::Shape::getxPos() const
{
	return _centerPoint.x;
}

int JIG::Shape::getyPos() const
{
	return _centerPoint.y;
}

void JIG::Shape::setxPos(int x)
{
    _centerPoint.x = x;
}

void JIG::Shape::setyPos(int y)
{
    _centerPoint.y = y;
}

void JIG::Shape::setRotPos(float r)
{
    _rotation = r;
}
