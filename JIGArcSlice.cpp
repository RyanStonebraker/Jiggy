/*
Unsigned Float
CS202
4/4/2017
JIGArcSlice.cpp
This is the .cpp responsible for function pertaining to arc slices and circles
*/

#include "ArcLength.h"
//using namespace JIG; syntax

int main()
{

}

double JIG::ArcSlice::getWidth() const
{
	return _boundingBox; //needs editing
}

double JIG::ArcSlice::calculateArcLength(double radius, double theta)
{
	return radius * degreesToRadians(theta); //using s=r(theta) where s is the arc length of a circle with radius r and angle theta(radians)
}
