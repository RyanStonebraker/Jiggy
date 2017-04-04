/*
Unsigned Float
CS202
4/4/2017
JIGArcSlice.h
This is the .h responsible for function pertaining to arc slices and circles (has namespace)
*/

#ifndef JIG_ARC_SLICE_H
#define JIG_ARC_SLICE_H

#define degreesToRadians(angleDegrees) (angleDegrees * 3.14159265 / 180.0)

namespace JIG
{
	class ArcSlice {

	public:
		ArcSlice(int r) : /* Shape(........) , */ _radius(r), _arcLength(calculateArcLength(_radius /*, angle? _theta */)) {};
		double getWidth() const;

	private:
		//Functions
		double calculateArcLength(double, double);

		//Variables
		double _boundingBox;
		double _radius;
		double _arcLength;
	};
}
#endif 
