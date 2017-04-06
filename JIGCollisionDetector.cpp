/*
JIGColisionDetector.cpp
Mark Underwood
4.4.17
Definitions for collision detector class
*/

#include "Collision.h"
using std::make_pair;


CollisionDetector::CollisionDetector()
{}

CollisionDetector::CollisionDetector(std::vector<Shape> pieces)
{


	if ((s2.xpos() <= (s1.xpos() + s1.width)) && (s2.xpos() >= (s1.xpos() - s2.xpos)) && (s2.ypos() <= (s1.ypos() + s1.height())) && (s2.ypos() >= (s1.ypos - s2.height())))
	{

	}
}

void CollisionDetector::getAdjMatrix()
{

}