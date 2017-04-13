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
#if 0
class Shape //Had to write this so I could write stuff with shapes before the actual JIGShape class is written 
{

public:
	Shape() : _width(1), _height(1), _xpos(0), _ypos(0)
	{}

	Shape(int width, int height) : _width(width), _height(height)
	{}

	int width()
	{
		return _width;
	}

	int height()
	{
		return _height;
	}

	int xpos()
	{
		return _xpos;
	}

	int ypos()
	{
		return _ypos;
	}

	int angle()
	{
		return _angle;
	}

protected:
	int _width;
	int _height;
	int _xpos;
	int _ypos;
	int _angle;
};

class OtherShape : public Shape
{
public:
	OtherShape(int width, int height) : Shape(width, height)
	{}
};
#endif

namespace JIG 
{

	class CollisionDetector
	{
	public:
		CollisionDetector();
		void addToMatrix(std::string, unsigned);
		CollisionDetector(Shape &, std::vector<Shape> &);
		void detectCollisions(Shape &, std::vector<Shape> &);
		std::unordered_map<std::string, unsigned> getMatrix();
	private:
		static std::unordered_map<std::string, unsigned> _matrix;
		std::vector<Shape> _pieces;
	};
}
#endif // !COLLISION_H

