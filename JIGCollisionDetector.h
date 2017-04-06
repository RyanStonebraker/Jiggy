/*
JIGColisionDetector.h
Mark Underwood
4.4.17
Contains declarations for the collision detector class
*/


#ifndef COLLISION_H
#define COLLISION_H

#include <unordered_map>
#include <string>
#include <vector>

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

private:
	int _width;
	int _height;
	int _xpos;
	int _ypos;
};

class CollisionDetector
{
public:
	CollisionDetector();
	void addToMatrix(std::string, unsigned);
	CollisionDetector(std::vector<Shape>);
	void detectCollisions(Shape &, Shape &);
	void getAdjMatrix();
private:
	std::unordered_map<std::string, unsigned> _matrix;
	std::vector<Shape> _pieces;
};


#endif // !COLLISION_H

