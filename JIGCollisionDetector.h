/*
JIGCollisionDetector.h
Mark Underwood
4.4.17
Contains declarations for the collision detector class
*/


#ifndef JIGCOLLISIONDETECTOR_H
#define JIGCOLLISIONDETECTOR_H

#include "JIGShape.h"
#include <unordered_map>
#include <string>
#include <vector>

namespace JIG 
{

	class CollisionDetector
	{
	public:
		CollisionDetector();
		void addToMatrix(std::string, unsigned);
		CollisionDetector(Shape &, std::vector<Shape> &);
		void detectCollisions(Shape &, std::vector<Shape> &);
		std::unordered_map<signed, unsigned> getMatrix();
	private:
		static std::unordered_map<signed, unsigned> _matrix;
		std::vector<Shape> _pieces;
	};
}
#endif // !COLLISION_H

