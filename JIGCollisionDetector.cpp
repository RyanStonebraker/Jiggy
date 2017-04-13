/*
JIGColisionDetector.cpp
Mark Underwood
4.4.17
Definitions for collision detector class
*/

#include "JIGCollisionDetector.h"
#include "JIGShape.h"
#include <cmath>
using std::sin;
using std::cos;
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
	_matrix.insert({ centralPiece.getVertexArrayID(), 0 }); //NOTE: will every shape have an identifier stored in it?
	KFAPoint bottomLeftC = centralPiece.centerPoint();
	bottomLeftC.x -= centralPiece.width()*0.5;
	bottomLeftC.y -= centralPiece.height()*0.5;
	for (auto p : otherPieces)
	{
		bool thereWasACollision;
		KFAPoint bottomLeftP = p.centerPoint();
		bottomLeftP.x -= p.width()*0.5;
		bottomLeftP.y -= p.height()*0.5;

		if (p.angle() <= (PI / 2) && p.angle() >= 0)
		{
			bool rightX(bottomLeftP.x <= (bottomLeftC.x + centralPiece.width() + p.height()*sin(p.angle()) ));
			bool leftX(bottomLeftP.x >= (bottomLeftC.x - p.width()*cos(p.angle()) ));
			bool aboveY(bottomLeftP.y <= (bottomLeftC.y + centralPiece.height() ));
			bool belowY(bottomLeftP.y >= (bottomLeftC.y - p.height()*cos(p.angle()) - p.width()*sin(p.angle()) ));

			thereWasACollision = rightX && leftX && aboveY && belowY;
		}
		else if (p.angle() <= (PI) && p.angle() >= (PI/2))
		{
			bool rightX(bottomLeftP.x <= (bottomLeftC.x + centralPiece.width() + p.height()*cos(p.angle() - PI/2) + p.width()*sin(p.angle() - PI/2) ));
			bool leftX(bottomLeftP.x >= (bottomLeftC.x ));
			bool aboveY(bottomLeftP.y <= (bottomLeftC.y + centralPiece.height() + p.height()*sin(p.angle() - PI/2) ));
			bool belowY(bottomLeftP.y >= (bottomLeftC.y - p.width()*cos(p.angle() - PI / 2) ));

			thereWasACollision = rightX && leftX && aboveY && belowY;
		}
		else if (p.angle() <= (3*PI/2) && p.angle() >= (PI))
		{
			bool rightX(bottomLeftP.x <= (bottomLeftC.x + centralPiece.width() + p.height()*sin(p.angle() - PI) ));
			bool leftX(bottomLeftP.x >= (bottomLeftC.x + p.width()*cos(p.angle() - PI) ));
			bool aboveY(bottomLeftP.y <= (bottomLeftC.y + centralPiece.height() + p.height()*cos(p.angle() - PI) + p.width()*sin(p.angle - PI) ));
			bool belowY(bottomLeftP.y >= (bottomLeftC.y ));

			thereWasACollision = rightX && leftX && aboveY && belowY;
		}
		else if (p.angle() <= (2 * PI) && p.angle() >= (PI))
		{
			bool rightX(bottomLeftP.x <= (bottomLeftC.x + centralPiece.width() ));
			bool leftX(bottomLeftP.x >= (bottomLeftC.x + p.width()*sin(p.angle() - 3*PI/2) + p.height()*cos(p.angle() - 3 *PI/2) ));
			bool aboveY(bottomLeftP.y <= (bottomLeftC.y + centralPiece.height() + p.width()*cos(p.angle - 3*PI/2) ));
			bool belowY(bottomLeftP.y >= (bottomLeftC.y - p.height()*sin(p.angle() - 3*PI/2) ));

			thereWasACollision = rightX && leftX && aboveY && belowY;
		}

		if (thereWasACollision)
			{
				++_matrix[centralPiece.getVertexArrayID()];
			}
	}
}

std::unordered_map<signed, unsigned> CollisionDetector::getMatrix()
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