/*
JIGColisionDetector.cpp
Mark Underwood
4.4.17
Definitions for collision detector class
*/

#include "JIGCollisionDetector.h"
#include "JIGShape.h"
#include "KFAGeometry.h"
#include <cmath>
using std::sin;
using std::cos;
using std::sqrt;
using std::atan;
#include <iostream>
#include <memory>
#include <vector>
#include <map>

using namespace JIG;

std::unordered_map<unsigned, unsigned> CollisionDetector::_matrix;

CollisionDetector::CollisionDetector()
{}

CollisionDetector::CollisionDetector(std::unique_ptr<Shape> &centralPiece, std::vector<std::unique_ptr<Shape> > &otherPieces)
{
	detectCollisions(*centralPiece, otherPieces);
}

float findPhase(float radius, float widthOrHeight, float smallest)
{
	return std::asin((widthOrHeight - radius) / (0.5f*(radius - smallest)) + 1);
}

float projectedWidth(Shape &s, float angle)
{
	float halfWidth = s.getWidth() * 0.5f;
	float halfHeight = s.getHeight() * 0.5f;
	float radius = sqrt((halfWidth)*(halfWidth)+(halfHeight)*(halfHeight));
	float phase;
	if (halfWidth <= halfHeight)
	{
		phase = findPhase(radius, halfWidth, halfWidth);
		return 0.5f*(radius - halfWidth)*sin(2 * angle + phase) + 0.5f*(radius + halfWidth);
	}
	else
	{
		phase = findPhase(radius, halfWidth, halfHeight);
		return 0.5f*(radius - halfHeight)*sin(2 * angle + phase) + 0.5f*(radius + halfHeight);
	}

	return -1;
}

float projectedHeight(Shape &s, float angle)
{
	float halfWidth = s.getWidth() * 0.5f;
	float halfHeight = s.getHeight() * 0.5f;
	float radius = sqrt((halfWidth)*(halfWidth)+(halfHeight)*(halfHeight));
	float phase;

	if (halfWidth <= halfHeight)
	{
		phase = findPhase(radius, halfHeight, halfWidth);
		return 0.5f*(radius - halfWidth)*sin(2 * angle + phase ) + 0.5f*(radius + halfWidth);
	}
	else
	{
		phase = findPhase(radius, halfHeight, halfHeight);
		return 0.5f*(radius - halfHeight)*sin(2 * angle + phase) + 0.5f*(radius-halfHeight);
	}

	return -1;
}

void CollisionDetector::detectCollisions(Shape &centralPiece, std::vector<std::unique_ptr<Shape> > &otherPieces) //Find all collisions between one shape and the shapes around it.
{
	
	CollisionDetector::_matrix.insert({ 0, 0 });
	
	for (unsigned int i = 1; i < 2; ++i)
	{
		bool collisionOne;
		bool collisionTwo;
		bool collisionThree;
		bool collisionFour;

		float actualWidth = abs(centralPiece.centerPoint().x - otherPieces[i]->centerPoint().x);
		float actualHeight = abs(centralPiece.centerPoint().y - otherPieces[i]->centerPoint().y);
		float radius = sqrt(actualWidth*actualWidth + actualHeight*actualHeight);
			
		float newAngleP = otherPieces[i]->angle() - centralPiece.angle();

		float collidedWidth = centralPiece.getWidth()*0.5f + projectedWidth(*otherPieces[i], newAngleP);

		collisionOne = actualWidth <= collidedWidth;
			
		//float collidedHeight = centralPiece.getHeight()*0.5f + otherPieces[i]->getHeight()*0.5f;
		float collidedHeight = centralPiece.getHeight()*0.5f + projectedHeight(*otherPieces[i], newAngleP);

		collisionTwo = actualHeight <= collidedHeight;

		//float newAngleC = centralPiece.angle() - otherPieces[i]->angle();
		//
		//float collidedWidth2 = otherPieces[i]->getWidth()*0.5f + projectedWidth(centralPiece, newAngleC);
		//
		//collisionThree = actualWidth <= collidedWidth2;
		//
		//float collidedHeight2 = otherPieces[i]->getHeight()*0.5f + projectedHeight(centralPiece, newAngleC);

		bool thereWasACollision = collisionOne && collisionTwo;
		if (thereWasACollision)
		{
			_collision = true;
			++CollisionDetector::_matrix[0];
		}
	}
}

std::unordered_map<unsigned, unsigned> CollisionDetector::getMatrix()
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

************************************************************************************
for (unsigned int i = 0; i < otherPieces.size(); ++i)
{
if (otherPieces[i]->getVertexArrayID() != centralPiece->getVertexArrayID())
{
bool collisionOne;
bool collisionTwo;
bool collisionThree;
bool collisionFour;

float actualWidth = abs(centralPiece->centerPoint().x - otherPieces[i]->centerPoint().x);
float actualHeight = abs(centralPiece->centerPoint().x - otherPieces[i]->centerPoint().x);
float radius = sqrt(actualWidth*actualWidth + actualHeight*actualHeight);

float newAngleP = otherPieces[i]->angle() - centralPiece->angle();

float collidedWidth = centralPiece->getWidth()*0.5f + projectedWidth(*otherPieces[i], newAngleP);

collisionOne = actualWidth <= collidedWidth;

float collidedHeight = centralPiece->getHeight()*0.5f + projectedHeight(*otherPieces[i], newAngleP);

collisionTwo = actualHeight <= collidedHeight;

float newAngleC = centralPiece->angle() - otherPieces[i]->angle();

float collidedWidth2 = otherPieces[i]->getWidth()*0.5f + projectedWidth(*centralPiece, newAngleC);

collisionThree = actualWidth <= collidedWidth2;

float collidedHeight2 = otherPieces[i]->getHeight()*0.5f + projectedHeight(*centralPiece, newAngleC);

collisionFour;

bool thereWasACollision = collisionOne && collisionTwo;
if (thereWasACollision)
{
_collision = true;
++CollisionDetector::_matrix[centralPiece->getVertexArrayID()];
}
}
}
*/