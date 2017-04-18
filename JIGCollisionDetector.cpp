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
using std::sqrt;
using std::atan;
#include <memory>
using std::unique_ptr;
using std::make_unique;
#include <vector>
#include <map>

using namespace JIG;

#define PI 3.14159265

CollisionDetector::CollisionDetector()
{}

CollisionDetector::CollisionDetector(Shape &centralPiece, std::vector<Shape> &otherPieces) 
{
	detectCollisions(centralPiece, otherPieces);
}

int projectedWidth(Shape &s)
{
	if (s.angle() <= 90 && s.angle() >= 0)
	{
		return sqrt((s.width() / 2)^2 + (s.height() / 2)^2)*cos(atan((s.height() / 2)/(s.width() / 2)-s.angle()));
	}
	else if (s.angle() <= 180 && s.angle() >= 90)
	{

	}
	else if (s.angle() <= 270 && s.angle() >= 180)
	{

	}
	else if (s.angle() <= 360 && s.angle() >= 270)
	{

	}
	return -1;
}

void CollisionDetector::detectCollisions(Shape &centralPiece, std::vector<Shape> &otherPieces) //Find all collisions between one shape and the shapes around it.
{
	_matrix.insert({ centralPiece.getVertexArrayID(), 0 });
	
	for (unsigned int i = 0; i < otherPieces.size(); ++i)
	{
		bool collisionOne;
		bool collisionTwo;
		bool thereWasACollision = collisionOne && collisionTwo;

		int actualWidth = abs(centralPiece.centerPoint().x - otherPieces[i].centerPoint.x);
		int actualHeight = abs(centralPiece.centerPoint().x - otherPieces[i].centerPoint().x);

		int newAngleC1 = centralPiece.angle() - centralPiece.angle();
		int newAngleP1;
		if (otherPieces[i].angle() < centralPiece.angle()) //Is there something that converts everything to 0-360 degrees?
		{
			newAngleP1 = 360 - (centralPiece.angle() - otherPieces[i].angle());
		}
		else
		{
			newAngleP1 = otherPieces[i].angle() - centralPiece.angle();
		}
		int collidedWidth1 = centralPiece.width() + projectedWidth(otherPieces[i]);

		collisionOne = actualWidth <= collidedWidth1;

		int newAngleP2 = otherPieces[i].angle() - otherPieces[i].angle();
		int newAngleC2;
		if (centralPiece.angle() < otherPieces[i].angle())
		{
			newAngleC2 = 360 - (otherPieces[i].angle() - centralPiece.angle());
		}
		else
		{
			newAngleP2 = centralPiece.angle() - otherPieces[i].angle();
		}
		int collidedWidth2 = otherPieces[i].width() + projectedWidth(centralPiece);

		collisionTwo = actualWidth <= collidedWidth2;

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

*********************************************************************************

KFAPoint bottomLeftOfC = centralPiece.centerPoint();
bottomLeftOfC.x -= centralPiece.width()/2;
bottomLeftOfC.y -= centralPiece.height()/2;

Shape *p = &otherPieces[i];
bool thereWasACollision;
KFAPoint bottomLeftOfP = p->centerPoint();
bottomLeftOfP.x -= p->width() / 2;
bottomLeftOfP.y -= p->height() / 2;

if (p->angle() <= (PI / 2) && p->angle() >= 0)
{
	int projC = projectedWidth(centralPiece);
	int projP = projectedWidth(otherPieces[i]);
	bool rightX(bottomLeftOfP.x <= (bottomLeftOfC.x + centralPiece.width()*cos(p->angle()) + p->height()*sin(p->angle())));
	bool leftX(bottomLeftOfP.x >= (bottomLeftOfC.x - centralPiece.height()*sin(p->angle()) - p->width()*cos(p->angle())));
	bool aboveY(bottomLeftOfP.y <= (bottomLeftOfC.y + centralPiece.width()*sin(p->angle()) + centralPiece.height()*sin(p->angle())));
	bool belowY(bottomLeftOfP.y >= (bottomLeftOfC.y - p->height()*cos(p->angle()) - p->width()*sin(p->angle())));

	thereWasACollision = rightX && leftX && aboveY && belowY;
}
else if (p->angle() <= (PI) && p->angle() >= (PI / 2))
{
	bool rightX(bottomLeftOfP.x <= (bottomLeftOfC.x + p->height()*cos(p->angle() - PI / 2) + p->width()*sin(p->angle() - PI / 2)));
	bool leftX(bottomLeftOfP.x >= (bottomLeftOfC.x));
	bool aboveY(bottomLeftOfP.y <= (bottomLeftOfC.y + centralPiece.height() + p->height()*sin(p->angle() - PI / 2)));
	bool belowY(bottomLeftOfP.y >= (bottomLeftOfC.y - p->width()*cos(p->angle() - PI / 2)));

	thereWasACollision = rightX && leftX && aboveY && belowY;
}
else if (p->angle() <= (3 * PI / 2) && p->angle() >= (PI))
{
	bool rightX(bottomLeftOfP.x <= (bottomLeftOfC.x + centralPiece.width() + p->height()*sin(p->angle() - PI)));
	bool leftX(bottomLeftOfP.x >= (bottomLeftOfC.x + p->width()*cos(p->angle() - PI)));
	bool aboveY(bottomLeftOfP.y <= (bottomLeftOfC.y + centralPiece.height() + p->height()*cos(p->angle() - PI) + p->width()*sin(p->angle() - PI)));
	bool belowY(bottomLeftOfP.y >= (bottomLeftOfC.y));

	thereWasACollision = rightX && leftX && aboveY && belowY;
}
else if (p->angle() <= (2 * PI) && p->angle() >= (PI))
{
	bool rightX(bottomLeftOfP.x <= (bottomLeftOfC.x + centralPiece.width()));
	bool leftX(bottomLeftOfP.x >= (bottomLeftOfC.x + p->width()*sin(p->angle() - 3 * PI / 2) + p->height()*cos(p->angle() - 3 * PI / 2)));
	bool aboveY(bottomLeftOfP.y <= (bottomLeftOfC.y + centralPiece.height() + p->width()*cos(p->angle() - 3 * PI / 2)));
	bool belowY(bottomLeftOfP.y >= (bottomLeftOfC.y - p->height()*sin(p->angle() - 3 * PI / 2)));

	thereWasACollision = rightX && leftX && aboveY && belowY;
}
*/