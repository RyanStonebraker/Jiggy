/*
JIGColisionDetector.cpp
Mark Underwood
4.4.17
Definitions for collision detector class
*/

#include "JIGCollisionDetector.h"
#include <cmath>
using std::sin;
using std::cos;
using std::make_pair;
using namespace JIG;

#define PI 3.14159265



CollisionDetector::CollisionDetector()
{}

CollisionDetector::CollisionDetector(Shape &centralPiece, std::vector<Shape> &otherPieces) 
{
	detectCollisions(centralPiece, otherPieces);
}

void CollisionDetector::detectCollisions(Shape &centralPiece, std::vector<Shape> &otherPieces) //Find all collisions between one shape and the shapes around it.
{
	_matrix.insert({ "Shape", 0 }); //NOTE: will every shape have an identifier stored in it?
	for (auto p : otherPieces)
	{
		bool thereWasACollision;

		if (p.angle() <= (PI / 2) && p.angle() >= 0)
		{
			bool rightX(p.xpos() <= (centralPiece.xpos() + centralPiece.width() + p.height()*sin(p.angle()) ));
			bool leftX(p.xpos() >= (centralPiece.xpos() - p.width()*cos(p.angle()) ));
			bool aboveY(p.ypos() <= (centralPiece.ypos() + centralPiece.height() ));
			bool belowY(p.ypos() >= (centralPiece.ypos() - p.height()*cos(p.angle()) - p.width()*sin(p.angle()) ));

			thereWasACollision = rightX && leftX && aboveY && belowY;
		}
		else if (p.angle() <= (PI) && p.angle() >= (PI/2))
		{
			bool rightX(p.xpos() <= (centralPiece.xpos() + centralPiece.width() + p.height()*cos(p.angle() - PI/2) + p.width()*sin(p.angle() - PI/2) ));
			bool leftX(p.xpos() >= (centralPiece.xpos() ));
			bool aboveY(p.ypos() <= (centralPiece.ypos() + centralPiece.height() + p.height()*sin(p.angle() - PI/2) ));
			bool belowY(p.ypos() >= (centralPiece.ypos() - p.width()*cos(p.angle() - PI / 2) ));

			thereWasACollision = rightX && leftX && aboveY && belowY;
		}
		else if (p.angle() <= (3*PI/2) && p.angle() >= (PI))
		{
			bool rightX(p.xpos() <= (centralPiece.xpos() + centralPiece.width() + p.height()*sin(p.angle() - PI) ));
			bool leftX(p.xpos() >= (centralPiece.xpos() + p.width()*cos(p.angle() - PI) ));
			bool aboveY(p.ypos() <= (centralPiece.ypos() + centralPiece.height() + p.height()*cos(p.angle() - PI) + p.width()*sin(p.angle - PI) ));
			bool belowY(p.ypos() >= (centralPiece.ypos() ));

			thereWasACollision = rightX && leftX && aboveY && belowY;
		}
		else if (p.angle() <= (2 * PI) && p.angle() >= (PI))
		{
			bool rightX(p.xpos() <= (centralPiece.xpos() + centralPiece.width() ));
			bool leftX(p.xpos() >= (centralPiece.xpos() + p.width()*sin(p.angle() - 3*PI/2) + p.height()*cos(p.angle() - 3 *PI/2) ));
			bool aboveY(p.ypos() <= (centralPiece.ypos() + centralPiece.height() + p.width()*cos(p.angle - 3*PI/2) ));
			bool belowY(p.ypos() >= (centralPiece.ypos() - p.height()*sin(p.angle() - 3*PI/2) ));

			thereWasACollision = rightX && leftX && aboveY && belowY;
		}

		if (thereWasACollision)
			{
				++_matrix["Shape"];
			}
	}
}

std::unordered_map<std::string, unsigned> CollisionDetector::getMatrix()
{
	return _matrix;
}

/*
int main()
{
	OtherShape s1(2, 3);

	Shape s2(3, 3);

	Shape s3(4, 6);

	std::vector<Shape> shapes{s2, s3};

	CollisionDetector d1(s1, shapes);

	std::unordered_map<std::string, unsigned> matrix = d1.getMatrix();

	return 0;
}
*/