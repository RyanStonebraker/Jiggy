/*
main.cpp
Mark Underwood
Any time
Play with stuff
*/

#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <vector>
using std::vector;
#include <algorithm>
using std::max_element;
using std::sort;
#include <fstream>
using std::ifstream;
using std::ofstream;
#include <cctype>
using std::toupper;
#include "JIGCollisionDetector.h"
#include "JIGRect.h"
#include "KFAGeometry.h"
#include "JIGShape.h"
using namespace JIG;

#if 0
int main()
{
	std::vector<std::unique_ptr<JIG::Shape>>global_LevelShapes;

	global_LevelShapes.push_back(std::make_unique<JIG::Rectangle>(JIG::Rectangle(JIGMakePoint(-400, 0, 200), 100.0f, 100.0f, 0.0f, JIGMakeColor(1.0f, 1.0f, 1.0f, 1.0f))));

	global_LevelShapes.push_back(std::make_unique<JIG::Rectangle>(JIG::Rectangle(JIGMakePoint(0, 0, 200), 100.0f, 300.0f, 0.0f, JIGMakeColor(1.0f, 1.0f, 1.0f, 1.0f))));

	JIG::CollisionDetector col(global_LevelShapes[0], global_LevelShapes);
	if (col.isCollided())
	{
		cout << "Collision!!" << endl;

		cout << "CentralPiece width: " << global_LevelShapes[0]->getWidth();
		cout << "CentralPiece height: " << global_LevelShapes[0]->getHeight();
		cout << "CentralPiece angle: " << global_LevelShapes[0]->angle();
		cout << endl;
		cout << "OtherPiece width: " << global_LevelShapes[1]->getWidth();
		cout << "OtherPiece height: " << global_LevelShapes[1]->getHeight();
		cout << "OtherPiece angle: " << global_LevelShapes[1]->angle();
		cout << "OtherPiece Projection: " << projectedWidth(global_LevelShapes[1], global_LevelShapes[1]->angle());
	}

	while (cin.get() != '\n')

	return 0;
}
#endif