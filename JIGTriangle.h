/*
TEAM UNSIGNED FLOAT
First Draft: 04/04/2017
Sasha Wessels
This .h file is reponsible for creating the Triangle shape
JIGTriangle.h
*/
#ifndef JIGTriangle_H_
#define JIGTriangle_H_
#include "JIGShape.h"
namespace JIG{
	class Triangle : public Shape {
	public:
		Triangle(KFAPoint centerPoint, float side, float rotationAngle, KFAColorRGBA color, int vaID = -1);
		Triangle(const Triangle &copyTri);
		/*void virtual submitForRender(void);
		void virtual updateGeometry(int horizontalVelocity, int verticalVelocity, float rotation);
		void virtual updateGeometry(int horizontalVelocity, int verticalVelocity, float rotation, KFAColorRGBA color);
		~Triangle();*/

	protected:
		float _side;

		//void virtual createDataBlock(void);

	};

}
#endif /*JIGTriangle_H_*/

