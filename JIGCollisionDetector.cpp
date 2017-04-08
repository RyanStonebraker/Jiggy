/*
JIGColisionDetector.cpp
Mark Underwood
4.4.17
Definitions for collision detector class
*/

#include "JIGCollisionDetector.h"
using std::make_pair;


CollisionDetector::CollisionDetector()
{}

CollisionDetector::CollisionDetector(Shape &centralPiece, std::vector<Shape &> otherPieces) 
{
	detectCollisions(centralPiece, otherPieces);
}

void CollisionDetector::detectCollisions(Shape &centralPiece, std::vector<Shape &> otherPieces) //Find all collisions between one shape and the shapes around it.
{
	_matrix.insert({ "Shape", 0 });
	for (auto p : otherPieces)
	{
		bool rightX(p.xpos() <= (centralPiece.xpos() + centralPiece.width()));
		bool leftX(p.xpos() >= (centralPiece.xpos() - p.xpos()));
		bool aboveY(p.ypos() <= (centralPiece.ypos() + centralPiece.height()));
		bool belowY(p.ypos() >= (centralPiece.ypos() - p.height()));

		if (leftX && rightX && aboveY && belowY)
			{
				++_matrix["Shape"];
			}
	}
}

std::unordered_map<std::string, unsigned> CollisionDetector::getAdjacent()
{
	return _matrix;
}