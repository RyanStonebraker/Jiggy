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
#include <memory>

namespace JIG
{

	class CollisionDetector
	{
	public:
		CollisionDetector();
		CollisionDetector(std::unique_ptr<Shape> &, std::vector<std::unique_ptr<Shape> > &);
		void detectCollisions(Shape &, std::vector<std::unique_ptr<Shape> > &);
		std::unordered_map<unsigned, unsigned> getMatrix();
		bool isCollided()
		{
			return _collision;
		}
		
	private:
		bool _collision;
		static std::unordered_map<unsigned, unsigned> _matrix;
		std::vector<std::unique_ptr<Shape> > _pieces;
	};
}
#endif 

