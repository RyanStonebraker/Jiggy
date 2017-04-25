// levelLoader.cpp
// Ryan Stonebraker
// 4/16/2017
// loads shape information from text file

#include "levelLoader.h"

#include <fstream>
#include <unordered_map>
#include <string>
#include <sstream>
#include "JIGShape.h"
#include "JIGRect.h"
#include <stdexcept>
#include "KFAGeometry.h"
#include <vector>
#include <memory>

JIG::LoadLevel::LoadLevel(std::string fname) : _fname{fname} {
    _getFromText();
}

void JIG::LoadLevel::_getFromText() {
    // TODO ERROR CHECKING
    std::ifstream reader(_fname);
    
    std::string shapeData;

    for (unsigned i = 0; getline(reader, shapeData); ++i) {
        
        std::istringstream shapeParser(shapeData);
        
        std::string shapeType;
        shapeParser >> shapeType;
        
        KFAPoint shapeLoc{0, 0, 0};
        shapeParser >> shapeLoc.x >> shapeLoc.y >> shapeLoc.z;
        
        float width = 0, height = 0;
        shapeParser >> width >> height;
        
        float angle = 1;
        shapeParser >> angle;
        
        if (shapeType == "Rect")
            _loadedShapes.push_back(std::make_unique<JIG::Rectangle>(JIG::Rectangle(shapeLoc, width, height, 0.0f, JIGMakeColor(1.0f, 1.0f, 1.0f, 1.0f))));
    }
}

std::unique_ptr<JIG::Shape> & JIG::LoadLevel::operator[](int i) {
    return _loadedShapes[i];
}

//void JIG::LoadLevel::renderLevel() const {
//    for (unsigned i = 0; i < _loadedShapes.size(); ++i) {
//        _loadedShapes[i]->submitForRender();
//    }

//}
