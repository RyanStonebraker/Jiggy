/*
JIGCollisionDetector.h
Mark Underwood
4.4.17
Contains declarations for the collision detector class
*/


#if 0
#ifndef JIGCOLLISIONDETECTOR_H
#define JIGCOLLISIONDETECTOR_H

#include <unordered_map>
#include <string>
#include <vector>

#include "JIGShape.h"

namespace JIG{
class CollisionDetector
{
public:
	CollisionDetector();
	void addToMatrix(std::string, unsigned);
    CollisionDetector(JIG::Shape &, std::vector<JIG::Shape &>);
    void detectCollisions(JIG::Shape &, std::vector<JIG::Shape &>);
	std::unordered_map<std::string, unsigned> getAdjacent();
private:
	static std::unordered_map<std::string, unsigned> _matrix;
    std::vector<JIG::Shape> _pieces;
};
}


#endif // !COLLISION_H
#endif

